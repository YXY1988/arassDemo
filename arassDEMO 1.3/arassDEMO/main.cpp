 /*主程序，读入零件，读入动画，建立链表，更新动画*/

//osgART includes
#include<osgART/Scene>
#include <osgART/PluginManager>
#include <osgART/GeometryUtils>

//osg includes
#include <osgDB/FileUtils>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osg/Group>
#include <osg/Node>

//C++ includes
#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
#include <vector>

//Demo includes
#include "CPartData.h"
#include "CAnimData.h"
#include "CAssInstruct.h"

using namespace std;


void main()
{
	CAssInstruct assInstru;
	
	//设置模型摆放位置
	osg::ref_ptr<osg::MatrixTransform> mtry = new osg::MatrixTransform;	
	osg::Matrix modelpose; 

	modelpose.setTrans(0,250,0);
	mtry->setMatrix(modelpose);

	osg::ref_ptr<osg::Group> root1 = new osg::Group();
	
	//打开指定数据文件
	ifstream infile("DummyData1.1.txt");
	if (!infile)
		exit(0);

	//读取指定数据文件
	assInstru.ReadFromFile(infile);

	//生成动画序列
	assInstru.GenAnimVector();

	//加载动画序列
	assInstru.RunAssAnim(mtry);				    //1.2版本方法
	//mtry->addChild(anim0.SetAssAnim(part0));  //1.1版本的方法，无列表

	
	root1->addChild(mtry);
	root1->addChild( osgART::create3DAxis(50,5));

	//viewer init
	osgViewer::Viewer viewer;
	viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);
	viewer.addEventHandler(new osgViewer::StatsHandler);
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
	viewer.addEventHandler(new osgViewer::ThreadingHandler);
	viewer.addEventHandler(new osgViewer::HelpHandler);

	//AR init
	osgART::Scene* scene = new osgART::Scene();
	scene->addVideo("osgart_artoolkit","osgart_video_artoolkit","D:\\osgART\\share\\osgART\\data\\artoolkit\\WDM_camera_flipV.xml");
	scene->addVisualTracker("osgart_artoolkit","osgart_tracker_artoolkit","D:\\osgART\\share\\osgART\\data\\artoolkit\\YXY_calib_140420.dat","mode=single");
	osg::ref_ptr<osg::MatrixTransform> tracker = scene->addTrackedTransform("single;D:\\osgART\\share\\osgART\\data/artoolkit/patt.kanji;80;0;0");
	tracker->addChild(root1);
	
	viewer.setSceneData(scene);
	viewer.realize();
	viewer.run();
}