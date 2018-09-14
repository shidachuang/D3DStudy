#pragma once
#include "stdafx.h"


//��Ҫ�õ�����ɫ��
const D3DXCOLOR     WHITE_LSZ(D3DCOLOR_XRGB(255, 255, 255));
const D3DXCOLOR     BLACK_LSZ(D3DCOLOR_XRGB(0, 0, 0));
const D3DXCOLOR     RED_LSZ(D3DCOLOR_XRGB(255, 0, 0));
const D3DXCOLOR     GREEN_LSZ(D3DCOLOR_XRGB(0, 255, 0));
const D3DXCOLOR     BLUE_LSZ(D3DCOLOR_XRGB(0, 0, 255));
const D3DXCOLOR     YELLOW_LSZ(D3DCOLOR_XRGB(255, 255, 0));
const D3DXCOLOR     CYAN_LSZ(D3DCOLOR_XRGB(0, 255, 255));
const D3DXCOLOR     MAGENTA_LSZ(D3DCOLOR_XRGB(255, 0, 255));

//�����ʽ��˵����Ӧ�ڶ����ʽ�Ķ���ṹ������λ�����Ժ���������ɫ����  
//Ҫע����ǣ������ʽ��ǵ�ָ��˳������붥��ṹ����Ӧ�������ݵ�˳�򱣳�һ�¡�
//const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

const DWORD VERTEX_FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;

//�����ṹ
struct _base_vertex
{
    float _x, _y, _z;

};

//��ɫ�ṹ
struct _color_vertex : _base_vertex
{
    D3DCOLOR dwColor;

    _color_vertex(float x, float y, float z, DWORD color):dwColor(color)
    {
        _base_vertex::_x = x;
        _base_vertex::_y = y;
        _base_vertex::_z = z;
    }
};


//����ṹ
struct _texture_vertex : _base_vertex
{
    float _u, _v;

    _texture_vertex(float x, float y, float z, float u, float v)
        :_u(u), _v(v) 
    {
        _base_vertex::_x = x;
        _base_vertex::_y = y;
        _base_vertex::_z = z;
    }
};