#pragma once
#include "Direct Demo.h"
#include "CGraphManager.h"
#include "CLightBase.h"

typedef LPDIRECT3DVERTEXBUFFER9 LPVertexBuf;
typedef LPDIRECT3DINDEXBUFFER9	LPIndexBuf;

struct Vertex 
{
	Vertex() {};
	Vertex(float x, float y, float z, D3DCOLOR color, float nx, float ny, float nz)
	{
		_x = x;
		_y = y;
		_z = z;

		_nx = nx;
		_ny = ny;
		_nz = nz;
		_color = color;
	};
	float _x, _y, _z;
	float _nx, _ny, _nz;
	D3DCOLOR _color;
};



class CBaseGraphBase
{
public:
	CBaseGraphBase();
	~CBaseGraphBase();

    void InitGraph(HWND hwnd);

	void Club();
    void TextrueClub();
	void Teapot();
	void OnDarwGraph(float x,float y,float z);
	void Display();
private:
	LPDIRECT3DDEVICE9			m_device;
    LPVertexBuf		            m_vb;
    LPIndexBuf          		m_ib;

    D3DXMATRIX					m_WorldMatrix;

    //ƒ⁄÷√Õº–Œ
	ID3DXMesh*					m_Teapot;
	LPD3DXMESH					m_lpBox;
	LPD3DXMESH					m_lpSphere;
	LPD3DXMESH					m_lpPolygon;

	const int m_height = SCREECN_HEIGHT;
	const int m_width = SCREECN_WIDTH;

	float y = 0.0f;

    CGraphManager*  m_lpManger;
	CLightBase      m_LightBase;
};