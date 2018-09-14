#include "stdafx.h"
#include "CBaseGraphBase.h"


CBaseGraphBase::CBaseGraphBase()
{
    m_lpManger = NULL;
}


CBaseGraphBase::~CBaseGraphBase()
{

}

void CBaseGraphBase::InitGraph(HWND hwnd)
{
    if (m_lpManger == NULL)
    {
        m_lpManger = g_SinglerManager->GetManager();
    }

    if (IsWindow(hwnd))
    {
        m_lpManger->InitD3D(hwnd);
    }

    m_device = g_SinglerManager->GetDirectDevice();
}

void CBaseGraphBase::Club()
{
	m_device = g_SinglerManager->GetDirectDevice();

	m_device->CreateVertexBuffer(8 * sizeof(Vertex), D3DUSAGE_WRITEONLY, VERTEX_FVF, D3DPOOL_MANAGED, &m_vb, NULL);
	m_device->CreateIndexBuffer(36 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_ib, NULL);

	Vertex* lpVertexes;
	m_vb->Lock(0, 0, (void**)&lpVertexes, 0);
	lpVertexes[0] = Vertex(-1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB(255, 0, 0), 0.0f, 0.0f, 0.0f);
	lpVertexes[1] = Vertex(-1.0f, 1.0f, -1.0f, D3DCOLOR_XRGB(0, 255, 0), 0.0f, 0.0f, 0.0f);
	lpVertexes[2] = Vertex(1.0f, 1.0f, -1.0f, D3DCOLOR_XRGB(0, 0, 255), 0.0f, 0.0f, 0.0f);
	lpVertexes[3] = Vertex(1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB(255, 0, 0), 0.0f, 0.0f, 0.0f);
	lpVertexes[4] = Vertex(-1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), 0.0f, 0.0f, 0.0f);
	lpVertexes[5] = Vertex(-1.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), 0.0f, 0.0f, 0.0f);
	lpVertexes[6] = Vertex(1.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), 0.0f, 0.0f, 0.0f);
	lpVertexes[7] = Vertex(1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), 0.0f, 0.0f, 0.0f);
	m_vb->Unlock();

	WORD* indices = 0;
	m_ib->Lock(0, 0, (void**)&indices, 0);

	// front side
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	// back side
	indices[6] = 4; indices[7] = 6; indices[8] = 5;
	indices[9] = 4; indices[10] = 7; indices[11] = 6;

	// left side
	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;

	// right side
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;

	// top
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;

	// bottom
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;

	m_ib->Unlock();

	//取景变换
	D3DXVECTOR3 position(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(1.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	m_device->SetTransform(D3DTS_VIEW, &V);

	//投影变换
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, (float)m_width / (float)m_height, 1.0f, 1000.0f);
	m_device->SetTransform(D3DTS_PROJECTION, &proj);

	//绘制状态
	//m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//m_device->SetRenderState(D3DRS_LIGHTING, false);

	m_device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	m_device->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, true);



	m_device->SetMaterial(m_LightBase.CreateMatrl());
	m_device->SetLight(0, m_LightBase.CreateLight());
	m_device->LightEnable(0, true);
}

void CBaseGraphBase::TextrueClub()
{
    m_device->CreateVertexBuffer(24 * sizeof(_texture_vertex), D3DUSAGE_WRITEONLY, VERTEX_FVF, D3DPOOL_MANAGED, &m_vb, NULL);
    _texture_vertex* v;
    m_vb->Lock(0, 0, (void**)&v, 0);
    // 正面数据
    v[0]  = _texture_vertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f);
    v[1]  = _texture_vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    v[2]  = _texture_vertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f);
    v[3]  = _texture_vertex(1.0f, -1.0f, -1.0f, 1.0f, 0.0f);

    //背面数据
    v[4]  = _texture_vertex(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f);
    v[5]  = _texture_vertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f);
    v[6]  = _texture_vertex(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    v[7]  = _texture_vertex(-1.0f, 1.0f, 1.0f, 1.0f, 0.0f);

    // 上面数据
    v[8]  = _texture_vertex(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f);
    v[9]  = _texture_vertex(-1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
    v[10] = _texture_vertex(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    v[11] = _texture_vertex(1.0f, 1.0f, -1.0f, 1.0f, 0.0f);

    // 下面数据
    v[12] = _texture_vertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f);
    v[13] = _texture_vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f);
    v[14] = _texture_vertex(1.0f, -1.0f, 1.0f, 1.0f, 1.0f);
    v[15] = _texture_vertex(-1.0f, -1.0f, 1.0f, 1.0f, 0.0f);

    // 左面数据
    v[16] = _texture_vertex(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f);
    v[17] = _texture_vertex(-1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
    v[18] = _texture_vertex(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f);
    v[19] = _texture_vertex(-1.0f, -1.0f, -1.0f, 1.0f, 0.0f);

    // 右面数据
    v[20] = _texture_vertex(1.0f, -1.0f, -1.0f, 0.0f, 0.0f);
    v[21] = _texture_vertex(1.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    v[22] = _texture_vertex(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    v[23] = _texture_vertex(1.0f, -1.0f, 1.0f, 1.0f, 0.0f);

    m_vb->Unlock();

    m_device->CreateIndexBuffer(36 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_ib, 0);
    WORD* i = 0;
    m_ib->Lock(0, 0, (void**)&i, 0);


    // 正面
    i[0] = 0; i[1] = 1; i[2] = 2;
    i[3] = 0; i[4] = 2; i[5] = 3;

    // 背面
    i[6] = 4; i[7] = 5; i[8] = 6;
    i[9] = 4; i[10] = 6; i[11] = 7;

    //上面
    i[12] = 8; i[13] = 9; i[14] = 10;
    i[15] = 8; i[16] = 10; i[17] = 11;

    // 下面
    i[18] = 12; i[19] = 13; i[20] = 14;
    i[21] = 12; i[22] = 14; i[23] = 15;

    // 左面
    i[24] = 16; i[25] = 17; i[26] = 18;
    i[27] = 16; i[28] = 18; i[29] = 19;

    //右面
    i[30] = 20; i[31] = 21; i[32] = 22;
    i[33] = 20; i[34] = 22; i[35] = 23;

    m_ib->Unlock();

    //取景变换
    D3DXVECTOR3 position(0.0f, 0.0f, -5.0f);
    D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
    D3DXVECTOR3 up(1.0f, 1.0f, 0.0f);
    D3DXMATRIX V;
    D3DXMatrixLookAtLH(&V, &position, &target, &up);
    m_device->SetTransform(D3DTS_VIEW, &V);

    //投影变换
    D3DXMATRIX proj;
    D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, (float)m_width / (float)m_height, 1.0f, 1000.0f);
    m_device->SetTransform(D3DTS_PROJECTION, &proj);

    //绘制状态
    //m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
    //m_device->SetRenderState(D3DRS_LIGHTING, false);

    m_device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
    m_device->SetRenderState(D3DRS_SPECULARENABLE, true);



    m_device->SetMaterial(m_LightBase.CreateMatrl());
    m_device->SetLight(0, m_LightBase.CreateLight());
    m_device->LightEnable(0, true);


    return;
}

void CBaseGraphBase::Teapot()
{
	//D3DXCreateCylinder		圆柱
	//D3DXCreatePolygon			多边形
	//D3DXCreateTorus			圆环
	D3DXCreateTeapot(m_device, &m_Teapot, nullptr);
	D3DXCreateBox(m_device, 5.0f, 5.0f, 1.0f, &m_lpBox, nullptr);
	D3DXCreateSphere(m_device, 3.0f, 100, 100, &m_lpSphere, nullptr);
	D3DXCreatePolygon(m_device, 2.0f, 8, &m_lpPolygon, nullptr);


	//取景变换
	D3DXVECTOR3 position(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(1.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	m_device->SetTransform(D3DTS_VIEW, &V);



	//投影变换
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, (float)m_width / (float)m_height, 1.0f, 1000.0f);
	m_device->SetTransform(D3DTS_PROJECTION, &proj);


	//设置着色模式
	m_device->SetRenderState(D3DRS_FILLMODE, D3DRS_FILLMODE);
	//m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

	//设置光源
	m_device->SetLight(0, m_LightBase.CreateLight());
	m_device->LightEnable(0, true);



	//D3DMATERIAL9  mtrl;
	//ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	//mtrl.Specular.r = 0.8f;
	//mtrl.Specular.g = 0.6f;
	//mtrl.Specular.b = 0.5f;
	//mtrl.Diffuse.a = 0.1f;
	//m_device->SetMaterial(&mtrl);
	//
	m_device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
}

void CBaseGraphBase::OnDarwGraph(float x, float y, float z)
{
	D3DXMATRIX Rx, Ry, Rz;
	D3DXMatrixRotationX(&Rx, x);
	D3DXMatrixRotationY(&Ry, y);
	D3DXMatrixRotationZ(&Rz, z);

	D3DXMATRIX p = Rx * Ry * Rz;
	m_device->SetTransform(D3DTS_WORLD, &p);
	

	m_device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x000000FF, 1.0f, 0);
	m_device->BeginScene();

    m_device->SetFVF(VERTEX_FVF);
    m_device->SetStreamSource(0, m_vb, 0, sizeof(_texture_vertex));
    m_device->SetIndices(m_ib);
    m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);

	//m_lpBox->DrawSubset(0);
	//m_Teapot->DrawSubset(0);
	//m_lpSphere->DrawSubset(0);
	//m_lpPolygon->DrawSubset(0);
	
	m_device->EndScene();

	m_device->Present(0, 0, 0, 0);
}

void CBaseGraphBase::Display()
{
	m_vb->Release();
	m_ib->Release();
}
