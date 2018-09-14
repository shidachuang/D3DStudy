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
       ���еĳ�Ա����Diffuse��Ambient��Specular�ֱ��ʾ��������������⡢��
       ���⡢���淴���ķ���ϵ����Emissive��ʾ�����������ȣ�Power��ʾ����
       ����ָ����
       �����Id��Ia��Is��Ie�ֱ��ʾ������⡢�����⡢���淴�����Է�������ȣ�
       ��ô���嶥�����յ���ɫ����Ϊ�� It = Id + Ia + Is + Ie;
     ************************************************************************/


	m_Matrl.Ambient = WHITE_LSZ;        //ָ�����淴��Ļ�����
	m_Matrl.Diffuse = YELLOW_LSZ;       //ָ�����淴����������
	m_Matrl.Specular = RED_LSZ;         //ָ�����淴��ľ����
	m_Matrl.Emissive = BLUE_LSZ;        //���汾���Է���
	m_Matrl.Power = 50.0f;               //����߹⣬����ֵ�Ǹ߹������ֵ����ֵԽ���ʾ�߹�ǿ������Χ�������Խ��


	return &m_Matrl;
}

D3DLIGHT9* CLightBase::CreateLight()
{
	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));

	m_Light.Type = D3DLIGHT_SPOT;                           //Type���ƹ����ͣ���3�֣�D3DLIGHT_POINT(���)��D3DLIGHT_SPOT(�۹��)��D3DLIGHT_DIRECTIONAL(�����)
	m_Light.Diffuse = YELLOW_LSZ;                           //Diffuse����Դ���������������ɫ
	m_Light.Specular = RED_LSZ *0.3f;                       //Specular����Դ�����ľ������ɫ
	m_Light.Ambient = WHITE_LSZ * 0.6f;                     //Ambient����Դ�����Ļ�������ɫ
	m_Light.Direction = D3DXVECTOR3(1.0f, 1.0f, 0.0f);      //��������ʾ�Ĺ�Դ�����������䷽�򣨶Ե��Դ��Ч��
    m_Light.Position = {1.0f,1.0f,0.0f};                    //��������ʾ�Ĺ�Դ��������λ�ã��������oЧ��
    m_Light.Falloff = true;                                 //�ƹ����Բ׶����Բ׶֮���ǿ��˥�������Ծ۹����Ч������ֵͨ����Ϊ1.0f��
    m_Light.Attenuation0 = 1.0f;                            //Attenuation0�� Attenuation1��Attenuation2���ƹ�˥����������������ƹ�ǿ�ȵĴ�������˥�����Է������Ч����
    m_Light.Attenuation1 = 0.0f;                            //Attenuation0����㶨˥����Attenuation1��������˥����Attenuation2�������˥����Attenuation0ͨ��Ϊ 0.0f��
    m_Light.Attenuation2 = 0.0f;                            //�ʵ���ʹ�����¹�ʽ��D������Դ�ľ��룬A0��A1�� A2�ֱ���Attenuation0��Attenuation1��Attenuation2��ƥ��
    m_Light.Theta = D3DX_PI / 3.0f;                         //ָ���ƹ���Բ׶�ĽǶȣ����Ծ۹����Ч������λ�ǻ���
    m_Light.Phi = D3DX_PI / 6.0f;                           //ָ����Բ׶�ĽǶȣ����Ծ۹����Ч������λ�ǻ���
    m_Light.Range = 5.0f;                                   //�ƹ��ܹ����������Χ���Է������Ч������ֵ����ӦС��0??
	return &m_Light;
}
