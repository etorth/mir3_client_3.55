

#ifndef __ORZ_SCREEN_CAPTURE__
#define __ORZ_SCREEN_CAPTURE__


#include <ddraw.h>


/*
	scScreenCapture7
	- 현재 DirectDraw 서피스를 BMP로 저장하는 함수

	IDirectDrawSurface7 *surface
	- DirectDrawSurface7 인터페이스

	char *dir
	- 저장할 디렉토리 (파일은 SCREEN0001.BMP 식으로 저장된다.)
	주1) 반드시 존재하고 있는 디렉토리여야 한다.
	주2) 기본 인자 NULL을 사용하면 현재 디렉토리에 저장된다. (비추천)
	     이 경우 C:\ 드라이브에서 바로 실행했다면 
		 C:\SCREEN0001.BMP 식의 파일이 만들어지므로 주의해야 한다.
*/
void scScreenCapture7( IDirectDrawSurface7 *surface, char *dir = NULL );

/*
	scIsValid
	- 조작된 파일인지 아닌지 판별하는 함수

	char *filename
	- 검사할 비트맵 파일명
*/
bool scIsValid( char *filename );


#endif