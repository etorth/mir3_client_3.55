/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/
#include "StdAfx.h"



/******************************************************************************************************************

	CParticleSystem Class	

*******************************************************************************************************************/
CParticleSystem::CParticleSystem()
{
	InitSystem();
}


CParticleSystem::~CParticleSystem()
{
	DestroySystem();
}


VOID CParticleSystem::InitSystem()
{
	m_nNum			 = 0;		
	m_pxParticle	 = NULL;
	m_fDeltaTime	 = 0.02f;

	m_fAirFiction	 = -0.05f;
	m_vecBounding[0] = D3DVECTOR(0, 0, 0);
	m_vecBounding[1] = D3DVECTOR(0, 0, 0);
	m_vecEnvironment = D3DVECTOR(0, 300, 0);

	D3DVECTOR vNorm(0, 0, -1);
	m_avShape[0] = D3DVERTEX(D3DVECTOR(-0.5f,-0.5f, 0.0f ), vNorm, 0.0f, 1.0f);
	m_avShape[1] = D3DVERTEX(D3DVECTOR( 0.5f,-0.5f, 0.0f ), vNorm, 0.0f, 0.0f);
	m_avShape[2] = D3DVERTEX(D3DVECTOR(-0.5f, 0.5f, 0.0f ), vNorm, 1.0f, 1.0f);
	m_avShape[3] = D3DVERTEX(D3DVECTOR( 0.5f, 0.5f, 0.0f ), vNorm, 1.0f, 0.0f);
}


VOID CParticleSystem::SetupSystem(WORD wCnt)
{
	InitSystem();
	m_nNum = wCnt;

    m_pxParticle = new CParticle[m_nNum];

	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		m_pxParticle[nCnt].Init();
	}
}


VOID CParticleSystem::DestroySystem()
{
	SAFE_DELETEARR(m_pxParticle);

	InitSystem();
}


VOID CParticleSystem::UpdateAirFiction(INT nNum)
{
	if ( !m_pxParticle[nNum].m_bIsDead )
	{
		m_pxParticle[nNum].m_vecLocalForce.x = -m_pxParticle[nNum].m_vecVel.x * m_fAirFiction;
		m_pxParticle[nNum].m_vecLocalForce.y = -m_pxParticle[nNum].m_vecVel.y * m_fAirFiction;
		m_pxParticle[nNum].m_vecLocalForce.z = m_pxParticle[nNum].m_vecVel.z * m_fAirFiction;
	}
}


VOID CParticleSystem::UpdateMove(INT nNum)
{
	if ( !m_pxParticle[nNum].m_bIsDead )
	{
		if ( m_pxParticle[nNum].m_fMass == 0.0f )
		{
			m_pxParticle[nNum].m_fMass = 1.0f;
		}

		m_pxParticle[nNum].m_vecAccel.x += (m_vecEnvironment.x + m_pxParticle[nNum].m_vecLocalForce.x) / m_pxParticle[nNum].m_fMass;
		m_pxParticle[nNum].m_vecAccel.y += (m_vecEnvironment.y + m_pxParticle[nNum].m_vecLocalForce.y) / m_pxParticle[nNum].m_fMass;
		m_pxParticle[nNum].m_vecAccel.z += (m_vecEnvironment.z + m_pxParticle[nNum].m_vecLocalForce.z) / m_pxParticle[nNum].m_fMass;

		m_pxParticle[nNum].m_vecVel.x += m_pxParticle[nNum].m_vecAccel.x * m_fDeltaTime;//*0.01f;
		m_pxParticle[nNum].m_vecVel.y += m_pxParticle[nNum].m_vecAccel.y * m_fDeltaTime;//*0.01f;
		m_pxParticle[nNum].m_vecVel.z += m_pxParticle[nNum].m_vecAccel.z * m_fDeltaTime;//*0.01f;

		m_pxParticle[nNum].m_vecOldPos = m_pxParticle[nNum].m_vecPos;

		m_pxParticle[nNum].m_vecPos.x += m_pxParticle[nNum].m_vecVel.x * m_fDeltaTime;//*0.01f;
		m_pxParticle[nNum].m_vecPos.y += m_pxParticle[nNum].m_vecVel.y * m_fDeltaTime;//*0.01f;
		m_pxParticle[nNum].m_vecPos.z += m_pxParticle[nNum].m_vecVel.z * m_fDeltaTime;//*0.01f;
	}
}


VOID CParticleSystem::UpdateCrash(INT nNum)
{
	if ( !m_pxParticle[nNum].m_bIsDead )
	{
		if ( m_pxParticle[nNum].m_vecPos.x <= m_vecBounding[0].x || m_pxParticle[nNum].m_vecPos.x >= m_vecBounding[1].x )
		{	
			m_pxParticle[nNum].m_vecVel.x = -m_pxParticle[nNum].m_vecVel.x * 0.7f;
		}

		if ( m_pxParticle[nNum].m_vecPos.y <= m_vecBounding[0].y || m_pxParticle[nNum].m_vecPos.y >= m_vecBounding[1].y )
		{
			FLOAT fOldX = m_pxParticle[nNum].m_vecPos.x - m_pxParticle[nNum].m_vecVel.x * m_pxParticle[nNum].m_nDelay;
			FLOAT fOldY = m_pxParticle[nNum].m_vecPos.y - m_pxParticle[nNum].m_vecVel.y * m_pxParticle[nNum].m_nDelay;

			FLOAT fBefore = 0.0f;
			FLOAT fAfter  = 0.0f;

			if ( (m_pxParticle[nNum].m_vecPos.y - fOldY) != 0 )
				fBefore = m_pxParticle[nNum].m_nDelay * (m_vecBounding[1].y - fOldY)/(m_pxParticle[nNum].m_vecPos.y - fOldY);				// 충돌전.

			if ( (m_pxParticle[nNum].m_vecPos.y - fOldY) != 0 )
				fAfter  = m_pxParticle[nNum].m_nDelay * (m_pxParticle[nNum].m_vecPos.y - m_vecBounding[1].y)/(m_pxParticle[nNum].m_vecPos.y - fOldY);	// 충돌후.
			
			m_pxParticle[nNum].m_vecPos.x = fOldX + m_pxParticle[nNum].m_vecVel.x * fBefore;
			m_pxParticle[nNum].m_vecPos.y = fOldY + m_pxParticle[nNum].m_vecVel.y * fBefore;
			
			m_pxParticle[nNum].m_vecVel.y = -m_pxParticle[nNum].m_vecVel.y * 0.6f;
			
			m_pxParticle[nNum].m_vecPos.x += m_pxParticle[nNum].m_vecVel.x * fAfter;
			m_pxParticle[nNum].m_vecPos.y += m_pxParticle[nNum].m_vecVel.y * fAfter;			
		}

		if ( m_pxParticle[nNum].m_vecPos.z <= m_vecBounding[0].z || m_pxParticle[nNum].m_vecPos.z >= m_vecBounding[1].y )
		{
			m_pxParticle[nNum].m_vecVel.z = -m_pxParticle[nNum].m_vecVel.z * 0.6f;
		}
	}
}



/******************************************************************************************************************

	CScatter Class	

*******************************************************************************************************************/
CScatter::CScatter()
{
	InitSystem();
}


CScatter::~CScatter()
{
	DestroySystem();
}



VOID CScatter::InitSystem()
{
	CParticleSystem::InitSystem();
	m_shPartNum = 0;
}


VOID CScatter::DestroySystem()
{
	CParticleSystem::DestroySystem();
	InitSystem();
}


VOID CScatter::SetupSystem(WORD wCnt)
{
	InitSystem();
	CParticleSystem::SetupSystem(wCnt);
}


VOID CScatter::UpdateSystem(INT nLoopTime, D3DVECTOR vecGenPos)
{
	// 현재 좌표에서 목적좌표로 이동.
	INT nPartCnt = 0;

    for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
    {
		if ( !m_pxParticle[nCnt].m_bIsDead )
		{
			if ( !m_pxParticle[nCnt].m_bIsDead )
			{
				m_pxParticle[nCnt].m_nCurrLife += nLoopTime;
			}

			// 거리측정.
			INT nScrnGapX, nScrnGapY;
			if ( m_pxParticle[nCnt].m_vecPos.x != m_pxParticle[nCnt].m_vecDstPos.x )
			{
				nScrnGapX = abs(m_pxParticle[nCnt].m_vecDstPos.x-m_pxParticle[nCnt].m_vecPos.x);
			}
			else
			{
				nScrnGapX = 1;
			}

			if ( m_pxParticle[nCnt].m_vecPos.y != m_pxParticle[nCnt].m_vecDstPos.y )
			{
				nScrnGapY = abs(m_pxParticle[nCnt].m_vecDstPos.y-m_pxParticle[nCnt].m_vecPos.y);
			}
			else
			{
				nScrnGapY = 1;
			}

			if ( nScrnGapX == 0 )
			{
				nScrnGapX = 1;
			}
			if ( nScrnGapY == 0 )
			{
				nScrnGapY = 1;
			}

			FLOAT fGapRateX = (FLOAT)(500/(FLOAT)nScrnGapX);
			FLOAT fGapRateY = (FLOAT)(500/(FLOAT)nScrnGapY);

			INT nDisX, nDisY;

			if ( nScrnGapX > nScrnGapY )
			{
				nDisX = (INT)((m_pxParticle[nCnt].m_vecDstPos.x-m_pxParticle[nCnt].m_vecPos.x) * (fGapRateX));
				nDisY = (INT)((m_pxParticle[nCnt].m_vecDstPos.y-m_pxParticle[nCnt].m_vecPos.y) * (fGapRateX));
			}
			else
			{
				nDisX = (INT)((m_pxParticle[nCnt].m_vecDstPos.x-m_pxParticle[nCnt].m_vecPos.x) * (fGapRateY));
				nDisY = (INT)((m_pxParticle[nCnt].m_vecDstPos.y-m_pxParticle[nCnt].m_vecPos.y) * (fGapRateY));
			}

			FLOAT fDisX = (FLOAT)((FLOAT)nDisX/1000);
			FLOAT fDisY = (FLOAT)((FLOAT)nDisY/1000);

			m_pxParticle[nCnt].m_vecOldPos.x = m_pxParticle[nCnt].m_vecPos.x;
			m_pxParticle[nCnt].m_vecOldPos.y = m_pxParticle[nCnt].m_vecPos.y;

			m_pxParticle[nCnt].m_vecPos.x += ((fDisX)*(FLOAT)nLoopTime);
			m_pxParticle[nCnt].m_vecPos.y += ((fDisY)*(FLOAT)nLoopTime);

		   INT nabsX, nabsY;
		   nabsX = abs(m_pxParticle[nCnt].m_vecDstPos.x-m_pxParticle[nCnt].m_vecPos.x);
		   nabsY = abs(m_pxParticle[nCnt].m_vecDstPos.y-m_pxParticle[nCnt].m_vecPos.y);
 		   if ( (nabsX <= 10 && nabsY <= 10) || (nabsX >= m_pxParticle[nCnt].m_vecPrevDis.x && nabsY >= m_pxParticle[nCnt].m_vecPrevDis.y) )
		   {
//			   if ( m_pxParticle[nCnt].m_nCurrLife > m_pxParticle[nCnt].m_nLife /*|| nCnt%5*/ )
			   {
				   m_pxParticle[nCnt].Init();
				   m_shPartNum--;
			   }
//			   else
			   {
//				   m_pxParticle[nCnt].m_fSize = (FLOAT)GetRandomNum(10, 50);
			   }
		   }
		   else
		   {
				m_pxParticle[nCnt].m_vecPrevDis.x = nabsX;
				m_pxParticle[nCnt].m_vecPrevDis.y = nabsY;
		   }


		   nPartCnt++;
		}

		if ( nPartCnt >= m_shPartNum )
		{
			return;
		}
    }
}


HRESULT CScatter::RenderSystem(LPDIRECT3DDEVICE7 lpDevice)
{
	if ( lpDevice )
	{
		D3DMATRIX matWorldOriginal;
		D3DMATRIX matTmpWorld;
		D3DMATRIX matTrans;
		D3DMATRIX matScale;
		D3DMATRIX matRot;
		D3DMATRIX matWorld;
		D3DVECTOR vTrans;
		D3DMATERIAL7 mtrl;
		INT nPartCnt = 0;

		if( SUCCEEDED(lpDevice->BeginScene()) )
		{
			lpDevice->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
			{
				if ( !m_pxParticle[nCnt].m_bIsDead )
				{
					D3DUtil_InitMaterial(mtrl, 
										 (FLOAT)m_pxParticle[nCnt].m_bRed/255.0f,
										 (FLOAT)m_pxParticle[nCnt].m_bGreen/255.0f, 
										 (FLOAT)m_pxParticle[nCnt].m_bBlue/255.0f);
					mtrl.diffuse.a = 1.0f/255.0f;
					lpDevice->SetMaterial(&mtrl);

  					vTrans.x = (FLOAT) m_pxParticle[nCnt].m_vecPos.x-400;
					vTrans.y = (FLOAT)-m_pxParticle[nCnt].m_vecPos.y+300;
					vTrans.z = (FLOAT) m_pxParticle[nCnt].m_vecPos.z;
					D3DUtil_SetScaleMatrix(matScale, 4.0f, m_pxParticle[nCnt].m_fSize, 1.0f);
					D3DUtil_SetRotateZMatrix(matRot, g_PI/2 - atan((m_pxParticle[nCnt].m_vecPos.y - m_pxParticle[nCnt].m_vecOldPos.y)/(m_pxParticle[nCnt].m_vecPos.x - m_pxParticle[nCnt].m_vecOldPos.x)));
					D3DUtil_SetTranslateMatrix(matTrans, vTrans);
					D3DMath_MatrixMultiply(matTmpWorld, matRot, matTrans);
					D3DMath_MatrixMultiply(matWorld, matScale, matTmpWorld);
					lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);
/*
					lpDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
					lpDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, TRUE);
					lpDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
					lpDevice->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
					lpDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
					lpDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
					lpDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);*/

					SetBlendRenderState(lpDevice, 1, &mtrl);

					LPDIRECTDRAWSURFACE7 lpddsParticleTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_PARTICLE, _IMAGE_PROGUSE, 520+m_pxParticle[nCnt].m_nCurrFrame);
					lpDevice->SetTexture(0, lpddsParticleTextr);
					lpDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avShape, 4, NULL);

/*
					lpDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
					lpDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);
					lpDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND , D3DBLEND_ONE);
					lpDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);*/

					ResetBlendenderState(lpDevice);

					lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);
					nPartCnt++;
				}

				if ( nPartCnt >= m_shPartNum )
				{
					break;
				}
			}

			lpDevice->EndScene();

			return S_OK;
		}
	}
	return E_FAIL;
}


VOID CScatter::SetParticles(D3DVECTOR vecDstPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			m_pxParticle[nCnt].m_vecPos		= D3DVECTOR((FLOAT)vecDstPos.x+GetRandomNum(-400, 400), (FLOAT)vecDstPos.y+GetRandomNum(-400, 400), 0.0f);
			m_pxParticle[nCnt].m_vecDstPos	= vecDstPos;
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(2000, 2200);
			m_pxParticle[nCnt].m_fMass		= 1000 + _RAND_FLOAT;
			m_pxParticle[nCnt].m_fSize		= (FLOAT)GetRandomNum(30, 100) + _RAND_FLOAT;
			m_pxParticle[nCnt].m_bIsDead	= FALSE;
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed   = (FLOAT)GetRandomNum(100, 125);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen = m_pxParticle[nCnt].m_bFstRed/2;
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue  = (FLOAT)GetRandomNum(0, 15);
/*			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed   = (FLOAT)GetRandomNum(50, 255);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen = (FLOAT)GetRandomNum(50, 255);
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue  = (FLOAT)GetRandomNum(50, 255);*/
			m_pxParticle[nCnt].m_nDelay		= 300;
			m_pxParticle[nCnt].m_nCurrDelay = 0;
			m_pxParticle[nCnt].m_nCurrFrame = 0;
			m_pxParticle[nCnt].m_bOpa		= 255;

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt >= 150 )
				return;
		}
	}
}




/******************************************************************************************************************

	CSnow Class	

*******************************************************************************************************************/
CSnow::CSnow()
{
	InitSystem();
}


CSnow::~CSnow()
{
	DestroySystem();
}



VOID CSnow::InitSystem()
{
	CParticleSystem::InitSystem();
	m_fWidth = m_fGround = 0.0f;
	m_shPartNum = 0;
}


VOID CSnow::DestroySystem()
{
	CParticleSystem::DestroySystem();

	InitSystem();
}


VOID CSnow::SetupSystem(WORD wCnt, FLOAT fWidth, FLOAT fGround)
{
	InitSystem();
	CParticleSystem::SetupSystem(wCnt);

	m_fWidth  = fWidth;
	m_fGround = fGround;

	SetEnvFactor(-0.05f, D3DVECTOR(10, 100, 0));
}


VOID CSnow::UpdateSystem(INT nLoopTime, D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0; 
	INT nPartCnt = 0;
	INT nSpeedRate = (nLoopTime / 17);

	if ( nSpeedRate < 1 ) 		
	{
		nSpeedRate = 1;
	}

	m_fDeltaTime = 0.02f*nSpeedRate;

    for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
    {
		// 파티클 생성.
		if ( m_pxParticle[nCnt].m_bIsDead && nGenCnt < 5 )
		{
			SetParticleDefault(nCnt);
			m_shPartNum++;
			nGenCnt++;
		}

		if ( !m_pxParticle[nCnt].m_bIsDead )
		{
			m_pxParticle[nCnt].m_nCurrLife += nLoopTime;

			// 파티클 소멸조건.
			if ( m_pxParticle[nCnt].m_nCurrLife > m_pxParticle[nCnt].m_nLife || m_pxParticle[nCnt].m_vecPos.y >= m_fGround )
			{
				if( (m_pxParticle[nCnt].m_nCurrLife-m_pxParticle[nCnt].m_nLife) > 255 )
				{
					m_pxParticle[nCnt].Init();
					m_shPartNum--;
					nPartCnt--;
				}
				// 점점 사라지게 한다.
				else
				{
					BYTE bRate;
					bRate = (BYTE)(255 - (m_pxParticle[nCnt].m_nCurrLife-m_pxParticle[nCnt].m_nLife));

					m_pxParticle[nCnt].m_bOpa = bRate;
					
					if ( bRate < m_pxParticle[nCnt].m_bRed )				m_pxParticle[nCnt].m_bRed = bRate;
					if ( bRate < m_pxParticle[nCnt].m_bGreen )				m_pxParticle[nCnt].m_bGreen = bRate;
					if ( bRate < m_pxParticle[nCnt].m_bBlue )				m_pxParticle[nCnt].m_bBlue = bRate;

					nPartCnt++;
				}
				continue;
			}

			UpdateAirFiction(nCnt);
			UpdateMove(nCnt);

			m_pxParticle[nCnt].m_nCurrDelay += nLoopTime;
			if ( m_pxParticle[nCnt].m_nCurrDelay > m_pxParticle[nCnt].m_nDelay )
			{
				m_pxParticle[nCnt].m_nCurrDelay = 0;
				m_pxParticle[nCnt].m_nCurrFrame++;

//				FLOAT fRand = _RAND_FLOAT;
//				SetEnvFactor(fRand, D3DVECTOR(-fRand, fRand*100, 0));

				if ( m_pxParticle[nCnt].m_nCurrFrame >= _MAX_SNOWFRAME )
				{
					m_pxParticle[nCnt].m_nCurrFrame = 0;
				}
			}

			nPartCnt++;
		}
		if ( nPartCnt >= m_shPartNum )
		{
			return;
		}
    }
}


HRESULT CSnow::RenderSystem(LPDIRECT3DDEVICE7 lpDevice)
{
	if ( lpDevice )
	{
		D3DMATRIX matWorldOriginal;
		D3DMATRIX matTrans;
		D3DMATRIX matScale;
		D3DMATRIX matWorld;
		D3DVECTOR vTrans;
		D3DMATERIAL7 mtrl;
		INT nPartCnt = 0;

		if( SUCCEEDED(lpDevice->BeginScene()) )
		{
			lpDevice->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
			{
				if ( !m_pxParticle[nCnt].m_bIsDead )
				{
					D3DUtil_InitMaterial(mtrl, 
										 (FLOAT)m_pxParticle[nCnt].m_bRed/255.0f,
										 (FLOAT)m_pxParticle[nCnt].m_bGreen/255.0f, 
										 (FLOAT)m_pxParticle[nCnt].m_bBlue/255.0f);
					mtrl.diffuse.a = 1.0f/255.0f;
					lpDevice->SetMaterial(&mtrl);

  					vTrans.x = (FLOAT) m_pxParticle[nCnt].m_vecPos.x-400;
					vTrans.y = (FLOAT)-m_pxParticle[nCnt].m_vecPos.y+300;
					vTrans.z = (FLOAT) m_pxParticle[nCnt].m_vecPos.z;
					D3DUtil_SetScaleMatrix(matScale, m_pxParticle[nCnt].m_fSize, m_pxParticle[nCnt].m_fSize, m_pxParticle[nCnt].m_fSize);
					D3DUtil_SetTranslateMatrix(matTrans, vTrans);
					D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
					lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

					lpDevice->SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
					lpDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, TRUE);
					lpDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
					lpDevice->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
					lpDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
					lpDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
					lpDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

					LPDIRECTDRAWSURFACE7 lpddsParticleTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_PARTICLE, _IMAGE_PROGUSE, 500+m_pxParticle[nCnt].m_nCurrFrame);
					lpDevice->SetTexture(0, lpddsParticleTextr);
					lpDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avShape, 4, NULL);

					lpDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
					lpDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);
					lpDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND , D3DBLEND_ONE);
					lpDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
					lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

					lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);
					nPartCnt++;
				}
				if ( nPartCnt >= m_shPartNum )
				{
					break;
				}
			}
			lpDevice->EndScene();

			return S_OK;
		}
	}
	return E_FAIL;
}


VOID CSnow::SetParticleDefault(INT nNum, D3DVECTOR vecGenPos)
{
    m_pxParticle[nNum].m_vecPos		= D3DVECTOR((FLOAT)GetRandomNum(0, (INT)m_fWidth)/*(-400, 1200)*/, (FLOAT)GetRandomNum(-300,  0), 0.0f);
    m_pxParticle[nNum].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-30,  30), (FLOAT)GetRandomNum(70, 100), 0.0f);
	m_pxParticle[nNum].m_vecAccel	= D3DVECTOR(0.0f, 0.0f, 0.0f);
	m_pxParticle[nNum].m_vecOldPos	= D3DVECTOR(0.0f, 0.0f, 0.0f);
	m_pxParticle[nNum].m_vecLocalForce = D3DVECTOR(0.0f, 0.0f, 0.0f);
	m_pxParticle[nNum].m_nLife		= GetRandomNum(2500,  7000);
	m_pxParticle[nNum].m_fMass		= 1000 + _RAND_FLOAT;
	m_pxParticle[nNum].m_fSize		= (FLOAT)GetRandomNum(2, 6) + _RAND_FLOAT;
//	m_pxParticle[nNum].m_nLife		= (FLOAT)GetRandomNum((BYTE)m_pxParticle[nNum].m_fSize*2000,  6000);
	m_pxParticle[nNum].m_bIsDead	= FALSE;
	m_pxParticle[nNum].m_bRed		= m_pxParticle[nNum].m_bGreen = m_pxParticle[nNum].m_bBlue = (BYTE)GetRandomNum(/*(BYTE)(m_pxParticle[nNum].m_fSize)*30+20*/120, 150);
	m_pxParticle[nNum].m_bBlue		+= 100;
//	m_pxParticle[nNum].m_bRed		= (FLOAT)GetRandomNum(0, 255);
//	m_pxParticle[nNum].m_bGreen		= (FLOAT)GetRandomNum(0, 255);
//	m_pxParticle[nNum].m_bBlue		= (FLOAT)GetRandomNum(0, 255);
	m_pxParticle[nNum].m_nDelay		= 300;//(FLOAT)GetRandomNum(50, 150);
	m_pxParticle[nNum].m_nCurrLife	= 0;
	m_pxParticle[nNum].m_nCurrDelay = 0;
	m_pxParticle[nNum].m_nCurrFrame = 0;
	m_pxParticle[nNum].m_bOpa		= 255;
}









/******************************************************************************************************************

	CRain Class	

*******************************************************************************************************************/
CRain::CRain()
{
	InitSystem();
}


CRain::~CRain()
{
	DestroySystem();
}


VOID CRain::InitSystem()
{
	CParticleSystem::InitSystem();
	m_fWidth = m_fGround = 0.0f;
	m_bRainIntensity = 0;
	m_bGenCnt = 10;
}


VOID CRain::DestroySystem()
{
	CParticleSystem::DestroySystem();

	InitSystem();
}


VOID CRain::SetupSystem(WORD wCnt, FLOAT fWidth, FLOAT fGround)
{
	InitSystem();
	CParticleSystem::SetupSystem(wCnt);

	m_fWidth  = fWidth;
	m_fGround = fGround;

	SetEnvFactor(-0.05f, D3DVECTOR(10, 100, 0));
}


VOID CRain::UpdateSystem(INT nLoopTime, D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0; 
	INT nPartCnt = 0;
	INT nSpeedRate = (nLoopTime / 17);
	if ( nSpeedRate < 1 ) 		
	{
		nSpeedRate = 1;
	}

	m_fDeltaTime = 0.02f*nSpeedRate;

    for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
    {
		// 파티클 생성.
		if ( m_pxParticle[nCnt].m_bIsDead && nGenCnt < 11/*m_bGenCnt*/ )
		{
			SetParticleDefault(nCnt);
			m_shPartNum++;
			nGenCnt++;
		}

		if ( !m_pxParticle[nCnt].m_bIsDead )
		{
			m_pxParticle[nCnt].m_nCurrLife += nLoopTime;

			// 파티클 소멸조건.
			if ( m_pxParticle[nCnt].m_nCurrLife > m_pxParticle[nCnt].m_nLife || m_pxParticle[nCnt].m_vecPos.y >= m_fGround )
			{
				if( (m_pxParticle[nCnt].m_nCurrLife-m_pxParticle[nCnt].m_nLife) > /*_MAX_RAINDROPFRAME*50*/250 )
				{
					m_pxParticle[nCnt].Init();
					m_shPartNum--;
					nPartCnt--;
				}
				else
				{
					BYTE bRate;
					bRate = (BYTE)(250 - (m_pxParticle[nCnt].m_nCurrLife-m_pxParticle[nCnt].m_nLife) / 4);

					m_pxParticle[nCnt].m_bOpa = bRate;
					m_pxParticle[nCnt].m_nDelay = 50;
					
					if ( bRate < m_pxParticle[nCnt].m_bRed )				m_pxParticle[nCnt].m_bRed = bRate;
					if ( bRate < m_pxParticle[nCnt].m_bGreen )				m_pxParticle[nCnt].m_bGreen = bRate;
					if ( bRate < m_pxParticle[nCnt].m_bBlue )				m_pxParticle[nCnt].m_bBlue = bRate;

					m_pxParticle[nCnt].m_nCurrDelay += nLoopTime;
					if ( m_pxParticle[nCnt].m_nCurrDelay > m_pxParticle[nCnt].m_nDelay )
					{
						m_pxParticle[nCnt].m_nCurrDelay = 0;
						m_pxParticle[nCnt].m_nCurrFrame++;

						if ( m_pxParticle[nCnt].m_nCurrFrame >= _MAX_RAINDROPFRAME )
						{
							m_pxParticle[nCnt].m_nCurrFrame = 0;
						}
					}
					nPartCnt++;
				}
				continue;
			}

			UpdateAirFiction(nCnt);
			UpdateMove(nCnt);

			m_pxParticle[nCnt].m_nCurrDelay += nLoopTime;
			if ( m_pxParticle[nCnt].m_nCurrDelay > m_pxParticle[nCnt].m_nDelay )
			{
				m_pxParticle[nCnt].m_nCurrDelay = 0;
				m_pxParticle[nCnt].m_nCurrFrame++;

				if ( m_pxParticle[nCnt].m_nCurrFrame >= _MAX_RAINFRAME )
				{
					m_pxParticle[nCnt].m_nCurrFrame = 0;
				}
			}

			nPartCnt++;
		}
		if ( nPartCnt >= m_shPartNum )
		{
			return;
		}
    }
}




HRESULT CRain::RenderSystem(LPDIRECT3DDEVICE7 lpDevice)
{
	if ( lpDevice )
	{
		D3DMATRIX matWorldOriginal;
		D3DMATRIX matTrans;
		D3DMATRIX matScale;
		D3DMATRIX matRot;
		D3DMATRIX matWorld;
		D3DMATRIX matTmpWorld;
		D3DVECTOR vTrans;
		D3DMATERIAL7 mtrl;
		INT nPartCnt = 0;

		if( SUCCEEDED(lpDevice->BeginScene()) )
		{
			lpDevice->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
			{
				if ( !m_pxParticle[nCnt].m_bIsDead )
				{
					D3DUtil_InitMaterial(mtrl, 
										 (FLOAT)m_pxParticle[nCnt].m_bRed/255.0f,
										 (FLOAT)m_pxParticle[nCnt].m_bGreen/255.0f, 
										 (FLOAT)m_pxParticle[nCnt].m_bBlue/255.0f);
					mtrl.diffuse.a = 1.0f/255.0f;
					lpDevice->SetMaterial(&mtrl);
				
  					vTrans.x = (FLOAT) m_pxParticle[nCnt].m_vecPos.x-400;
					vTrans.y = (FLOAT)-m_pxParticle[nCnt].m_vecPos.y+300;
					vTrans.z = (FLOAT) m_pxParticle[nCnt].m_vecPos.z; 
					D3DUtil_SetScaleMatrix(matScale, 1.5f, m_pxParticle[nCnt].m_fSize, 1.0f);
					if ( (m_pxParticle[nCnt].m_vecPos.x - m_pxParticle[nCnt].m_vecOldPos.x) != 0 )
						D3DUtil_SetRotateZMatrix(matRot, (FLOAT)(g_PI/2 - atan((m_pxParticle[nCnt].m_vecPos.y - m_pxParticle[nCnt].m_vecOldPos.y)/(m_pxParticle[nCnt].m_vecPos.x - m_pxParticle[nCnt].m_vecOldPos.x))));
					else
						D3DUtil_SetRotateZMatrix(matRot, 0.0f);
					D3DUtil_SetTranslateMatrix(matTrans, vTrans);
					D3DMath_MatrixMultiply(matTmpWorld, matRot, matTrans);
					D3DMath_MatrixMultiply(matWorld, matScale, matTmpWorld);
					lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

					INT nCurrFrame;
					if( (m_pxParticle[nCnt].m_nCurrLife-m_pxParticle[nCnt].m_nLife) > 0 && (m_pxParticle[nCnt].m_nCurrLife-m_pxParticle[nCnt].m_nLife) < 510 )
					{
						D3DUtil_SetScaleMatrix(matScale, 32.0f, 32.0f, 1.0f);
						D3DUtil_SetTranslateMatrix(matTrans, vTrans);
						D3DMath_MatrixMultiply(matTmpWorld, matRot, matTrans);
						D3DMath_MatrixMultiply(matWorld, matScale, matTmpWorld);
						lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);
						nCurrFrame = 510+m_pxParticle[nCnt].m_nCurrFrame;
					}
					else
					{
						nCurrFrame = 500+m_pxParticle[nCnt].m_nCurrFrame;
					}

					SetBlendRenderState(lpDevice, _BLEND_LIGHTINV, &mtrl);

					LPDIRECTDRAWSURFACE7 lpddsParticleTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_PARTICLE, _IMAGE_PROGUSE, nCurrFrame);
					lpDevice->SetTexture(0, lpddsParticleTextr);

					lpDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avShape, 4, NULL);

					ResetBlendenderState(g_xMainWnd.Get3DDevice());

					lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);
					nPartCnt++;
				}
				if ( nPartCnt >= m_shPartNum )
				{
					break;
				}
			}

			lpDevice->EndScene();

			return S_OK;
		}
	}
	return E_FAIL;
}


VOID CRain::SetParticleDefault(INT nNum, D3DVECTOR vecGenPos)
{
	// m_bRainIntensity ---> 비의 강도가 심해질수록 gencnt, mass, size, delay, velocity등에 영향을 미친다.


	ZeroMemory(&m_pxParticle[nNum], sizeof(CParticle));
    m_pxParticle[nNum].m_vecPos		= D3DVECTOR((FLOAT)GetRandomNum(-100, (INT)(m_fWidth+100))/*(-400, 1200)*/, (FLOAT)GetRandomNum(-500, 0), 0.0f);
    m_pxParticle[nNum].m_vecVel		= D3DVECTOR((FLOAT)/*GetRandomNum(0,  10)*/0, 500/*(FLOAT)GetRandomNum(10, 30)*/, 0.0f);
//	m_pxParticle[nNum].m_vecAccel	= D3DVECTOR(0.0f, 0.0f, 0.0f);
//	m_pxParticle[nNum].m_vecOldPos	= D3DVECTOR(0.0f, 0.0f, 0.0f);
//	m_pxParticle[nNum].m_vecLocalForce = D3DVECTOR(0.0f, 0.0f, 0.0f);
	m_pxParticle[nNum].m_nLife		= GetRandomNum(800, 1400);
	m_pxParticle[nNum].m_fMass		= 100.0f;
	m_pxParticle[nNum].m_fSize		= (FLOAT)GetRandomNum(3, 30) + _RAND_FLOAT;
//	m_pxParticle[nNum].m_nLife		= (FLOAT)GetRandomNum((BYTE)m_pxParticle[nNum].m_fSize*2000,  6000);
//	m_pxParticle[nNum].m_bIsDead	= FALSE;
	m_pxParticle[nNum].m_bRed		= m_pxParticle[nNum].m_bGreen = m_pxParticle[nNum].m_bBlue = (BYTE)GetRandomNum(/*(BYTE)(m_pxParticle[nNum].m_fSize)*30+20*/120, 180);
	m_pxParticle[nNum].m_bBlue		= 125;
//	m_pxParticle[nNum].m_bRed		= (FLOAT)GetRandomNum(0, 255);
//	m_pxParticle[nNum].m_bGreen		= (FLOAT)GetRandomNum(0, 255);
//	m_pxParticle[nNum].m_bBlue		= (FLOAT)GetRandomNum(0, 255);
	m_pxParticle[nNum].m_nDelay		= GetRandomNum(50, 150);
//	m_pxParticle[nNum].m_nCurrLife	= 0;
//	m_pxParticle[nNum].m_nCurrDelay = 0;
//	m_pxParticle[nNum].m_nCurrFrame = 0;
//	m_pxParticle[nNum].m_bOpa		= 255;
}






/******************************************************************************************************************

	CFly Class	

*******************************************************************************************************************/
CFly::CFly()
{
	InitSystem();
}


CFly::~CFly()
{
	DestroySystem();
}


VOID CFly::InitSystem()
{
	CParticleSystem::InitSystem();
	m_bGenCnt = 3;
}


VOID CFly::DestroySystem()
{
	CParticleSystem::DestroySystem();

	InitSystem();
}


VOID CFly::SetupSystem(WORD wCnt)
{
	InitSystem();
	CParticleSystem::SetupSystem(wCnt);
	SetEnvFactor(-0.05f, D3DVECTOR(100, 1000, 0));
}


VOID CFly::UpdateSystem(INT nLoopTime, D3DVECTOR vecGenPos)
{
	BYTE bRate;
	INT nGenCnt = 0; 

	INT nSpeedRate = (nLoopTime / 17);
	if ( nSpeedRate < 1 ) 		
		nSpeedRate = 1;

	m_fDeltaTime = 0.02f*nSpeedRate;

    for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
    {
		m_pxParticle[nCnt].m_nCurrLife += nLoopTime;

		if ( m_pxParticle[nCnt].m_nCurrLife > m_pxParticle[nCnt].m_nLife )
		{
			m_pxParticle[nCnt].m_bIsDead = TRUE;
		}
		else
		{
			m_pxParticle[nCnt].m_nCurrDelay += nLoopTime;
			if ( m_pxParticle[nCnt].m_nCurrDelay > m_pxParticle[nCnt].m_nDelay )
			{
				m_pxParticle[nCnt].m_nCurrDelay = 0;
				m_pxParticle[nCnt].m_nCurrFrame++;

				m_pxParticle[nCnt].m_fSize += 0.5f;


				if ( m_pxParticle[nCnt].m_nCurrFrame >= _MAX_FLYFRAME )
				{
					m_pxParticle[nCnt].m_nCurrFrame = 0;
				}
			}

/*			bRate = 255 - 255*(FLOAT)((FLOAT)m_pxParticle[nCnt].m_nCurrLife/(FLOAT)m_pxParticle[nCnt].m_nLife);
			m_pxParticle[nCnt].m_bRed = m_pxParticle[nCnt].m_bGreen = m_pxParticle[nCnt].m_bBlue = bRate;
*/			
			if ( m_pxParticle[nCnt].m_nLife == 0 )
			{
				m_pxParticle[nCnt].m_nLife = 1;
			}

			bRate = (BYTE)(m_pxParticle[nCnt].m_bFstRed - m_pxParticle[nCnt].m_bFstRed*(FLOAT)((FLOAT)m_pxParticle[nCnt].m_nCurrLife/(FLOAT)m_pxParticle[nCnt].m_nLife));
			m_pxParticle[nCnt].m_bRed	= bRate;
			bRate = (BYTE)(m_pxParticle[nCnt].m_bFstGreen - m_pxParticle[nCnt].m_bFstGreen*(FLOAT)((FLOAT)m_pxParticle[nCnt].m_nCurrLife/(FLOAT)m_pxParticle[nCnt].m_nLife));
			m_pxParticle[nCnt].m_bGreen = bRate;
			bRate = (BYTE)(m_pxParticle[nCnt].m_bFstBlue - m_pxParticle[nCnt].m_bFstBlue*(FLOAT)((FLOAT)m_pxParticle[nCnt].m_nCurrLife/(FLOAT)m_pxParticle[nCnt].m_nLife));
			m_pxParticle[nCnt].m_bBlue	= bRate;

			UpdateAirFiction(nCnt);
			UpdateMove(nCnt);
		}

		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			if ( nGenCnt < m_bGenCnt )
			{
				SetParticleDefault(nCnt, vecGenPos);
				nGenCnt++;
			}
		}
    }
}


HRESULT CFly::RenderSystem(LPDIRECT3DDEVICE7 lpDevice)
{
	if ( lpDevice )
	{
		D3DMATRIX matWorldOriginal;
		D3DMATRIX matTrans;
		D3DMATRIX matScale;
		D3DMATRIX matWorld;
		D3DVECTOR vTrans;
		D3DMATERIAL7 mtrl;

		if( SUCCEEDED(lpDevice->BeginScene()) )
		{
			lpDevice->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
			{
				if ( !m_pxParticle[nCnt].m_bIsDead )
				{
					D3DUtil_InitMaterial(mtrl, 
										 (FLOAT)m_pxParticle[nCnt].m_bRed/255.0f,
										 (FLOAT)m_pxParticle[nCnt].m_bGreen/255.0f, 
										 (FLOAT)m_pxParticle[nCnt].m_bBlue/255.0f);
					mtrl.diffuse.a = 1.0f/255.0f;
					lpDevice->SetMaterial(&mtrl);

  					vTrans.x = (FLOAT) m_pxParticle[nCnt].m_vecPos.x-400;
					vTrans.y = (FLOAT)-m_pxParticle[nCnt].m_vecPos.y+300;
					vTrans.z = (FLOAT) m_pxParticle[nCnt].m_vecPos.z; 
					D3DUtil_SetScaleMatrix(matScale, m_pxParticle[nCnt].m_fSize, m_pxParticle[nCnt].m_fSize, 1);
					D3DUtil_SetTranslateMatrix(matTrans, vTrans);
					D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
					lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);
				
					lpDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
					lpDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, TRUE);
					lpDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
					lpDevice->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
					lpDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
					lpDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
					lpDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

					LPDIRECTDRAWSURFACE7 lpddsParticleTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_PARTICLE, _IMAGE_PROGUSE, 520+m_pxParticle[nCnt].m_nCurrFrame);
					lpDevice->SetTexture(0, lpddsParticleTextr);
					lpDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avShape, 4, NULL);

					lpDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
					lpDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);
					lpDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND , D3DBLEND_ONE);
					lpDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
					lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

					lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);
				}
			}
			lpDevice->EndScene();

			return S_OK;
		}
	}
	return E_FAIL;
}


VOID CFly::SetParticleDefault(INT nNum, D3DVECTOR vecGenPos)
{
	// m_bRainIntensity ---> 비의 강도가 심해질수록 gencnt, mass, size, delay, velocity등에 영향을 미친다.

	ZeroMemory(&m_pxParticle[nNum], sizeof(CParticle));
    m_pxParticle[nNum].m_vecPos		= vecGenPos;
    m_pxParticle[nNum].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-30, 30), (FLOAT)GetRandomNum(-20, 40), 0.0f);
	m_pxParticle[nNum].m_nLife		= GetRandomNum(500, 1500);
	m_pxParticle[nNum].m_fMass		= 1000.0f;
	m_pxParticle[nNum].m_fSize		= (FLOAT)GetRandomNum(5, 40) + _RAND_FLOAT;
//	m_pxParticle[nNum].m_nLife		= (FLOAT)GetRandomNum((BYTE)m_pxParticle[nNum].m_fSize*2000,  6000);
//	m_pxParticle[nNum].m_bIsDead	= FALSE;
	m_pxParticle[nNum].m_bRed		= m_pxParticle[nNum].m_bFstRed   = (BYTE)GetRandomNum(200, 255);
	m_pxParticle[nNum].m_bGreen		= m_pxParticle[nNum].m_bFstGreen = (BYTE)(m_pxParticle[nNum].m_bFstRed/2);//(FLOAT)GetRandomNum(0, 125);
	m_pxParticle[nNum].m_bBlue		= m_pxParticle[nNum].m_bFstBlue  = (BYTE)GetRandomNum(0, 30);
	m_pxParticle[nNum].m_nDelay		= GetRandomNum(200, 300);

//	m_pxParticle[nNum].m_nCurrLife	= 0;
//	m_pxParticle[nNum].m_nCurrDelay = 0;
//	m_pxParticle[nNum].m_nCurrFrame = 0;
//	m_pxParticle[nNum].m_bOpa		= 255;
}








/******************************************************************************************************************

	CBoom Class	

*******************************************************************************************************************/
CBoom::CBoom()
{
	InitSystem();
}


CBoom::~CBoom()
{
	DestroySystem();
}


VOID CBoom::InitSystem()
{
	CParticleSystem::InitSystem();
	m_shPartNum = 0;
}


VOID CBoom::DestroySystem()
{
	CParticleSystem::DestroySystem();

	InitSystem();
}


VOID CBoom::SetupSystem(WORD wCnt)
{
	InitSystem();
	CParticleSystem::SetupSystem(wCnt);
	SetEnvFactor(-0.05f, D3DVECTOR(0, 200, 0));
}


VOID CBoom::UpdateSystem(INT nLoopTime, D3DVECTOR vecGenPos)
{
	INT nSpeedRate = (nLoopTime / 17);
	INT nPartCnt = 0;

	if ( nSpeedRate < 1 ) 		
		nSpeedRate = 1;

	m_fDeltaTime = 0.02f*nSpeedRate;

    for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
    {
		if ( !m_pxParticle[nCnt].m_bIsDead )
		{
			m_pxParticle[nCnt].m_nCurrLife += nLoopTime;

			if ( m_pxParticle[nCnt].m_nCurrLife > m_pxParticle[nCnt].m_nLife )
			{
				m_pxParticle[nCnt].Init();
				m_shPartNum--;
				nPartCnt--;
			}
			else
			{
				m_pxParticle[nCnt].m_nCurrDelay += nLoopTime;

				m_pxParticle[nCnt].m_fMass		+= 3.0f;

				if ( m_pxParticle[nCnt].m_fSize < 0 )
					m_pxParticle[nCnt].m_fSize = 0;

				if ( m_pxParticle[nCnt].m_nCurrDelay > m_pxParticle[nCnt].m_nDelay )
				{
					m_pxParticle[nCnt].m_nCurrDelay = 0;
					m_pxParticle[nCnt].m_nCurrFrame++;

					if ( m_pxParticle[nCnt].m_nCurrFrame >= _MAX_BOOMFRAME )
					{
						m_pxParticle[nCnt].m_nCurrFrame = 0;
					}
				}

				if ( m_pxParticle[nCnt].m_nLife == 0 )
				{
					m_pxParticle[nCnt].m_nLife = 1;
				}

				m_pxParticle[nCnt].m_fSize = m_pxParticle[nCnt].m_fOriSize - m_pxParticle[nCnt].m_fOriSize*(FLOAT)((FLOAT)m_pxParticle[nCnt].m_nCurrLife/(FLOAT)m_pxParticle[nCnt].m_nLife);

				UpdateAirFiction(nCnt);
				UpdateMove(nCnt);
				nPartCnt++;
			}
		}
		if ( nPartCnt >= m_shPartNum )
		{
			return;
		}
    }
}


HRESULT CBoom::RenderSystem(LPDIRECT3DDEVICE7 lpDevice)
{
	INT nPartCnt = 0;
	if ( lpDevice )
	{
		D3DMATRIX matWorldOriginal;
		D3DMATRIX matTrans;
		D3DMATRIX matScale;
		D3DMATRIX matWorld;
		D3DVECTOR vTrans;
		D3DMATERIAL7 mtrl;

		if( SUCCEEDED(lpDevice->BeginScene()) )
		{
			lpDevice->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
			{
				if ( !m_pxParticle[nCnt].m_bIsDead )
				{
					D3DUtil_InitMaterial(mtrl, 
										 (FLOAT)m_pxParticle[nCnt].m_bRed/255.0f,
										 (FLOAT)m_pxParticle[nCnt].m_bGreen/255.0f, 
										 (FLOAT)m_pxParticle[nCnt].m_bBlue/255.0f);
					mtrl.diffuse.a = 1.0f/255.0f;
					lpDevice->SetMaterial(&mtrl);
				
  					vTrans.x = (FLOAT) m_pxParticle[nCnt].m_vecPos.x-400;
					vTrans.y = (FLOAT)-m_pxParticle[nCnt].m_vecPos.y+300;
					vTrans.z = (FLOAT) m_pxParticle[nCnt].m_vecPos.z; 
					D3DUtil_SetScaleMatrix(matScale, m_pxParticle[nCnt].m_fSize, m_pxParticle[nCnt].m_fSize, 1.0f);
					D3DUtil_SetTranslateMatrix(matTrans, vTrans);
					D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
					lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

					lpDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
					lpDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, TRUE);
					lpDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
					lpDevice->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
					lpDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
					lpDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
					lpDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

					LPDIRECTDRAWSURFACE7 lpddsParticleTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_PARTICLE, _IMAGE_PROGUSE, 520+m_pxParticle[nCnt].m_nCurrFrame);
					lpDevice->SetTexture(0, lpddsParticleTextr);
					lpDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avShape, 4, NULL);

					lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

					lpDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
					lpDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);
					lpDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND , D3DBLEND_ONE);
					lpDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
					lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);
					nPartCnt++;
				}
				if ( nPartCnt >= m_shPartNum )
				{
					break;
				}
			}
			lpDevice->EndScene();

			return S_OK;
		}
	}
	return E_FAIL;
}


VOID CBoom::SetBoomParticle(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			SetParticleDefault(nCnt, vecGenPos);
			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 1 )
//			if ( nGenCnt > 10 )
				return;
		}
	}

/*	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
//			vecGenPos.x += GetRandomNum(-2, 2);
//			vecGenPos.y += GetRandomNum(-2, 2);
//			vecGenPos.z += GetRandomNum(-10, 10);
			SetParticleDefault(nCnt, vecGenPos);
		}
	}
*/
}

VOID CBoom::SetBoomParticle2(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			SetParticleDefault2(nCnt, vecGenPos);
			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 20 )
				return;
		}
	}
}

VOID CBoom::SetBoomParticle3(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;

	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= vecGenPos;
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-300, 300), (FLOAT)GetRandomNum(-300, 150), 0.0f);
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(300, 1600);
			m_pxParticle[nCnt].m_fMass		= 10.0f;
			m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = (FLOAT)GetRandomNum(2, 2) + _RAND_FLOAT;

			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed	= (BYTE)GetRandomNum( 30,  60);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen= (BYTE)GetRandomNum(130, 160);
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue	= (BYTE)GetRandomNum(130, 160);

			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(200, 300);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 20 )
				return;
		}
	}
}

VOID CBoom::SetBoomParticle4(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			SetParticleDefault3(nCnt, vecGenPos);
			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 10 )
				return;
		}
	}
}

VOID CBoom::SetBoomParticle5(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			SetParticleDefault2(nCnt, vecGenPos);
			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 5 )
				return;
		}
	}
}

VOID CBoom::SetBoomParticle6(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < 600; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			SetParticleDefault2(nCnt, vecGenPos);
/*
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= vecGenPos;
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-80, 80), (FLOAT)GetRandomNum(-180, 10), 0.0f);
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(800, 1200);
			m_pxParticle[nCnt].m_fMass		= 5.0f;
			m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = (FLOAT)GetRandomNum(4, 5) + _RAND_FLOAT;

			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed	= (BYTE)GetRandomNum( 120, 130);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen= (BYTE)GetRandomNum( 200, 210);
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue	= (BYTE)GetRandomNum( 230, 240);

			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(200, 300);
*/
			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 5 )
				return;
		}
	}
}


VOID CBoom::SetParticleDefault(INT nNum, D3DVECTOR vecGenPos)
{
/*	ZeroMemory(&m_pxParticle[nNum], sizeof(CParticle));
    m_pxParticle[nNum].m_vecPos		= vecGenPos;
    m_pxParticle[nNum].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-75, 75), (FLOAT)GetRandomNum(-180, -50), 0.0f);
	m_pxParticle[nNum].m_nLife		= GetRandomNum(800, 1200);
	m_pxParticle[nNum].m_fMass		= 1.0f;
	m_pxParticle[nNum].m_fSize		= m_pxParticle[nNum].m_fOriSize = (FLOAT)GetRandomNum(5, 40) + _RAND_FLOAT;
	m_pxParticle[nNum].m_bRed		= m_pxParticle[nNum].m_bFstRed   = (BYTE)GetRandomNum(0, 255);
	m_pxParticle[nNum].m_bGreen		= m_pxParticle[nNum].m_bFstGreen = (BYTE)(m_pxParticle[nNum].m_bFstRed/2);
	m_pxParticle[nNum].m_bBlue		= m_pxParticle[nNum].m_bFstBlue  = 0;
	m_pxParticle[nNum].m_nDelay		= GetRandomNum(200, 300);
*/
	ZeroMemory(&m_pxParticle[nNum], sizeof(CParticle));
    m_pxParticle[nNum].m_vecPos		= vecGenPos;
    m_pxParticle[nNum].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-75, 75), (FLOAT)GetRandomNum(-180, -50), 0.0f);
	m_pxParticle[nNum].m_nLife		= GetRandomNum(800, 1200);
	m_pxParticle[nNum].m_fMass		= 1.0f;
	m_pxParticle[nNum].m_fSize		= m_pxParticle[nNum].m_fOriSize = (FLOAT)GetRandomNum(2, 10) + _RAND_FLOAT;
	m_pxParticle[nNum].m_bRed		= m_pxParticle[nNum].m_bFstRed   = (BYTE)GetRandomNum( 50, 100);
	m_pxParticle[nNum].m_bGreen		= m_pxParticle[nNum].m_bFstGreen = (BYTE)GetRandomNum(100, 200);
	m_pxParticle[nNum].m_bBlue		= m_pxParticle[nNum].m_bFstBlue  = (BYTE)GetRandomNum(200, 255);
	m_pxParticle[nNum].m_nDelay		= GetRandomNum(200, 300);
}

VOID CBoom::SetParticleDefault2(INT nNum, D3DVECTOR vecGenPos)
{
	ZeroMemory(&m_pxParticle[nNum], sizeof(CParticle));
    m_pxParticle[nNum].m_vecPos		= vecGenPos;
    m_pxParticle[nNum].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-175, 175), (FLOAT)GetRandomNum(-180, 10), 0.0f);
	m_pxParticle[nNum].m_nLife		= GetRandomNum(800, 2000);
	m_pxParticle[nNum].m_fMass		= 1.0f;
	m_pxParticle[nNum].m_fSize		= m_pxParticle[nNum].m_fOriSize = (FLOAT)GetRandomNum(6, 7) + _RAND_FLOAT;

	m_pxParticle[nNum].m_bRed		= m_pxParticle[nNum].m_bFstRed	= (BYTE)GetRandomNum( 40, 50);
	m_pxParticle[nNum].m_bGreen		= m_pxParticle[nNum].m_bFstGreen= (BYTE)GetRandomNum( 40, 50);
	m_pxParticle[nNum].m_bBlue		= m_pxParticle[nNum].m_bFstBlue	= (BYTE)GetRandomNum( 40, 50);

	m_pxParticle[nNum].m_nDelay		= GetRandomNum(200, 300);
}

VOID CBoom::SetParticleDefault3(INT nNum, D3DVECTOR vecGenPos)
{
	ZeroMemory(&m_pxParticle[nNum], sizeof(CParticle));
    m_pxParticle[nNum].m_vecPos		= vecGenPos;
    m_pxParticle[nNum].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-120, 120), (FLOAT)GetRandomNum(-180, 0), 0.0f);
	m_pxParticle[nNum].m_nLife		= GetRandomNum(200, 1200);
	m_pxParticle[nNum].m_fMass		= 1.0f;
	m_pxParticle[nNum].m_fSize		= m_pxParticle[nNum].m_fOriSize = (FLOAT)GetRandomNum(3, 12) + _RAND_FLOAT;

	m_pxParticle[nNum].m_bRed		= m_pxParticle[nNum].m_bFstRed	= (BYTE)GetRandomNum( 40, 50);
	m_pxParticle[nNum].m_bGreen		= m_pxParticle[nNum].m_bFstGreen= (BYTE)GetRandomNum( 40, 50);
	m_pxParticle[nNum].m_bBlue		= m_pxParticle[nNum].m_bFstBlue	= (BYTE)GetRandomNum( 40, 50);

	m_pxParticle[nNum].m_nDelay		= GetRandomNum(200, 300);
}











/******************************************************************************************************************

	CFlyingTail Class	

*******************************************************************************************************************/
CFlyingTail::CFlyingTail()
{
	InitSystem();
}


CFlyingTail::~CFlyingTail()
{
	DestroySystem();
}


VOID CFlyingTail::InitSystem()
{
	CParticleSystem::InitSystem();
	m_shPartNum = 0;
}


VOID CFlyingTail::DestroySystem()
{
	CParticleSystem::DestroySystem();

	InitSystem();
}


VOID CFlyingTail::SetupSystem(WORD wCnt)
{
	InitSystem();
	CParticleSystem::SetupSystem(wCnt);
	SetEnvFactor(-0.05f, D3DVECTOR(100, 1000, 0));
}


VOID CFlyingTail::SetFlyTailParticle(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			SetParticleDefault(nCnt, vecGenPos);
			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 2 )
				return;
		}
	}
}

VOID CFlyingTail::SetFlyTailParticleEx(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;

//	CONST FLOAT rSinVal[8] = { 0.0f, 0.707107f, 1.0f, 0.707107f, 0.0f, -0.707107f, -1.0f, -0.707107f };
//	CONST FLOAT rCosVal[8] = { 1.0f, 0.707107f, 0.0f, -0.707107f, -1.0f, -0.707107f, 0.0f, 0.707107f };
//	m_pxParticle[nCnt].m_vecPos	= D3DVECTOR(vecGenPos.x+rCosVal[nGenCnt]*20, vecGenPos.y+(FLOAT)+rSinVal[nGenCnt]*20, 0.0f);

	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= D3DVECTOR(vecGenPos.x+(FLOAT)GetRandomNum(-10, 10), vecGenPos.y+(FLOAT)GetRandomNum(-10, 10), 0.0f);
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-150, 150), (FLOAT)GetRandomNum(-80, 150), 0.0f);
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(200, 1200);
			m_pxParticle[nCnt].m_fMass		= 1000.0f;
			m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = (FLOAT)GetRandomNum(5, 10) + _RAND_FLOAT;
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed	= (BYTE)GetRandomNum(100, 110);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen= (BYTE)GetRandomNum(100, 110);
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue	= (BYTE)GetRandomNum(245, 255);
			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(200, 300);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 1 )
				return;
		}
	}
}

VOID CFlyingTail::SetFlyTailParticleEx2(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;

	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= D3DVECTOR(vecGenPos.x+(FLOAT)GetRandomNum(-10, 10), vecGenPos.y+(FLOAT)GetRandomNum(-10, 10), 0.0f);
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-30, 30), (FLOAT)GetRandomNum(-30, 30), 0.0f);
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(200, 1200);
			m_pxParticle[nCnt].m_fMass		= 1000.0f;
			m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = (FLOAT)GetRandomNum(3, 7) + _RAND_FLOAT;
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed	= (BYTE)GetRandomNum(100, 150);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen= (BYTE)GetRandomNum(150, 255);
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue	= (BYTE)GetRandomNum(100, 150);
			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(200, 300);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 2 )
				return;
		}
	}
}

VOID CFlyingTail::SetFlyTailParticleEx3(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;

	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= vecGenPos;
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-50, 50), (FLOAT)GetRandomNum(-30, 60), 0.0f);
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(500, 900);
			m_pxParticle[nCnt].m_fMass		= 1000.0f;
			m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = (FLOAT)GetRandomNum(3, 5) + _RAND_FLOAT;
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed   = (BYTE)GetRandomNum(200, 255);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen = (BYTE)(m_pxParticle[nCnt].m_bFstRed/2);//(FLOAT)GetRandomNum(0, 125);
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue  = (BYTE)GetRandomNum(0, 30);
			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(200, 300);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 4 )
				return;
		}
	}
}

VOID CFlyingTail::SetFlyTailParticleEx4(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= vecGenPos;
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-50, 50), (FLOAT)GetRandomNum(-30, 60), 0.0f);
		
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(20, 500);

			m_pxParticle[nCnt].m_fMass		= 10000.0f;
			m_pxParticle[nCnt].m_fSize		= (FLOAT)GetRandomNum(5, 15) + _RAND_FLOAT;
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed   = (BYTE)GetRandomNum(70, 90);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen = (BYTE)GetRandomNum(70, 90);
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue  = (BYTE)GetRandomNum(100, 150);
			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(0, 10);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 2 )
				return;
		}
	}
}

VOID CFlyingTail::SetFlyTailParticleEx5(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= vecGenPos;
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-45, 45), (FLOAT)GetRandomNum(-150, -250), 0.0f);
		
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(1000, 1600);

			m_pxParticle[nCnt].m_fMass		= 100.0f;
			m_pxParticle[nCnt].m_fSize		= 4.0f;
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed   = 255;
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen = 125;;
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue  = 0;
			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(200, 300);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 2 )
				return;
		}
	}
}

VOID CFlyingTail::UpdateSystem(INT nLoopTime, D3DVECTOR vecGenPos)
{
	BYTE bRate;
	INT  nSpeedRate, nPartCnt;
	
	nPartCnt = 0;

	nSpeedRate = (nLoopTime / 17);

	if ( nSpeedRate < 1 ) 	nSpeedRate = 1;

	m_fDeltaTime = 0.02f*nSpeedRate;

    for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
    {
		if ( !m_pxParticle[nCnt].m_bIsDead )
		{
			m_pxParticle[nCnt].m_nCurrLife += nLoopTime;

			if ( m_pxParticle[nCnt].m_nCurrLife > m_pxParticle[nCnt].m_nLife )
			{				
				m_pxParticle[nCnt].Init();
				m_shPartNum--;
				nPartCnt--;
			}
			else
			{
				m_pxParticle[nCnt].m_nCurrDelay += nLoopTime;
				if ( m_pxParticle[nCnt].m_nCurrDelay > m_pxParticle[nCnt].m_nDelay )
				{
					m_pxParticle[nCnt].m_nCurrDelay = 0;
					m_pxParticle[nCnt].m_nCurrFrame++;

					if ( m_pxParticle[nCnt].m_nCurrFrame >= _MAX_FLYTAILFRAME )
					{
						m_pxParticle[nCnt].m_nCurrFrame = 0;
					}
				}

				if ( m_pxParticle[nCnt].m_nLife == 0 )
				{
					m_pxParticle[nCnt].m_nLife = 1;
				}

				bRate = (BYTE)(m_pxParticle[nCnt].m_bFstRed - m_pxParticle[nCnt].m_bFstRed*(FLOAT)((FLOAT)m_pxParticle[nCnt].m_nCurrLife/(FLOAT)m_pxParticle[nCnt].m_nLife));
				m_pxParticle[nCnt].m_bRed	= bRate;
				bRate = (BYTE)(m_pxParticle[nCnt].m_bFstGreen - m_pxParticle[nCnt].m_bFstGreen*(FLOAT)((FLOAT)m_pxParticle[nCnt].m_nCurrLife/(FLOAT)m_pxParticle[nCnt].m_nLife));
				m_pxParticle[nCnt].m_bGreen = bRate;
				bRate = (BYTE)(m_pxParticle[nCnt].m_bFstBlue - m_pxParticle[nCnt].m_bFstBlue*(FLOAT)((FLOAT)m_pxParticle[nCnt].m_nCurrLife/(FLOAT)m_pxParticle[nCnt].m_nLife));
				m_pxParticle[nCnt].m_bBlue	= bRate;

				UpdateAirFiction(nCnt);
				UpdateMove(nCnt);
				nPartCnt++;
			}
		}
		if ( nPartCnt >= m_shPartNum )
		{
			return;
		}
    }
}


HRESULT CFlyingTail::RenderSystem(LPDIRECT3DDEVICE7 lpDevice)
{
	INT  nPartCnt;
	
	nPartCnt = 0;

	if ( lpDevice )
	{
		LPDIRECTDRAWSURFACE7 lpddsParticleTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_PARTICLE, _IMAGE_PROGUSE, 520);

		D3DMATRIX matWorldOriginal;
		D3DMATRIX matTrans;
		D3DMATRIX matScale;
		D3DMATRIX matWorld;
		D3DVECTOR vTrans;
		D3DMATERIAL7 mtrl;

		if( SUCCEEDED(lpDevice->BeginScene()) )
		{
			lpDevice->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
			{
				if ( !m_pxParticle[nCnt].m_bIsDead )
				{
					D3DUtil_InitMaterial(mtrl, 
										 (FLOAT)m_pxParticle[nCnt].m_bRed/255.0f,
										 (FLOAT)m_pxParticle[nCnt].m_bGreen/255.0f, 
										 (FLOAT)m_pxParticle[nCnt].m_bBlue/255.0f);
					mtrl.diffuse.a = 1.0f/255.0f;
					lpDevice->SetMaterial(&mtrl);
				
 					vTrans.x = (FLOAT) m_pxParticle[nCnt].m_vecPos.x-400;
					vTrans.y = (FLOAT)-m_pxParticle[nCnt].m_vecPos.y+300;
					vTrans.z = (FLOAT) m_pxParticle[nCnt].m_vecPos.z; 

					D3DUtil_SetScaleMatrix(matScale, m_pxParticle[nCnt].m_fSize, m_pxParticle[nCnt].m_fSize, 1.0f);
					D3DUtil_SetTranslateMatrix(matTrans, vTrans);
					D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
					lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

					lpDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
					lpDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, TRUE);
					lpDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
					lpDevice->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
					lpDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
					lpDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
					lpDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

					lpDevice->SetTexture(0, lpddsParticleTextr);
					lpDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avShape, 4, NULL);

					lpDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
					lpDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);
					lpDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND , D3DBLEND_ONE);
					lpDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
					lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

					lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);
					nPartCnt++;
				}
				if ( nPartCnt >= m_shPartNum )
				{
					break;
				}
			}

			lpDevice->EndScene();

			return S_OK;
		}
	}
	return E_FAIL;
}


VOID CFlyingTail::SetParticleDefault(INT nNum, D3DVECTOR vecGenPos)
{
	ZeroMemory(&m_pxParticle[nNum], sizeof(CParticle));
    m_pxParticle[nNum].m_vecPos		= vecGenPos;
    m_pxParticle[nNum].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-50, 50), (FLOAT)GetRandomNum(-30, 60), 0.0f);

//	m_pxParticle[nNum].m_nLife		= (FLOAT)GetRandomNum(500, 1000);
	m_pxParticle[nNum].m_nLife		= GetRandomNum(150, 400);

	m_pxParticle[nNum].m_fMass		= 1000.0f;
	m_pxParticle[nNum].m_fSize		= (FLOAT)GetRandomNum(5, 15) + _RAND_FLOAT;
	m_pxParticle[nNum].m_bRed		= m_pxParticle[nNum].m_bFstRed   = (BYTE)GetRandomNum(200, 255);
	m_pxParticle[nNum].m_bGreen		= m_pxParticle[nNum].m_bFstGreen = (BYTE)(m_pxParticle[nNum].m_bFstRed/2);//(FLOAT)GetRandomNum(0, 125);
	m_pxParticle[nNum].m_bBlue		= m_pxParticle[nNum].m_bFstBlue  = (BYTE)GetRandomNum(0, 30);
/*
	m_pxParticle[nNum].m_bRed		= m_pxParticle[nNum].m_bFstRed   = (FLOAT)GetRandomNum(200, 255);
	m_pxParticle[nNum].m_bGreen		= m_pxParticle[nNum].m_bFstGreen = (FLOAT)GetRandomNum(0, 150);
	m_pxParticle[nNum].m_bBlue		= m_pxParticle[nNum].m_bFstBlue  = (FLOAT)GetRandomNum(0, 150);
*/	m_pxParticle[nNum].m_nDelay		= GetRandomNum(200, 300);
}











/******************************************************************************************************************

	CSmoke Class	

*******************************************************************************************************************/
CSmoke::CSmoke()
{
	InitSystem();
}


CSmoke::~CSmoke()
{
	DestroySystem();
}


VOID CSmoke::InitSystem()
{
	CParticleSystem::InitSystem();
	m_shPartNum = 0;
}


VOID CSmoke::DestroySystem()
{
	CParticleSystem::DestroySystem();

	InitSystem();
}


VOID CSmoke::SetupSystem(WORD wCnt)
{
	InitSystem();
	CParticleSystem::SetupSystem(wCnt);
	SetEnvFactor(-0.05f, D3DVECTOR(0, 1000, 0));
}


VOID CSmoke::UpdateSystem(INT nLoopTime, D3DVECTOR vecGenPos)
{
	BYTE bRate;
	INT  nSpeedRate, nPartCnt;
	D3DVECTOR vecAddVel;
	
	nPartCnt = 0;

	nSpeedRate = (nLoopTime / 17);

	if ( nSpeedRate < 1 ) 	nSpeedRate = 1;

	m_fDeltaTime = 0.02f*nSpeedRate;

//	SetSmokeParticle(vecGenPos);

    for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
    {
		if ( !m_pxParticle[nCnt].m_bIsDead )
		{
			m_pxParticle[nCnt].m_nCurrLife += nLoopTime;

			if ( m_pxParticle[nCnt].m_nCurrLife > m_pxParticle[nCnt].m_nLife )
			{				
				m_pxParticle[nCnt].Init();
				m_shPartNum--;
				nPartCnt--;
			}
			else
			{
				m_pxParticle[nCnt].m_nCurrDelay += nLoopTime;
				if ( m_pxParticle[nCnt].m_nCurrDelay > m_pxParticle[nCnt].m_nDelay )
				{
					m_pxParticle[nCnt].m_nCurrDelay = 0;
					m_pxParticle[nCnt].m_nCurrFrame++;

					if ( m_pxParticle[nCnt].m_nCurrFrame >= _MAX_SMOKEFRAME )
					{
						m_pxParticle[nCnt].m_nCurrFrame = 0;
					}
				}

//				m_pxParticle[nCnt].m_fSize = m_pxParticle[nCnt].m_fOriSize + m_pxParticle[nCnt].m_fOriSize*15.0f*(FLOAT)((FLOAT)m_pxParticle[nCnt].m_nCurrLife/(FLOAT)m_pxParticle[nCnt].m_nLife);
//				vecAddVel = D3DVECTOR((FLOAT)GetRandomNum(-1, 1), GetRandomNum(-2, 0), 0.0f);

				if ( m_pxParticle[nCnt].m_nLife == 0 )
				{
					m_pxParticle[nCnt].m_nLife = 1;
				}

				m_pxParticle[nCnt].m_fSize = m_pxParticle[nCnt].m_fOriSize + m_pxParticle[nCnt].m_fOriSize*7.0f*(FLOAT)((FLOAT)m_pxParticle[nCnt].m_nCurrLife/(FLOAT)m_pxParticle[nCnt].m_nLife);
				vecAddVel = D3DVECTOR((FLOAT)GetRandomNum(-1, 1), 0.0f, 0.0f);
				m_pxParticle[nCnt].m_vecVel += vecAddVel;

				bRate = (BYTE)(m_pxParticle[nCnt].m_bFstRed - m_pxParticle[nCnt].m_bFstRed*(FLOAT)((FLOAT)m_pxParticle[nCnt].m_nCurrLife/(FLOAT)m_pxParticle[nCnt].m_nLife));
				m_pxParticle[nCnt].m_bRed	= bRate;
				bRate = (BYTE)(m_pxParticle[nCnt].m_bFstGreen - m_pxParticle[nCnt].m_bFstGreen*(FLOAT)((FLOAT)m_pxParticle[nCnt].m_nCurrLife/(FLOAT)m_pxParticle[nCnt].m_nLife));
				m_pxParticle[nCnt].m_bGreen = bRate;
				bRate = (BYTE)(m_pxParticle[nCnt].m_bFstBlue - m_pxParticle[nCnt].m_bFstBlue*(FLOAT)((FLOAT)m_pxParticle[nCnt].m_nCurrLife/(FLOAT)m_pxParticle[nCnt].m_nLife));
				m_pxParticle[nCnt].m_bBlue	= bRate;

				UpdateAirFiction(nCnt);
				UpdateMove(nCnt);
				nPartCnt++;
			}
		}
		if ( nPartCnt >= m_shPartNum )
			return;
    }
}


VOID CSmoke::SetSmokeParticle(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			SetParticleDefault(nCnt, vecGenPos);
			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 0 )
				return;
		}
	}
}


HRESULT CSmoke::RenderSystem(LPDIRECT3DDEVICE7 lpDevice)
{
	INT  nPartCnt;
	
	nPartCnt = 0;

	if ( lpDevice )
	{
		LPDIRECTDRAWSURFACE7 lpddsParticleTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_PARTICLE, _IMAGE_PROGUSE, 530);

		D3DMATRIX matWorldOriginal;
		D3DMATRIX matTrans;
		D3DMATRIX matScale;
		D3DMATRIX matWorld;
		D3DVECTOR vTrans;
		D3DMATERIAL7 mtrl;

		if( SUCCEEDED(lpDevice->BeginScene()) )
		{
			lpDevice->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
			{
				if ( !m_pxParticle[nCnt].m_bIsDead )
				{
					D3DUtil_InitMaterial(mtrl, 
										 (FLOAT)m_pxParticle[nCnt].m_bRed/255.0f,
										 (FLOAT)m_pxParticle[nCnt].m_bGreen/255.0f, 
										 (FLOAT)m_pxParticle[nCnt].m_bBlue/255.0f);
					mtrl.diffuse.a = 1.0f/255.0f;
					lpDevice->SetMaterial(&mtrl);
				
  					vTrans.x = (FLOAT) m_pxParticle[nCnt].m_vecPos.x-400;
					vTrans.y = (FLOAT)-m_pxParticle[nCnt].m_vecPos.y+300;
					vTrans.z = (FLOAT) m_pxParticle[nCnt].m_vecPos.z; 
					D3DUtil_SetScaleMatrix(matScale, m_pxParticle[nCnt].m_fSize, m_pxParticle[nCnt].m_fSize, 1.0f);
					D3DUtil_SetTranslateMatrix(matTrans, vTrans);
					D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
					lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

					SetBlendRenderState(lpDevice, _BLEND_LIGHTINV, &mtrl);

					lpDevice->SetTexture(0, lpddsParticleTextr);
					lpDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avShape, 4, NULL);
					
					ResetBlendenderState(lpDevice);

					lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);
					nPartCnt++;
				}
				if ( nPartCnt >= m_shPartNum )
				{
					break;
				}
			}

			lpDevice->EndScene();

			return S_OK;
		}
	}
	return E_FAIL;
}


VOID CSmoke::SetParticleDefault(INT nNum, D3DVECTOR vecGenPos)
{
	ZeroMemory(&m_pxParticle[nNum], sizeof(CParticle));
//	vecGenPos.x += (FLOAT)GetRandomNum(-5, 5);
//	vecGenPos.y += (FLOAT)GetRandomNum(-8, 2);
    m_pxParticle[nNum].m_vecPos		= vecGenPos;
    m_pxParticle[nNum].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-8, 8), 0.0f, 0.0f);
//	m_pxParticle[nNum].m_nLife		= (FLOAT)GetRandomNum(500, 1000);
	m_pxParticle[nNum].m_nLife		= GetRandomNum(150, 400);
	m_pxParticle[nNum].m_fMass		= 1000.0f;
//	m_pxParticle[nNum].m_fSize		= m_pxParticle[nNum].m_fOriSize = (FLOAT)GetRandomNum(5, 10) + _RAND_FLOAT;
	m_pxParticle[nNum].m_fSize		= m_pxParticle[nNum].m_fOriSize = (FLOAT)GetRandomNum(5, 10) + _RAND_FLOAT;
	m_pxParticle[nNum].m_bRed		= m_pxParticle[nNum].m_bFstRed = m_pxParticle[nNum].m_bGreen = m_pxParticle[nNum].m_bFstGreen = m_pxParticle[nNum].m_bBlue = m_pxParticle[nNum].m_bFstBlue = (BYTE)GetRandomNum(100, 150);
	m_pxParticle[nNum].m_nDelay		= GetRandomNum(200, 300);
}


VOID CSmoke::SetSmokeParticleEx(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= vecGenPos;
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-12, 12), 0.0f, 0.0f);
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(200, 1200);
			m_pxParticle[nCnt].m_fMass		= 1000.0f;
			m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = (FLOAT)GetRandomNum(20, 25) + _RAND_FLOAT;
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed	= (BYTE)GetRandomNum(80, 120);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen= (BYTE)GetRandomNum(80, 120);
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue	= (BYTE)GetRandomNum(220, 255);
			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(200, 300);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 0 )
				return;
		}
	}
}

VOID CSmoke::SetSmokeParticleEx2(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= vecGenPos;
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-20, 20), 0.0f, 0.0f);
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(400, 800);
			m_pxParticle[nCnt].m_fMass		= 1000.0f;
			m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = (FLOAT)GetRandomNum(20, 25) + _RAND_FLOAT;
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed	= (BYTE)GetRandomNum( 50, 100);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen= (BYTE)GetRandomNum( 50, 100);
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue	= (BYTE)GetRandomNum(255, 255);
			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(200, 300);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 0 )
				return;
		}
	}
}

VOID CSmoke::SetSmokeParticleEx3(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= vecGenPos;
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)0, 0.0f, 0.0f);
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(400, 500);
			m_pxParticle[nCnt].m_fMass		= 10000.0f;
			m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = 7.0f;
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed	= (BYTE)GetRandomNum(100, 150);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen= (BYTE)GetRandomNum(150, 200);
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue	= (BYTE)GetRandomNum(255, 255);
			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(200, 300);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 0 )
				return;
		}
	}
}

VOID CSmoke::SetSmokeParticleEx4(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= vecGenPos;
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-12, 12), (FLOAT)GetRandomNum(-120, -80), 0.0f);
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(300, 600);
			m_pxParticle[nCnt].m_fMass		= 1000.0f;
			m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = (FLOAT)GetRandomNum(10, 30);
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed	= (BYTE)GetRandomNum(100, 150);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen= (BYTE)GetRandomNum(150, 200);
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue	= (BYTE)GetRandomNum(255, 255);
			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(200, 300);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 0 )
				return;
		}
	}
}

VOID CSmoke::SetSmokeParticleEx5(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= vecGenPos;
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-2, 2), 0.0f, 0.0f);
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(200, 400);
			m_pxParticle[nCnt].m_fMass		= 1000.0f;
			m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = (FLOAT)GetRandomNum(8, 12) + _RAND_FLOAT;
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed	= (BYTE)GetRandomNum(220, 255);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen= (BYTE)GetRandomNum(140, 160);
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue	= (BYTE)GetRandomNum(60, 80);
			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(200, 300);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 0 )
				return;
		}
	}
}



VOID CSmoke::SetSmokeParticleEx6(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= vecGenPos;
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-30, 0), (FLOAT)GetRandomNum(-60, -60), 0.0f);
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(800, 1200);
			m_pxParticle[nCnt].m_fMass		= 2000.0f;
			m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = (FLOAT)GetRandomNum(20, 40);
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed	= (BYTE)GetRandomNum( 50, 50);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen= (BYTE)GetRandomNum( 50, 50);
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue	= (BYTE)GetRandomNum( 50, 50);
			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(200, 300);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 0 )
				return;
		}
	}

}

VOID CSmoke::SetSmokeParticleEx7(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= vecGenPos;
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR(-20.0f, -20.0f, 0.0f);
			m_pxParticle[nCnt].m_nLife		= 1000;
			m_pxParticle[nCnt].m_fMass		= 10000.0f;
			m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = 18.0f;
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed	= (BYTE)GetRandomNum(60, 70);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen= (BYTE)GetRandomNum(60, 70);
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue	= (BYTE)GetRandomNum(70, 80);
			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(200, 300);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 0 )
				return;
		}
	}
}

VOID CSmoke::SetSmokeParticleEx8(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= vecGenPos;
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-12, 12), 0.0f, 0.0f);
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(200, 400);
			m_pxParticle[nCnt].m_fMass		= 1000.0f;
			m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = (FLOAT)GetRandomNum(20, 20) + _RAND_FLOAT;
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed	= (BYTE)GetRandomNum(60, 70);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen= (BYTE)GetRandomNum(220, 230);
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue	= (BYTE)GetRandomNum(210, 220);
			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(200, 300);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 0 )
				return;
		}
	}
}



VOID CSmoke::SetSmokeParticleEx9(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= vecGenPos;
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-20, 0), (FLOAT)GetRandomNum(-90, -150), 0.0f);
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(1000, 3000);
			m_pxParticle[nCnt].m_fMass		= 2000.0f;
			m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = (FLOAT)GetRandomNum(8, 10) + _RAND_FLOAT;
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed  = m_pxParticle[nCnt].m_bGreen = m_pxParticle[nCnt].m_bFstGreen = m_pxParticle[nCnt].m_bBlue = m_pxParticle[nCnt].m_bFstBlue = (FLOAT)GetRandomNum(120, 150);
			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(200, 300);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 1 )
				return;
		}
	}
}


VOID CSmoke::SetSmokeParticleEx10(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= vecGenPos;
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-10, 10), (FLOAT)GetRandomNum(-80, 0), 0.0f);
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(800, 1200);
			m_pxParticle[nCnt].m_fMass		= 2000.0f;
			m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = (FLOAT)GetRandomNum(20, 40);
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed	= (BYTE)GetRandomNum( 50, 50);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen= (BYTE)GetRandomNum( 50, 50);
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue	= (BYTE)GetRandomNum( 50, 50);
			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(200, 300);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 0 )
				return;
		}
	}
}

VOID CSmoke::SetSmokeParticleEx11(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= vecGenPos;
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-55, 5), (FLOAT)GetRandomNum(-100, -50), 0.0f);
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(900, 1000);
			m_pxParticle[nCnt].m_fMass		= 2000.0f;
			m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = (FLOAT)GetRandomNum(20, 40);
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed	= (BYTE)GetRandomNum( 50, 50);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen= (BYTE)GetRandomNum( 50, 50);
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue	= (BYTE)GetRandomNum( 50, 50);
			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(200, 300);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 0 )
				return;
		}
	}
}

VOID CSmoke::SetSmokeParticleEx12(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
		//	vecGenPos.x += (FLOAT)GetRandomNum(-5, 5);
		//	vecGenPos.y += (FLOAT)GetRandomNum(-8, 2);
			m_pxParticle[nCnt].m_vecPos		= vecGenPos;
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-10, 10), 0.0f, 0.0f);
			m_pxParticle[nCnt].m_nLife		= (FLOAT)GetRandomNum(500, 500);
//			m_pxParticle[nCnt].m_nLife		= GetRandomNum(150, 400);
			m_pxParticle[nCnt].m_fMass		= 1000.0f;
		//	m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = (FLOAT)GetRandomNum(5, 10) + _RAND_FLOAT;
			m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = (FLOAT)GetRandomNum(10, 30) + _RAND_FLOAT;
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed = m_pxParticle[nCnt].m_bGreen = m_pxParticle[nCnt].m_bFstGreen = m_pxParticle[nCnt].m_bBlue = m_pxParticle[nCnt].m_bFstBlue = (BYTE)GetRandomNum(100, 150);
			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(200, 300);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 0 )
				return;
		}
	}
}


VOID CSmoke::SetSmokeParticleEx13(D3DVECTOR vecGenPos)
{
	INT nGenCnt = 0;
	for ( INT nCnt = 0; nCnt < m_nNum; nCnt++ )
	{
		if ( m_pxParticle[nCnt].m_bIsDead )
		{
			ZeroMemory(&m_pxParticle[nCnt], sizeof(CParticle));
			m_pxParticle[nCnt].m_vecPos		= vecGenPos;
			m_pxParticle[nCnt].m_vecVel		= D3DVECTOR((FLOAT)GetRandomNum(-30, 0), (FLOAT)GetRandomNum(-130, -100), 0.0f);
			m_pxParticle[nCnt].m_nLife		= GetRandomNum(800, 900);
			m_pxParticle[nCnt].m_fMass		= 1000.0f;
			m_pxParticle[nCnt].m_fSize		= m_pxParticle[nCnt].m_fOriSize = (FLOAT)GetRandomNum(20, 30);
			m_pxParticle[nCnt].m_bRed		= m_pxParticle[nCnt].m_bFstRed	= (BYTE)GetRandomNum( 0, 10);
			m_pxParticle[nCnt].m_bGreen		= m_pxParticle[nCnt].m_bFstGreen= (BYTE)GetRandomNum( 65, 75);
			m_pxParticle[nCnt].m_bBlue		= m_pxParticle[nCnt].m_bFstBlue	= (BYTE)GetRandomNum( 140, 150);
			m_pxParticle[nCnt].m_nDelay		= GetRandomNum(1000, 1500);

			m_shPartNum++;

			nGenCnt++;

			if ( nGenCnt > 0 )
				return;
		}
	}
}


/******************************************************************************************************************

	CElec Class	

*******************************************************************************************************************/
CElec::CElec()
{
	InitElec();
}

CElec::~CElec()
{
	DestroyElec();
}


VOID CElec::SetupElec()
{
	D3DVECTOR vNorm(0, 0, -1);

	for ( INT nCntY = 0; nCntY < (_MAX_ELEC_NODEY+1); nCntY++ )
	{
		for ( INT nCntX = 0; nCntX < (_MAX_ELEC_NODEX+1); nCntX++ )
		{
			FLOAT fXPos = -0.5f+(FLOAT)nCntX/(FLOAT)(_MAX_ELEC_NODEX);
			FLOAT fYPos = /*-0.5f+*/(FLOAT)nCntY/(FLOAT)(_MAX_ELEC_NODEY);
			FLOAT fu = (FLOAT)nCntX/(FLOAT)(_MAX_ELEC_NODEX);
			FLOAT fv = (FLOAT)nCntY/(FLOAT)(_MAX_ELEC_NODEY);

			m_avElec[nCntY][nCntX] = D3DVERTEX(D3DVECTOR(fXPos, fYPos, 0), vNorm, fu, fv);
//			m_avElec[nCntY][nCntX] = D3DLVERTEX(D3DVECTOR(fXPos, fYPos, 0), RGB(0, 255, 0), RGB(255, 0, 0), fu, fv);
		}
	}

	memcpy(m_avSaveElec, m_avElec, (_MAX_ELEC_NODEY+1)*(_MAX_ELEC_NODEX+1)*sizeof(D3DVERTEX));

	// 타일폴리곤의 인덱스 생성.
    WORD* pwIndex = m_pwElecIndices;
	for ( nCntY = 0; nCntY < _MAX_ELEC_NODEY; nCntY++ )
	{
		for ( INT nCntX = 0; nCntX < _MAX_ELEC_NODEX; nCntX++ )
		{
			*pwIndex++ = (WORD)((nCntX+1)+((_MAX_ELEC_NODEX+1)*nCntY));
			*pwIndex++ = (WORD)(nCntX+((_MAX_ELEC_NODEX+1)*(nCntY+1)));
			*pwIndex++ = (WORD)((nCntX+1)+((_MAX_ELEC_NODEX+1)*(nCntY+1)));
			*pwIndex++ = (WORD)(nCntX+((_MAX_ELEC_NODEX+1)*(nCntY+1)));
			*pwIndex++ = (WORD)((nCntX+1)+((_MAX_ELEC_NODEX+1)*nCntY));
			*pwIndex++ = (WORD)((nCntX)+((_MAX_ELEC_NODEX+1)*nCntY));
		}
	}
}

VOID CElec::InitElec()
{
	ZeroMemory(m_pwElecIndices, _ELEC_INDICES*sizeof(WORD));
	ZeroMemory(m_avElec, sizeof(D3DVERTEX)*_MAX_ELEC_NODEY+1*_MAX_ELEC_NODEX+1);
	ZeroMemory(m_avSaveElec, (_MAX_ELEC_NODEY+1)*(_MAX_ELEC_NODEX+1)*sizeof(D3DVERTEX));

	m_fSize		= 0;
	m_fRadian	= 0;
	m_shPosX	= 0;
	m_shPosY	= 0;
	m_shDstPosX = 0;
	m_shDstPosY = 0;

}

VOID CElec::DestroyElec()
{
	InitElec();
}

VOID CElec::UpdateElec(SHORT shPosX, SHORT shPosY, SHORT shDstPosX, SHORT shDstPosY)
{
	FLOAT	fDiv;

	fDiv = 0.0f;

	m_shPosX = shPosX;
	m_shPosY = shPosY;
	m_shDstPosX = shDstPosX;
	m_shDstPosY = shDstPosY;

	INT nAbsX = abs(m_shDstPosX - m_shPosX);
	INT nAbsY = abs(m_shDstPosY - m_shPosY);

	m_fSize = (FLOAT)sqrt(nAbsX*nAbsX + nAbsY*nAbsY);

//	fDiv = (FLOAT)(nAbsY)/(FLOAT)(nAbsX);

	if ( m_fSize == 0.0f )
	{
		m_fSize = 1.0f;
	}

	fDiv = (FLOAT)-(m_shDstPosX - m_shPosX)/m_fSize;

	m_fRadian = (FLOAT)asin(fDiv);

	if ( m_shDstPosY - m_shPosY > 0 )
		m_fRadian = g_PI/2 + g_PI/2 - m_fRadian;


//	for ( INT nCntY = 0; nCntY < (_MAX_ELEC_NODEY+1); nCntY++ )

	static int nCnt = 0;

	nCnt++;

	if ( nCnt >= 2 )
		nCnt = 0;

	if ( nCnt == 1 )
	{
	
	for ( INT nCntY = 1; nCntY < _MAX_ELEC_NODEY; nCntY++ )
	{
//		FLOAT fRandX = _RAND_FLOAT*1.3f	 - 1.0f;
		FLOAT fRandX = _RAND_FLOAT*0.8f - 0.4f;
//		FLOAT fRandY = _RAND_FLOAT*0.2f;
		for ( INT nCntX = 0; nCntX < (_MAX_ELEC_NODEX+1); nCntX++ )
		{
			m_avElec[nCntY][nCntX].x = m_avSaveElec[nCntY][nCntX].x+fRandX;
//			m_avElec[nCntY][nCntX].y = m_avSaveElec[nCntY][nCntX].y+fRandY;
		}
	}

	}
	
/*
	CHAR szBuff[MAX_PATH];
	sprintf(szBuff, "->라디안:[%f] %f", m_fRadian, fDiv);
	g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), 0, 100, RGB(250, 125, 0), RGB(0, 0, 0), szBuff);
*/
}

HRESULT CElec::RenderElec(LPDIRECT3DDEVICE7 lpDevice)
{
	if ( lpDevice )
	{
		LPDIRECTDRAWSURFACE7 lpddsParticleTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_PARTICLE, _IMAGE_PROGUSE, 540);

		D3DMATRIX matWorldOriginal;
		D3DMATRIX matTrans;
		D3DMATRIX matScale;
		D3DMATRIX matRot;
		D3DMATRIX matTmpWorld;
		D3DMATRIX matWorld;
		D3DVECTOR vTrans;
		D3DMATERIAL7 mtrl;

		D3DUtil_InitMaterial(mtrl, (FLOAT)200/255.0f, (FLOAT)200/255.0f,  (FLOAT)255/255.0f);
		mtrl.diffuse.a = 1.0f/255.0f;
		lpDevice->SetMaterial(&mtrl);

  		vTrans.x = (FLOAT)m_shPosX-400;
		vTrans.y = (FLOAT)-m_shPosY+300;
		vTrans.z = (FLOAT)0; 

		if( SUCCEEDED(lpDevice->BeginScene()) )
		{
			lpDevice->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			SetBlendRenderState(lpDevice, _BLEND_LIGHTINV, &mtrl);
			D3DUtil_SetRotateZMatrix(matRot, m_fRadian);
			D3DUtil_SetTranslateMatrix(matTrans, vTrans);
			D3DUtil_SetScaleMatrix(matScale, 128/2.4f, 512, 1.0f);

			D3DMath_MatrixMultiply(matTmpWorld, matRot, matTrans);
			D3DMath_MatrixMultiply(matWorld, matScale, matTmpWorld);

			lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

			lpDevice->SetTexture(0, lpddsParticleTextr);
			lpDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
										   D3DFVF_VERTEX,
										   m_avElec, _ELEC_VERTICES, 
										   m_pwElecIndices, _ELEC_INDICES, NULL);

			lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			ResetBlendenderState(lpDevice);
			lpDevice->EndScene();

			return S_OK;
		}
	}
	return E_FAIL;
}






CMist::CMist()
{
 	D3DVECTOR vNorm(0, 0, -1);
    m_avBillboard[0] = D3DVERTEX(D3DVECTOR(-400.0f, 300.0f, 0), vNorm, 0, 0);
    m_avBillboard[1] = D3DVERTEX(D3DVECTOR(-400.0f,-300.0f, 0), vNorm, 0, 1);
    m_avBillboard[2] = D3DVERTEX(D3DVECTOR( 400.0f, 300.0f, 0), vNorm, 1, 0);
    m_avBillboard[3] = D3DVERTEX(D3DVECTOR( 400.0f,-300.0f, 0), vNorm, 1, 1);

	m_vTrans.x = 0;
	m_vTrans.y = 0;
	m_vTrans.z = 0;
}

CMist::~CMist()
{
}

BOOL CMist::Create()
{
	return TRUE;
}

VOID CMist::Init()
{
}

VOID CMist::Destory()
{
}

HRESULT CMist::DrawMist()
{
	if ( g_xMainWnd.Get3DDevice() )
	{
		LPDIRECTDRAWSURFACE7 lpddsParticleTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_PARTICLE, _IMAGE_PROGUSE, 550);

		D3DMATRIX matWorldOriginal;
		D3DMATRIX matTrans;
		D3DMATRIX matScale;
		D3DMATRIX matWorld;
		D3DMATERIAL7 mtrl;

		static int nCnt = 0;

		nCnt++;

		if ( nCnt < 800 )
		{
 			m_vTrans.x -= 1.9f; 
			m_vTrans.y -= 0.2f; 
			m_vTrans.z = (FLOAT)0;
		}
		else if ( nCnt >= 800 &&  nCnt < 1600 )
		{
 			m_vTrans.x += 1.9f; 
			m_vTrans.y += 0.2f; 
			m_vTrans.z = (FLOAT)0;
		}
		else
		{
			nCnt = 0;
		}

		D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)200/255.0f, (FLOAT)200/255.0f);
		mtrl.diffuse.a = 1.0f/255.0f;
		g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

		if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
		{
			g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			D3DUtil_SetTranslateMatrix(matTrans, m_vTrans);
			D3DUtil_SetScaleMatrix(matScale, 5.0f, 2.0f, 1.0f);
			D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
			g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

			SetBlendRenderState(g_xMainWnd.Get3DDevice(), 2, &mtrl);

			g_xMainWnd.Get3DDevice()->SetTexture(0, lpddsParticleTextr);

			g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBillboard, 4, NULL);

			ResetBlendenderState(g_xMainWnd.Get3DDevice());

			g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			g_xMainWnd.Get3DDevice()->EndScene();
			return S_OK;
		}
	}
	return E_FAIL;
}

VOID CMist::ProgressMist()
{
	DrawMist();
}
