#include "StdAfx.h"


#include "ScreenCapture.h"
#include <stdio.h>


#define HEADER_SIZE		(sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER ))


static void GetBmpHeaders( DDSURFACEDESC2 *ddsd, BITMAPFILEHEADER *fh, BITMAPINFOHEADER *ih )
{	
	memset( fh, 0, sizeof( BITMAPFILEHEADER ) );
	memset( ih, 0, sizeof( BITMAPINFOHEADER ) );

	fh->bfType			= 0x4D42; // BM
	fh->bfSize			= HEADER_SIZE + ddsd->dwWidth * ddsd->dwHeight * 2;
	fh->bfOffBits		= HEADER_SIZE;

	ih->biSize			= sizeof( BITMAPINFOHEADER );
	ih->biWidth			= ddsd->dwWidth;
	ih->biHeight		= ddsd->dwHeight;
	ih->biPlanes		= 1;
	ih->biBitCount		= 16;
	ih->biCompression	= BI_RGB;
	ih->biClrUsed		= 0;
	ih->biClrImportant	= 0;
	ih->biSizeImage		= 0;
}


static void RGB565_to_RGB555( DDSURFACEDESC2 *ddsd, WORD *dst )
{	
	WORD *src = (WORD *) ddsd->lpSurface;
	WORD *nxt;

	for ( DWORD y = 0; y < ddsd->dwHeight; y++ )
	{
		nxt = src + ddsd->lPitch;

		for ( DWORD x = 0; x < ddsd->dwWidth; x++, src++ )
			*dst++ = (*src & 0xF800) >> 1 | (*src & 0x07C0) >> 1 | *src & 0x001F;

		src = nxt;
	}
}


static void RGB555_to_RGB555( DDSURFACEDESC2 *ddsd, WORD *dst )
{
	WORD *src = (WORD *) ddsd->lpSurface;
	WORD *nxt;

	for ( DWORD y = 0; y < ddsd->dwHeight; y++ )
	{
		nxt = src + ddsd->lPitch;

		memcpy( dst, src, ddsd->dwWidth * 2 );
		dst += ddsd->dwWidth;

		src = nxt;
	}
}


static void BGR565_to_RGB555( DDSURFACEDESC2 *ddsd, WORD *dst )
{
	WORD *src = (WORD *) ddsd->lpSurface;
	WORD *nxt;

	for ( DWORD y = 0; y < ddsd->dwHeight; y++ )
	{
		nxt = src + ddsd->lPitch;

		for ( DWORD x = 0; x < ddsd->dwWidth; x++, src++ )
			*dst++ = (*src & 0x001F) << 10 | (*src & 0x07C0) >> 1 | (*src & 0xF800) >> 11;

		src = nxt;
	}
}


static void ReverseImage( DDSURFACEDESC2 *ddsd, WORD *dst )
{
	WORD *temp = new WORD[ddsd->dwWidth];
	WORD *l1 = dst;
	WORD *l2 = dst + ((ddsd->dwHeight - 1) * ddsd->dwWidth);
	int  len = ddsd->dwWidth * 2;

	for ( DWORD y = 0; y < ddsd->dwHeight / 2; y++ )
	{
		memcpy( temp, l1, len );
		memcpy( l1, l2, len );
		memcpy( l2, temp, len );

		l1 += ddsd->dwWidth;
		l2 -= ddsd->dwWidth;
	}

	delete[] temp;
}


static DWORD CalcChecksum( WORD *buf, int size )
{
	DWORD cksum = 0;

	while ( size > 1 )
	{
		cksum += *buf++;
		size  -= sizeof( WORD );
	}

	if ( size )
		cksum += *(BYTE *) buf;

	cksum  = (cksum >> 16) + (cksum & 0xFFFF);
	cksum += (cksum >> 16);
	cksum ^= 0x7F;

	return cksum;
}


void GenerateFileName( char *dir, char *res )
{
	int maxnum = 1;

	SetCurrentDirectory( dir );
	WIN32_FIND_DATA fd;
	HANDLE hfind = FindFirstFile( "SCREEN*.bmp", &fd );

	if ( hfind != INVALID_HANDLE_VALUE )
	{
		do
		{
			char idx[16] = {0,};
			char *ptr = fd.cFileName + strlen( "SCREEN" );
			memcpy( idx, ptr, strchr( ptr, '.' ) - ptr );
			
			if ( atoi( idx ) >= maxnum )
				maxnum = atoi( idx ) + 1;

		} while ( FindNextFile( hfind, &fd ) );
	}

	sprintf( res, "%s\\SCREEN%04d.bmp", dir, maxnum );
}


void scScreenCapture7( IDirectDrawSurface7 *surface, char *dir )
{
	DDSURFACEDESC2 ddsd;
	ddsd.dwSize = sizeof( DDSURFACEDESC2 );

	surface->Lock( NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL );
	{
		WORD *image = new WORD[ddsd.dwWidth * ddsd.dwHeight * 2];
		if ( !image )
		{
			surface->Unlock( NULL );
			return;
		}
		
		BITMAPFILEHEADER fh;
		BITMAPINFOHEADER ih;
		GetBmpHeaders( &ddsd, &fh, &ih );

		ddsd.lPitch >>= 1;
		
		switch ( ddsd.ddpfPixelFormat.dwRBitMask )
		{
		case 0xF800: RGB565_to_RGB555( &ddsd, image ); break;
		case 0x7C00: RGB555_to_RGB555( &ddsd, image ); break;
		case 0x001F: BGR565_to_RGB555( &ddsd, image ); break;
		}
		
		ReverseImage( &ddsd, image );

		DWORD cksum[3];
		cksum[0] = CalcChecksum( (WORD *) &fh, sizeof( fh ) );
		cksum[1] = CalcChecksum( (WORD *) &ih, sizeof( ih ) );
		cksum[2] = CalcChecksum( image, ddsd.dwWidth * ddsd.dwHeight * 2 );

		char filename[1024];
		if ( !dir )
		{
			char cdir[1024];
			GetCurrentDirectory( sizeof( cdir ), cdir );
			GenerateFileName( cdir, filename );
		}
		else
			GenerateFileName( dir, filename );
				
		FILE *fp = fopen( filename, "wb" );
		if ( fp )
		{
			fwrite( &fh, 1, sizeof( fh ), fp );
			fwrite( &ih, 1, sizeof( ih ), fp );
			fwrite( image, 1, ddsd.dwWidth * ddsd.dwHeight * 2, fp );
			fwrite( cksum, 1, sizeof( cksum ), fp );
			fclose( fp );
		}
		
		delete[] image;
	}
	surface->Unlock( NULL );
}


bool scIsValid( char *filename )
{
	FILE *fp = fopen( filename, "rb" );
	if ( !fp )
		return false;

	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;

	if ( fread( &fh, 1, sizeof( fh ), fp ) != sizeof( fh ) ||
		 fread( &ih, 1, sizeof( ih ), fp ) != sizeof( ih ) )
	{
		fclose( fp );
		return false;
	}

	DWORD size = fh.bfSize - HEADER_SIZE;
	char *image = new char[size];

	if ( !image )
	{
		fclose( fp );
		return false;
	}

	DWORD cksum[3];

	if ( fread( image, 1, size, fp ) != size || 
		 fread( cksum, 1, sizeof( cksum ), fp ) != sizeof( cksum ) )
	{
		delete[] image;
		fclose( fp );
		return false;
	}

	if ( cksum[0] != CalcChecksum( (WORD *) &fh, sizeof( fh ) ) || 
		 cksum[1] != CalcChecksum( (WORD *) &ih, sizeof( ih ) ) ||
		 cksum[2] != CalcChecksum( (WORD *) image, size ) )
	{
		delete[] image;
		fclose( fp );
		return false;
	}

	delete[] image;
	fclose( fp );
	return true;
}
