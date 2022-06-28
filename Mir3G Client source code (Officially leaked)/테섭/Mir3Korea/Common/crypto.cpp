

#include "StdAfx.h"
#include "crypto.h"
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <time.h>


static crypto_seed _gs;


void crypto::setSeed( crypto_seed *seed )
{
	if ( seed )
	{
		_gs = *seed;
	}
	else
	{
		srand( time( NULL ) );

		for ( int i = 0; i < 4; i++ )
			_gs.c[i] = rand() % 256;

		_gs.x = rand() << 16 | rand();
	}
}


crypto_seed * crypto::getSeed()
{
	return &_gs;
}


bool crypto::encrypt( unsigned char *src, int srcLen )
{
	unsigned char *dst = src - 8;
	int i, j, key, checksum = 0;

	dst[0] = (srcLen >> 24 & 0xFF) ^ _gs.c[0];
	dst[1] = (srcLen >> 16 & 0xFF) ^ _gs.c[1];
	dst[2] = (srcLen >>  8 & 0xFF) ^ _gs.c[2];
	dst[3] = (srcLen >>  0 & 0xFF) ^ _gs.c[3];
		
	for ( i = 0; i < 4; i++ )
	{
		key = dst[i];

		for ( j = 0; j < srcLen; j++ )
			src[j] ^= key++;
	}

	for ( i = 0; i < srcLen; i++ )
		checksum += src[i] * i + i;

	checksum ^= _gs.x;

	*((int *) dst + 1) = checksum;

	return true;
}


bool crypto::decrypt( unsigned char *src, int srcLen )
{
	unsigned char *dst = src + 8;
	int length, i, j, key, checksum = 0;

	length = (src[0] ^ _gs.c[0]) << 24 | 
			 (src[1] ^ _gs.c[1]) << 16 | 
			 (src[2] ^ _gs.c[2]) <<  8 | 
			 (src[3] ^ _gs.c[3]);

	for ( i = 0; i < srcLen - 8; i++ )
		checksum += dst[i] * i + i;

	checksum ^= _gs.x;

	if ( checksum != *((int *) src + 1) )
		return false;

	for ( i = 3; i >= 0; i-- )
	{
		key = src[i];

		for ( j = 0; j < length; j++ )
			dst[j] ^= key++;
	}

	return true;
}


bool crypto::encryptFile( char *srcName, char *dstName )
{
	FILE *fp = fopen( srcName, "rb" );
	if ( !fp )
		return false;

	int len = _filelength( _fileno( fp ) );
	char *buf = new char[ len + 8 ];
	if ( !buf )
	{
		fclose( fp );
		return false;
	}

	fread( buf + 8, 1, len, fp );
	fclose( fp );

	if ( !encrypt( (unsigned char *) buf + 8, len ) )
	{
		delete[] buf;
		return false;
	}

	fp = fopen( dstName, "wb" );
	if ( !fp )
	{
		delete[] buf;
		return false;
	}

	fwrite( buf, 1, len + 8, fp );
	fclose( fp );

	delete[] buf;
	return true;
}


bool crypto::decryptFile( char *srcName, char *dstName )
{
	FILE *fp = fopen( srcName, "rb" );
	if ( !fp )
		return false;

	int len = _filelength( _fileno( fp ) );
	char *buf = new char[ len ];
	if ( !buf )
	{
		fclose( fp );
		return false;
	}

	fread( buf, 1, len, fp );
	fclose( fp );

	if ( !decrypt( (unsigned char *) buf, len ) )
	{
		delete[] buf;
		return false;
	}

	fp = fopen( dstName, "wb" );
	if ( !fp )
	{
		delete[] buf;
		return false;
	}

	fwrite( buf + 8, 1, len - 8, fp );
	fclose( fp );

	delete[] buf;
	return true;
}