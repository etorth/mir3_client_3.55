

#ifndef __ORZ_CRYPTO__
#define __ORZ_CRYPTO__


struct crypto_seed
{
	unsigned char c[4];
	unsigned long x;
};


class /*__declspec( dllexport )*/ crypto
{
public:
	static void setSeed( crypto_seed *seed );
	static crypto_seed * getSeed();

	static bool encrypt( unsigned char *src, int srcLen );
	static bool decrypt( unsigned char *src, int srcLen );

	static bool encryptFile( char *srcName, char *dstName );
	static bool decryptFile( char *srcName, char *dstName );
};


#endif