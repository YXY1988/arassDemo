/*根据约束类型创建导航动画*/
#pragma once

#include <osg/Matrix>
#include <osg/Matrixd>
#include <osg/Array>
#include <osg/AnimationPath>
#include <osgDB/FileUtils>
#include <osg/Group>
#include <osg/Node>
#include <osgART/Scene>

#include "CPartData.h"
#include "CAnimData.h"

using namespace std;

#define TRANSLATIONAL 1
#define SPIRAL        0

CAnimData::CAnimData()
{
	anim_TYPE=partd.GetAnimType();
	sm = partd.GetStartMatrix();
	em = partd.GetEndMatrix();
	spos = osg::Vec3d(0.0,0.0,0.0);
	sori = osg::Quat (0.0,0.0,0.0,0.0);
	epos = osg::Vec3d(0.0,0.0,0.0);
	eori = osg::Quat (0.0,0.0,0.0,0.0);
}
CAnimData::~CAnimData()
{
	anim_TYPE=partd.GetAnimType();
	sm = partd.GetStartMatrix();
	em = partd.GetEndMatrix();
	spos = osg::Vec3d(0.0,0.0,0.0);
	sori = osg::Quat (0.0,0.0,0.0,0.0);
	epos = osg::Vec3d(0.0,0.0,0.0);
	eori = osg::Quat (0.0,0.0,0.0,0.0);

}
osg::ref_ptr<osg::MatrixTransform> CAnimData::SetAssAnim(CPartData partd)
{
	this->partd=partd;
	//partdata = partd;
	SetStartMatrix();
	SetEndMatrix();
	SetStartPose(sm);
	SetEndPose(em);
	SetAnimType();
	SetAnimID();
	
	osg::ref_ptr<osg::MatrixTransform> mt1 = new osg::MatrixTransform();
	
	//设置起点位姿势
	mt1->setMatrix(sm);
	if(anim_TYPE==TRANSLATIONAL)

		{//读入模型
		mt1->addChild(osgDB::readNodeFile(partd.GetCurrentPartPath()));

		//呼出更新回调函数，增加到矩阵变换节点上
		mt1->addUpdateCallback(new osg::AnimationPathCallback(SegTransPath(spos,epos,sori,eori)));}
			
	else if(anim_TYPE==SPIRAL)
		{
			osg::ref_ptr<osg::MatrixTransform> circle = new osg::MatrixTransform();
			circle->addChild(osgDB::readNodeFile(partd.GetCurrentPartPath()));
			circle->addUpdateCallback(new osg::AnimationPathCallback(osg::Vec3(0.0f,0.0f,0.0f),osg::Z_AXIS,osg::inDegrees(360.0f)));
			mt1->addChild(circle);
			mt1->addUpdateCallback(new osg::AnimationPathCallback(SegTransPath(spos,epos,sori,eori)));
		}	

	//返回加载有动画的节点变换矩阵
	mt = mt1.get();
	return mt;
}








