#pragma once
#include "stdafx.h"


//所要用到的颜色：
const D3DXCOLOR     WHITE_LSZ(D3DCOLOR_XRGB(255, 255, 255));
const D3DXCOLOR     BLACK_LSZ(D3DCOLOR_XRGB(0, 0, 0));
const D3DXCOLOR     RED_LSZ(D3DCOLOR_XRGB(255, 0, 0));
const D3DXCOLOR     GREEN_LSZ(D3DCOLOR_XRGB(0, 255, 0));
const D3DXCOLOR     BLUE_LSZ(D3DCOLOR_XRGB(0, 0, 255));
const D3DXCOLOR     YELLOW_LSZ(D3DCOLOR_XRGB(255, 255, 0));
const D3DXCOLOR     CYAN_LSZ(D3DCOLOR_XRGB(0, 255, 255));
const D3DXCOLOR     MAGENTA_LSZ(D3DCOLOR_XRGB(255, 0, 255));

//顶点格式：说明对应于顶点格式的顶点结构包含了位置属性和漫反射颜色属性  
//要注意的是，灵活顶点格式标记的指定顺序必须与顶点结构中相应类型数据的顺序保持一致。
//const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

const DWORD VERTEX_FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;

//基础结构
struct _base_vertex
{
    float _x, _y, _z;

};

//颜色结构
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


//纹理结构
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