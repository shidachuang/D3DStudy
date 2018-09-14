#pragma once



class CLightBase
{
public:
	CLightBase();
	~CLightBase();


	D3DMATERIAL9* CreateMatrl();

	D3DLIGHT9* CreateLight();
private:
	D3DMATERIAL9	m_Matrl;
	D3DLIGHT9		m_Light;
};

