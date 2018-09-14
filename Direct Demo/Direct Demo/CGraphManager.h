#pragma once

class CGraphManager
{
protected:
	CGraphManager();
	~CGraphManager();

public:
	//static CGraphManager*	m_single_point;
	static CGraphManager* GetManager();
	static void PureInstance();

	HRESULT InitD3D(HWND hwnd);
	void UnInitD3D();

	LPDIRECT3DDEVICE9 GetDirectDevice();
private:
	LPDIRECT3D9				m_lpD3D9 = NULL;
	LPDIRECT3DDEVICE9		m_lpD3DDevice = NULL;
};

#define g_SinglerManager (CGraphManager::GetManager())