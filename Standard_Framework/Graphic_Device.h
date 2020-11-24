#pragma once

// mfc 구조도 기억해보는건 어때요


class CGraphic_Device final
{
public:
	static CGraphic_Device* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CGraphic_Device;
		}
		
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}	
	}
private:
	explicit CGraphic_Device();
	~CGraphic_Device();

	//사실 복사생성자, 디폴트대입연산자도 막아요
	explicit CGraphic_Device(const CGraphic_Device& rObject) {};
	void operator=(const CGraphic_Device& rObject) {};

public:
	PDIRECT3DDEVICE9 Get_Device() { return m_pDevice; }
	LPD3DXSPRITE Get_Sprite() { return m_pSprite; }
	LPD3DXFONT Get_Font() { return m_pFont; }

public:
	// 객체를 제어하기 위한 컴객체들을 생성, 초기화 공간
	HRESULT	Ready_Graphic_Device();
	void Release_Graphic_Device();


	void Render_Begin();
	void Render_End();

private:

	// component object model, 컴객체, ms에서 만들어놓은 부품단위의 객체
	// 요걸 골라서 조립하면 됩니다.
	// 장치의 지원 수준을 확인
	// 수준에 맞는 장치를 생성해주는 녀석?
	LPDIRECT3D9			m_pSDK;
	LPDIRECT3DDEVICE9	m_pDevice;	// 실질적으로 장치를 제어하는 com 객체
	LPD3DXSPRITE		m_pSprite;	// 스프라이트 부품
	LPD3DXFONT			m_pFont;	// 폰트 부품
	// 1. 장치를 조사하기 위한 컴객체 생성
	// 2. 제어하기 위한 SDK를 이용하여 그래픽카드 지원 수준 조사
	// 3. 그래픽 카드의 지원 수준에 맞춰 장치 제어하기 위한 컴객체 생성


private:
	static CGraphic_Device*	m_pInstance;

};

