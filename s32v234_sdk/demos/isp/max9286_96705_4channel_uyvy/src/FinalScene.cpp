#include "FinalScene.h"
#include "CameraDevice.h"
#include "const_value.h"
#include "DrawScene.h"
#include "TextureIL.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "OGLWin.h"
#include "PanoramaParam.h"
#include "Panorama3DScene.h"
#include <time.h>
#include <pthread.h>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

//#include "json.hpp"


#include "dump.h"
#include "CVOGLBridge.h"
#include "utils.hpp"

#include "imgproc/LuminanceEqualize.hpp"
#include "imgproc/smooth.hpp"

#include "utils/Timer.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "trail.hpp"

float hOffset = 0.0;
float vOffset = 0.0;
float view2DScale = 1.0;


using namespace const_value;



static const float ANGLETORADIUS = 3.141592654 / 180.0;
//定义旋转动画的多个视角，旋转时，依次执行到下一个视角，并停顿一段时间，然后继续旋转
static const float constPhei = 55 * ANGLETORADIUS;
//static const float constPhei = 35 * ANGLETORADIUS;
static float gTheta[] = {0 * ANGLETORADIUS,45 * ANGLETORADIUS,90 * ANGLETORADIUS,135 * ANGLETORADIUS,180 * ANGLETORADIUS,
225 * ANGLETORADIUS,270 * ANGLETORADIUS,315 * ANGLETORADIUS};
static float gPhei[] = {constPhei,constPhei,constPhei,constPhei,constPhei,constPhei,constPhei,constPhei};
static int gViewNum = sizeof(gTheta) / sizeof(gTheta[0]);

float CFinalScene::blankColor[4] = {0.0, 0.0, 0.0, 0.0};
float CFinalScene::highlightColor[4] = {1.0, 1.0, 0.0, 0.3};

////////////////////////////////////////////////////////wyd added///////////////////////////////////////////
int SwitchChannelNum = 8;
float yangjiao=30*3.141592654 / 180.0;;
float xuanzhuan=0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////
CFinalScene::CFinalScene()
{
	for(int i = 0;i < CAMERANUM;i++){
		m_dataBuffer[i] = NULL;
	}
	m_endView = 0;
	m_curView = 4;

    glGenFramebuffers(1, &fbo);
    glGenRenderbuffers(1, &rbo);

    glGenTextures(1, &dstTex);
    glBindTexture(GL_TEXTURE_2D, dstTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 810, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glBindRenderbuffer(GL_RENDERBUFFER,  rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 810, 1080);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, dstTex, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

    auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
    	printf("framebuffer failed: ");
    	switch (status)
		{
		case GL_FRAMEBUFFER_UNSUPPORTED:
			printf("unsupported\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			printf("incomplete attachment\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
			printf("incomplete dimensions\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			printf("incomplete missing attchment\n");
			break;
		default:
			printf("unknown error: %d (0x%x)\n", status, status);
			break;
		}
    }

	// render to screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	lut.load("/data/opengl_new/LUT.bin");
	setBirdEyeViewParams(lut);
	setSingleViewParams(singleViewWidth, singleViewHeight);

	for (auto& h : isRegionHighlighted)
	{
		h = false;
	}
}


CFinalScene::~CFinalScene(void)
{
    glDeleteFramebuffers(1, &fbo);
    glDeleteRenderbuffers(1, &rbo);
    glDeleteTextures(1, &dstTex);
}

void CFinalScene::onStart()
{
    //getCameraDevice().startCapture(SRC_IMAGE_WIDTH,SRC_IMAGE_HEIGHT);
    for(int i = 0;i < CAMERANUM;i++){
        m_imageTextureID[i] = createDynamicYUYVTexture2(SRC_IMAGE_WIDTH,SRC_IMAGE_HEIGHT,&m_dataBuffer[i]);
        //m_imageTextureID[i] = createDynamicYUYVTexture(SRC_IMAGE_WIDTH,SRC_IMAGE_HEIGHT,&m_dataBuffer[i]);
    }
    int colorRGB[][3] = {{139, 0, 255},{125,125,125},{0,255,0},{255,255,255},{0,0,0}};   //紫色,灰色,绿色,白色,黑色
    int curColor = g_globalParam.m_themeColor;
    setBackGround(colorRGB[curColor][0],colorRGB[curColor][1],colorRGB[curColor][2],255);
    beginCurrentMode(g_globalParam.m_displayMode);
    getPanorama3DScene().setPanorama3dParam(gTheta[m_curView],gPhei[m_curView]);
}

void CFinalScene::onStop()
{
    getCameraDevice().stopCapture();    //停止4路摄像头采集
    for(int i = 0; i < CAMERANUM; i++)  //释放4个g2d_buf缓冲区
    {
         delete[] m_dataBuffer[i];
    }
}
void CFinalScene::onMessage(int message)
{
    //响应键盘上的数字按键，数字表示旋转的结束视角
    if(message >= '0' && message < '0' + gViewNum){
        m_endView = (message - '0');
        m_curView = (m_curView + 1) % gViewNum;
        //printf("m_curView = %d,m_endView = %d,gViewNum = %d\n",m_curView,m_endView,gViewNum);
        getPanorama3DScene().setNextCameraViewByThetaPhei(gTheta[m_curView],gPhei[m_curView],30);
    }
}
void CFinalScene::changeView(){
    static int times = 0;
	//如果还没旋转到最终的视角，且当前的动画已经结束
    if(m_curView != m_endView && getPanorama3DScene().isAnimationCompleted()){
        times++;
        if(times >= 20){     //如果已经停止了20帧，则开始下一次旋转
            m_curView = (m_curView + 1) % gViewNum;
            //printf("m_curView = %d,m_endView = %d,gViewNum = %d\n",m_curView,m_endView,gViewNum);
            getPanorama3DScene().setNextCameraViewByThetaPhei(gTheta[m_curView],gPhei[m_curView],30);
            times = 0;
        }
    }
}

extern glm::mat4 bevTransformMatrix;
static bool rotated = false;

void CFinalScene::render2DView(int x, int y, int width, int height, void* data, GLuint fbo)
{
	float* delta = static_cast<float*>(data);

	glViewport(x, y, width, height);
	for (int i = 0; i < 4; i++)
	{
		float* mask = isRegionHighlighted[i] ? highlightColor : blankColor;
		Generate_2D_View(fbo, i, m_imageTextureID, delta, mask);
	}
	for (int i = 0; i < 4; i++)
	{
		float* mask = isRegionHighlighted[i + 4] ? highlightColor : blankColor;
		Generate_2D_View_Merge(fbo, i, m_imageTextureID, delta, mask);
	}
	Generate_Car_Icon();
	glViewport(0, 0, getScreenWidth(), getScreenHeight());
}

void CFinalScene::render3DView(int x, int y, int width, int height, void* data, GLuint fbo)
{
	getPanorama3DScene().getTrackBall()->setCurViewByAngle(yangjiao,xuanzhuan);
	float* delta = static_cast<float*>(data);
	getPanorama3DScene().setViewport(x, y, width, height);
	getPanorama3DScene().draw(delta);
}

void CFinalScene::renderSingleView(int camId,int x, int y, int width, int height, void* data, GLuint fbo)
{
	float* delta = static_cast<float*>(data);
	glViewport(x, y, width, height);
	Generate_SingleView(camId, m_imageTextureID, delta);
	if(camId<2)
		Generate_Radar_Chart(0, dynamicLineFlag);
	//Avm_ParkingTrail(dynamicLineFlag);
	glViewport(0, 0, getScreenWidth(), getScreenHeight());
}

void CFinalScene::renderTrail(int x, int y, int width, int height, bool applyTransform, GLuint fbo)
{
	#if 0
	glViewport(x, y, width, height);
	drawTrail(steeringAngle, 200, width, height, applyTransform);
	glViewport(0, 0, getScreenWidth(), getScreenHeight());
	#endif
}

inline void CFinalScene::setRegionHighlight(int regionId)
{
	isRegionHighlighted[regionId] = true;
}

inline void CFinalScene::unsetRegionHighlight(int regionId)
{
	isRegionHighlighted[regionId] = false;
}

extern vsdk::SMat frame_map[4];
extern unsigned char* frameDataPtr[4];
extern unsigned char  mem_tmp_T0[1280*720*2];
extern unsigned char  mem_tmp_T1[1280*720*2];
extern unsigned char  mem_tmp_T2[1280*720*2];
extern unsigned char  mem_tmp_T3[1280*720*2];


//vsdk::Mat uyvyMat1[4];// = {NULL};
//cv::Mat databufs[4];
int readflag;
void CFinalScene::renderToSreen()
{
    static int Flag_Next =0;
    static int index = 0;
    static time_t preTime = time(NULL);
    static int States_Flag = 0;
    const int nframes = 50;
	uint8_t* ptr = NULL;
    //changeView();
	vsdk::SMat databufs[4];
	usleep(30000);
	Timer<> timer;
	timer.start();
	//static vsdk::UMat *uyvyMat[4] = {NULL};
	//static vsdk::Mat uyvyMat1(720,1280,CV_8UC2,mem_tmp_T0);
	readflag = 1;
    for(int i = 0; i < CAMERANUM; i++)
    {
		//从摄像头设备中取出一个图像缓冲区Calib_Bird_View
		#if 0
		
		#if defined(PLATFORM_X11)
			databufs[i] = getCameraDevice().getImageBuffer(i);
		#elif defined(PLATFORM_S32V)
			MatType& databuf = getCameraDevice().getBuffer(i);
			//MatType& databuf= getCameraDevice().getImageBuffer(i);
			databufs[i] = databuf.getMat(vsdk::ACCESS_READ | OAL_USAGE_NONCACHED);
			
		#else
		#error unsupported platform
		#endif
		uint8_t* ptr = databufs[i].data;
		
		#endif
		ptr = frame_map[i].data;
		//databufs[i] = uyvyMat1.getMat(vsdk::ACCESS_RW | OAL_USAGE_CACHED);
		//  ptr =	databufs[i].data;
		#if 0       //read front.yuv back.yuv left.yuv right.yuv
		vsdk::UMat &dataBuf = getCameraDevice().getImageBuffer(i);
		vsdk::Mat mat = dataBuf.getMat(vsdk::ACCESS_READ | OAL_USAGE_CACHED);
		ptr = mat.data;
		#endif
		#if 0         //read camdata from videotask
    	if(uyvyMat[i] == NULL)
		{
            uyvyMat[i] = new vsdk::UMat(SRC_IMAGE_HEIGHT,SRC_IMAGE_WIDTH,CV_8UC2);
    	}
		databufs[i] = uyvyMat[i]->getMat(vsdk::ACCESS_WRITE | OAL_USAGE_CACHED);
		ptr = databufs[i].data;
		memcpy( (unsigned char *)ptr, mem_tmp_T0, 1280*720*2 );
		#endif
		//ptr = databufs[i].data;
	   /**********************************************************************************/
		
        updateYUYVTexture2(i,m_imageTextureID[i],ptr,SRC_IMAGE_WIDTH,SRC_IMAGE_HEIGHT);
		
		//释放摄像头设备中取出的图像缓冲区

		#if 0
		#if defined(PLATFORM_S32V)
				getCameraDevice().giveBackBuffer(i);
				//getCameraDevice().giveBackImageBuffer(i);
		#else
				getCameraDevice().giveBackImageBuffer(i);
		#endif
		#endif 
    }
	readflag = 0;
	timer.stop();
	//std::cout << "read images: " << timer.get() << std::endl;

 	static float delta[4] = {1.0, 1.0, 1.0, 1.0};
#if defined(PLATFORM_S32V)
	for (int i = 0; i < 4; ++i)
	{
		//printf("databufs[%d]: width = %d, height = %d, channels = %d\n", i, databufs[i].size().width, databufs[i].size().height, databufs[i].channels());
	}
	//timer.start();
	//calcExposureGainUYVY<cv::Vec3b>(databufs, lut, delta);
	//timer.stop();
	//std::cout << "calcExposureGain: " << timer.get() << std::endl;
#else
	//calcExposureGainBGR<cv::Vec3b>(databufs, lut, delta);
#endif

    index++;
    if(index % nframes == 0){
        Flag_Next++;
        printf("Flag_Next is %d\n",Flag_Next);
        time_t curTime = time(NULL);
        float frameRate = nframes * 1.0 / (curTime - preTime);
       printf("GPU AVM frame rate is:::::::::::::::::::: %f\n",frameRate);
        preTime = curTime;
	//States_Flag++;
	if(Flag_Next >= 4)
		Flag_Next = 0;
    }
    if(g_globalParam.m_displayMode == 1){
		static int aaa = m_imageTextureID[0];

		void* data = static_cast<void*>(delta);
		static int cnt;
		//switch (mode)

		if(SwitchChannelNum != 8)
		{
			cnt = 181;
		}
		SwitchChannelNum = 1;
		switch(SwitchChannelNum)
		{
			//case SceneMode::Scene2D:
			case 0:
				rotated = true;
				bevTransformMatrix = glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
				render2DView(0, 0, getScreenWidth(), getScreenHeight(), data);
				break;
			
			//case SceneMode::Scene2DWithSingle:
			case 1:
				bevTransformMatrix = glm::mat4(1.0);
				render2DView(birdEyeViewX, birdEyeViewY, birdEyeViewWidth, birdEyeViewHeight, data);
				renderTrail(birdEyeViewX, birdEyeViewY, birdEyeViewWidth, birdEyeViewHeight, false);
				renderSingleView(0,singleViewX, singleViewY, singleViewWidth, singleViewHeight, data);
				renderTrail(singleViewX, singleViewY, singleViewWidth, singleViewHeight, true);
				Generate_Image_View("/data/opengl_new/direction_front.bmp",810, 0, 320, 270);
				Generate_Image_View("/data/opengl_new/warningLogo.bmp",810+320, 0, 800, 270);
				break;
			case 2:
				bevTransformMatrix = glm::mat4(1.0);
				render2DView(birdEyeViewX, birdEyeViewY, birdEyeViewWidth, birdEyeViewHeight, data);
				renderTrail(birdEyeViewX, birdEyeViewY, birdEyeViewWidth, birdEyeViewHeight, false);
				renderSingleView(1,singleViewX, singleViewY, singleViewWidth, singleViewHeight, data);
				renderTrail(singleViewX, singleViewY, singleViewWidth, singleViewHeight, true);
				Generate_Image_View("/data/opengl_new/direction_back.bmp",810, 0, 320, 270);
				Generate_Image_View("/data/opengl_new/warningLogo.bmp",810+320, 0, 800, 270);
				break;
			case 3:  
				bevTransformMatrix = glm::mat4(1.0);
				render2DView(birdEyeViewX, birdEyeViewY, birdEyeViewWidth, birdEyeViewHeight, data);
				renderTrail(birdEyeViewX, birdEyeViewY, birdEyeViewWidth, birdEyeViewHeight, false);
				renderSingleView(2,singleViewX, singleViewY, singleViewWidth, singleViewHeight, data);
				renderTrail(singleViewX, singleViewY, singleViewWidth, singleViewHeight, true);
				Generate_Image_View("/data/opengl_new/direction_left.bmp",810, 0, 320, 270);
				Generate_Image_View("/data/opengl_new/warningLogo.bmp",810+320, 0, 800, 270);
				break;
			case 4:
				bevTransformMatrix = glm::mat4(1.0);
				render2DView(birdEyeViewX, birdEyeViewY, birdEyeViewWidth, birdEyeViewHeight, data);
				renderTrail(birdEyeViewX, birdEyeViewY, birdEyeViewWidth, birdEyeViewHeight, false);
				renderSingleView(3,singleViewX, singleViewY, singleViewWidth, singleViewHeight, data);
				renderTrail(singleViewX, singleViewY, singleViewWidth, singleViewHeight, true);
				Generate_Image_View("/data/opengl_new/direction_right.bmp",810, 0, 320, 270);
				Generate_Image_View("/data/opengl_new/warningLogo.bmp",810+320, 0, 800, 270);
				break;
			//case SceneMode::Scene2DWithZoomFront:
			//case SceneMode::Scene2DWithZoomRear:
			case 5:
			{
				float yoffset = (-0.5);
				bevTransformMatrix = glm::mat4(1.0);
				render2DView(birdEyeViewX, birdEyeViewY, birdEyeViewWidth, birdEyeViewHeight, data);
				bevTransformMatrix = glm::scale(glm::mat4(1.0), glm::vec3(2.0, 2.0, 0.0));
				bevTransformMatrix = glm::translate(bevTransformMatrix, glm::vec3(0.0, yoffset, 0.0));
				render2DView(singleViewX, singleViewY, singleViewWidth, singleViewHeight, data);
				Generate_Image_View("/data/opengl_new/direction_front.bmp",810, 0, 320, 270);
				Generate_Image_View("/data/opengl_new/warningLogo.bmp",810+320, 0, 800, 270);
				break;
			}
			case 6:
			{
				float yoffset = (0.5);
				bevTransformMatrix = glm::mat4(1.0);
				render2DView(birdEyeViewX, birdEyeViewY, birdEyeViewWidth, birdEyeViewHeight, data);
				bevTransformMatrix = glm::scale(glm::mat4(1.0), glm::vec3(2.0, 2.0, 0.0));
				bevTransformMatrix = glm::translate(bevTransformMatrix, glm::vec3(0.0, yoffset, 0.0));
				render2DView(singleViewX, singleViewY, singleViewWidth, singleViewHeight, data);
				Generate_Image_View("/data/opengl_new/direction_back.bmp",810, 0, 320, 270);
				Generate_Image_View("/data/opengl_new/warningLogo.bmp",810+320, 0, 800, 270);
				break;
			}
			#if 0
			//case SceneMode::Scene2DWithZoomLeft:
			//case SceneMode::Scene2DWithZoomRight:
			case 6:
			{
				float xoffset = (mode == SceneMode::Scene2DWithZoomLeft ? 0.5 : -0.5);
				bevTransformMatrix = glm::mat4(1.0);
				render2DView(birdEyeViewX, birdEyeViewY, birdEyeViewWidth, birdEyeViewHeight, data);
				renderTrail(birdEyeViewX, birdEyeViewY, birdEyeViewWidth, birdEyeViewHeight, false);

				bevTransformMatrix = glm::scale(glm::mat4(1.0), glm::vec3(2.0, 2.0, 1.0));
				bevTransformMatrix = glm::translate(bevTransformMatrix, glm::vec3(xoffset, 0.0, 0.0));
				render2DView(singleViewX, singleViewY, singleViewWidth, singleViewHeight, data);
				break;
			}
			#endif 
			//case SceneMode::Scene2DWithZoomLeftRight:
			case 7:
			{
				float xoffset = 0.5;
				float scale = 2.5;
				bevTransformMatrix = glm::mat4(1.0);
				render2DView(birdEyeViewX, birdEyeViewY, birdEyeViewWidth, birdEyeViewHeight, data);
				renderTrail(birdEyeViewX, birdEyeViewY, birdEyeViewWidth, birdEyeViewHeight, false);

				bevTransformMatrix = glm::scale(glm::mat4(1.0), glm::vec3(scale, scale, 0.0));
				bevTransformMatrix = glm::translate(bevTransformMatrix, glm::vec3(xoffset, 0.0, 0.0));
				renderSingleView(2, singleViewX, singleViewY, singleViewWidth / 2, singleViewHeight, data);

				bevTransformMatrix = glm::scale(glm::mat4(1.0), glm::vec3(scale, scale, 0.0));
				bevTransformMatrix = glm::translate(bevTransformMatrix, glm::vec3(-xoffset, 0.0, 0.0));
				renderSingleView(3, singleViewX + singleViewWidth / 2, singleViewY, singleViewWidth / 2, singleViewHeight, data);
				Generate_Image_View("/data/opengl_new/direction_left_right.bmp",810, 0, 320, 270);
				Generate_Image_View("/data/opengl_new/warningLogo.bmp",810+320, 0, 800, 270);
				break;
			}
			//case SceneMode::SceneSingle:
			//case 2:
			//	renderSingleView(0, 0, getScreenWidth(), getScreenHeight(), data);
			//	break;
			//case SceneMode::Scene3D:
			case 8:
				{	
					
					Timer<> timer;
					timer.start();
					if(cnt <= 180)
					{
						cnt++;
						xuanzhuan = 2*cnt*3.141592654 / 180.0;
					}
					render3DView(0, 0, getScreenWidth(), getScreenHeight(), data);
					timer.stop();
					std::cout << "render3DView: " << timer.get() << std::endl;
				}
				break;
			//case SceneMode::Scene2DWith3D:
			case 9:
				bevTransformMatrix = glm::mat4(1.0);
				render3DView(threeDViewX, threeDViewY, threeDViewWidth, threeDViewHeight, data);
				render2DView(birdEyeViewX, birdEyeViewY, birdEyeViewWidth, birdEyeViewHeight, data);
				renderTrail(birdEyeViewX, birdEyeViewY, birdEyeViewWidth, birdEyeViewHeight, false);
				Generate_Image_View("/data/opengl_new/direction_3d.bmp",810, 0, 320, 270);
				Generate_Image_View("/data/opengl_new/warningLogo.bmp",810+320, 0, 800, 270);
				break;
			default:
				break;
		}
		glViewport(0, 0, getScreenWidth(), getScreenHeight());
		#if 0
		for(int i = 0;i<0;i++)
		{
			//Generate_SingleView(Flag_Next,m_imageTextureID, delta);
			int a = index/10;
			if(a>=62)
				index = 0;
			if(Flag_Next == 0)
				Generate_Radar_Chart(0,a);
			else if(Flag_Next == 1)
				Generate_Radar_Chart(1,a);
		}
		#endif
		//Avm_ParkingTrail(0);

		// Test_Fbo(m_imageTextureID);
		// Test_Fbo_Render(m_imageTextureID);
		m_imageTextureID[0]=aaa;
    }
}
void CFinalScene::endPreviousMode(int mode)
{
}
void CFinalScene::beginCurrentMode(int mode)
{
    if(g_globalParam.m_displayMode == 1)
    {
        clearForeGround();
        getPanorama3DScene().initDrawScene(m_imageTextureID);
    }
}
void CFinalScene::onButtonUp(int times)
{
    if(g_globalParam.m_displayMode == 1)
    {
        getPanorama3DScene().getTrackBall()->incrementPhei(-ADJUST_TIMES * times);
    }
}
void CFinalScene::onButtonDown(int times)
{
    onButtonUp(-times);
}

void CFinalScene::onButtonLeft(int times)
{
    if(g_globalParam.m_displayMode == 1)
    {
        getPanorama3DScene().getTrackBall()->incrementTheta(-ADJUST_TIMES * times);
    }
}
void CFinalScene::onButtonRight(int times)
{
    onButtonLeft(-times);
}
void CFinalScene::onButtonOK()
{
    endPreviousMode(g_globalParam.m_displayMode);
    g_globalParam.m_displayMode = (g_globalParam.m_displayMode + 1) % 3;
    beginCurrentMode(g_globalParam.m_displayMode);
}

void CFinalScene::onButtonZoomIn(int times)
{
	view2DScale += times * 0.1;
}


void CFinalScene::onButtonZoomOut(int times)
{
	if (view2DScale - times * 0.1 >= 1.0f)
	{
		view2DScale -= times * 0.1;
	}
}

void CFinalScene::onButtonMoveLeft(int times)
{
	hOffset -= 0.1;
}

void CFinalScene::onButtonMoveRight(int times)
{
	hOffset += 0.1;
}

void CFinalScene::onButtonMoveUp(int times)
{
	vOffset += 0.1;
}

void CFinalScene::onButtonMoveDown(int times)
{
	vOffset -= 0.1;
}

void CFinalScene::onButtonSwitchMode(SceneMode mode)
{
	this->mode = mode;
}