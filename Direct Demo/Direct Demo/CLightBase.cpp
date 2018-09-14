#include "stdafx.h"
#include "CLightBase.h"


CLightBase::CLightBase()
{
}


CLightBase::~CLightBase()
{
}

D3DMATERIAL9* CLightBase::CreateMatrl()
{
    /************************************************************************
       其中的成员变量Diffuse、Ambient、Specular分别表示物体表面的漫反射光、环
       境光、镜面反射光的反射系数，Emissive表示物体的自身发光度，Power表示镜面
       反射指数。
       如果用Id、Ia、Is、Ie分别表示漫反射光、环境光、镜面反射光和自发光的亮度，
       那么物体顶点最终的颜色亮度为： It = Id + Ia + Is + Ie;
     ************************************************************************/


	m_Matrl.Ambient = WHITE_LSZ;        //指定表面反射的环境光
	m_Matrl.Diffuse = YELLOW_LSZ;       //指定表面反射的漫反射光
	m_Matrl.Specular = RED_LSZ;         //指定表面反射的镜面光
	m_Matrl.Emissive = BLUE_LSZ;        //表面本身自发光
	m_Matrl.Power = 50.0f;               //镜面高光，它的值是高光的锐利值，该值越大表示高光强度与周围亮度相差越大


	return &m_Matrl;
}

D3DLIGHT9* CLightBase::CreateLight()
{
	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));

	m_Light.Type = D3DLIGHT_SPOT;                           //Type－灯光类型，共3种：D3DLIGHT_POINT(点光)、D3DLIGHT_SPOT(聚光灯)、D3DLIGHT_DIRECTIONAL(方向光)
	m_Light.Diffuse = YELLOW_LSZ;                           //Diffuse－光源发出的漫反射光颜色
	m_Light.Specular = RED_LSZ *0.3f;                       //Specular－光源发出的镜面光颜色
	m_Light.Ambient = WHITE_LSZ * 0.6f;                     //Ambient－光源发出的环境光颜色
	m_Light.Direction = D3DXVECTOR3(1.0f, 1.0f, 0.0f);      //用向量表示的光源世界坐标照射方向（对点光源无效）
    m_Light.Position = {1.0f,1.0f,0.0f};                    //用向量表示的光源世界坐標位置（對方向光無效）
    m_Light.Falloff = true;                                 //灯光从内圆锥到外圆锥之间的强度衰减（仅对聚光灯有效），该值通常设为1.0f。
    m_Light.Attenuation0 = 1.0f;                            //Attenuation0、 Attenuation1、Attenuation2－灯光衰减变量，用来定义灯光强度的传播距离衰减（对方向光无效）。
    m_Light.Attenuation1 = 0.0f;                            //Attenuation0定义恒定衰减，Attenuation1定义线性衰减，Attenuation2定义二次衰减。Attenuation0通常为 0.0f，
    m_Light.Attenuation2 = 0.0f;                            //适当的使用如下公式，D代表到光源的距离，A0、A1、 A2分别与Attenuation0、Attenuation1、Attenuation2相匹配
    m_Light.Theta = D3DX_PI / 3.0f;                         //指定灯光内圆锥的角度（仅对聚光灯有效），单位是弧度
    m_Light.Phi = D3DX_PI / 6.0f;                           //指定外圆锥的角度（仅对聚光灯有效），单位是弧度
    m_Light.Range = 5.0f;                                   //灯光能够传播的最大范围（对方向光无效），该值不能应小于0??
	return &m_Light;
}
