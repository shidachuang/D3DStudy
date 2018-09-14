#include "stdafx.h"
#include "CGraphManager.h"

static CGraphManager* m_single_point = NULL;

CGraphManager::CGraphManager()
{
}


CGraphManager::~CGraphManager()
{
}

CGraphManager* CGraphManager::GetManager()
{
	if (m_single_point == NULL)
		m_single_point = new CGraphManager;

	return m_single_point;
}

void CGraphManager::PureInstance()
{
	if (m_single_point)
	{
		m_single_point->UnInitD3D();
		delete m_single_point;
	}
	m_single_point = nullptr;
}

HRESULT CGraphManager::InitD3D(HWND hwnd)
{
	D3DPRESENT_PARAMETERS d3dParameters;

	m_lpD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_lpD3D9 == NULL)
		return E_FAIL;

	D3DCAPS9 caps;
	m_lpD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	ZeroMemory(&d3dParameters, sizeof(D3DPRESENT_PARAMETERS));

	d3dParameters.BackBufferWidth = SCREECN_WIDTH;
	d3dParameters.BackBufferHeight = SCREECN_HEIGHT;
	d3dParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dParameters.BackBufferCount = 1;
	d3dParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dParameters.MultiSampleQuality = 0;
	d3dParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dParameters.hDeviceWindow = hwnd;
	d3dParameters.Windowed = TRUE;
	d3dParameters.EnableAutoDepthStencil = true;
	d3dParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dParameters.Flags = 0;
	d3dParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;


	if (FAILED(m_lpD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, vp, &d3dParameters, &m_lpD3DDevice)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CGraphManager::UnInitD3D()
{
	if (m_lpD3DDevice != NULL)
	{
		m_lpD3DDevice->Release();
		m_lpD3DDevice = NULL;
	}
	if (m_lpD3D9 != NULL)
	{
		m_lpD3D9->Release();
		m_lpD3D9 = NULL;
	}
}

LPDIRECT3DDEVICE9 CGraphManager::GetDirectDevice()
{
	return m_lpD3DDevice;
}
