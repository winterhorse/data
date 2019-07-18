#ifndef _UNIFORM_LOCATION_H__
#define _UNIFORM_LOCATION_H__
#include <GLES2/gl2.h>
struct Light
{
	bool  m_enableLight;                             //�Ƿ��������
	float m_position[4];                             //��Դλ��
	float m_ambientColor[4];                         //��Դ��������� 
	float m_diffuseColor[4];                         //��Դ����������
	float m_specularColor[4];                        //��Դ���淴������  
	float m_spotDirection[3];                        //�۹�����䷽�� 
	float m_attenuationFactors[3];                   //��ǿ������ϵ����
	float m_spotExponent;                            //��ǿ��ƫ�����ĽǶȵ�˥��ϵ��                  
	float m_spotCutoffAngle;                         //�۹��Դ�������           
	bool  m_computeDistanceAttenuation;              //�Ƿ������Դ���������   
	Light()
	{
		for(int i = 0;i < 4;i++)
		{
			m_position[i] = 0;
			m_ambientColor[i] = 0;
			m_diffuseColor[i] = 0;
			m_specularColor[i] = 0;
		}
		for(int i = 0;i < 3;i++)
		{
			m_spotDirection[i] = 0;
			m_attenuationFactors[i] = 0;
		}
		m_spotExponent = 0;
		m_spotCutoffAngle = 0;
		m_enableLight = false;
		m_computeDistanceAttenuation = true;
	}
};
struct LightLoc
{
	GLuint m_enableLightLoc;                          //�Ƿ��������
	GLuint m_positionLoc;                             //��Դλ��
	GLuint m_ambientColorLoc;                         //��Դ���������  
	GLuint m_diffuseColorLoc;                         //��Դ����������
	GLuint m_specularColorLoc;                        //��Դ���淴������  
	GLuint m_spotDirectionLoc;                        //�۹�����䷽��  
	GLuint m_attenuationFactorsLoc;                   //��ǿ������ϵ����
	GLuint m_spotExponentLoc;                         //��ǿ��ƫ�����ĽǶȵ�˥��ϵ�� 
	GLuint m_spotCutoffAngleLoc;                      //�۹��Դ�������
	GLuint m_computeDistanceAttenuationLoc;           // �Ƿ������Դ��������� 
	LightLoc()
	{
		m_enableLightLoc = 0;
		m_positionLoc = 0;
		m_ambientColorLoc = 0;
		m_diffuseColorLoc = 0;
		m_specularColorLoc = 0;
		m_spotDirectionLoc = 0;
		m_attenuationFactorsLoc = 0;
		m_spotExponentLoc = 0;
		m_spotCutoffAngleLoc = 0;
		m_computeDistanceAttenuationLoc = 0;
	}
};
struct Matrial
{
	float m_ambientColor[4];                         //���ʻ�������� 
	float m_diffuseColor[4];                         //��������������
	float m_specularColor[4];                        //���ʾ��淴������ 
	float m_emissiveColor[4];                        //���������ǿ
	float m_shiness;                                 //���ʷ���ϵ��
	bool  m_enableColorMatrial;                      //�Ƿ����ò��ϻ����������������������ڵ�ǰ������ɫ
	Matrial()
	{
		for(int i = 0;i < 4;i++)
		{
			m_ambientColor[i] = 0;
			m_diffuseColor[i] = 0;
			m_specularColor[i] = 0;
			m_emissiveColor[i] = 0;
		}
		m_shiness = 0;
		m_enableColorMatrial = false;
	}

};
struct MatrialLoc
{
	GLuint m_ambientColorLoc;                         //���ʻ�������� 
	GLuint m_diffuseColorLoc;                         //��������������
	GLuint m_specularColorLoc;                        //���ʾ��淴������ 
	GLuint m_emissiveColorLoc;                        //���������ǿ
	GLuint m_shinessLoc;                              //���ʷ���ϵ��
	GLuint m_opacityLoc;
	GLuint m_enableColorMatrialLoc;                   //�Ƿ����ò��ϻ����������������������ڵ�ǰ������ɫ
	MatrialLoc()
	{
		m_ambientColorLoc = 0;
		m_diffuseColorLoc = 0;
		m_specularColorLoc = 0;
		m_shinessLoc = 0;
		m_enableColorMatrialLoc = 0;
		m_emissiveColorLoc = 0;
		m_opacityLoc = 0;
	}
};
struct VertexLoc
{
	GLuint m_positionLoc;                               //��������
	GLuint m_normalLoc;                               //����������
	GLuint m_colorLoc;                                //��ɫ����
	GLuint m_textCoordLoc;                            //������������
	VertexLoc()
	{
		m_positionLoc = 0;
		m_normalLoc = 0;
		m_colorLoc = 0;
		m_textCoordLoc = 0;
	}
};
struct MatrixLoc
{
	GLuint m_cameraPositionLoc;                       //���������
	GLuint m_finalMatrixLoc;                          //�ܱ任����
	GLuint m_worldMatrixLoc;                          //��������ϵ��ģ�;���
	GLuint m_cameraViewLoc;                           //�������ϵ��ģ�;���
	GLuint m_projMatrixLoc;                           //ͶӰ����
	MatrixLoc()
	{
		m_projMatrixLoc = 0;
		m_cameraPositionLoc = 0;
		m_cameraViewLoc = 0;
		m_finalMatrixLoc = 0;
		m_worldMatrixLoc = 0;
	}
};
struct SamplerLoc
{
	static const int MAX_SAMPLER_NUM = 8;
	GLuint m_existTextureLoc;
	GLuint m_texSamplerLoc[MAX_SAMPLER_NUM];
	SamplerLoc()
	{
		for(int i = 0;i < MAX_SAMPLER_NUM;i++)
			m_texSamplerLoc[i] = 0;
	}
};
#endif