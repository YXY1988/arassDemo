/*根据约束类型创建导航动画，读入类型int参数，1代表平移，0代表旋转；返回动画节点
参数化动画，输入：读到的起点、终点位姿矩阵，模型路径，动画类型
			输出：加载了相应动画的矩阵变换节点，利用该类节点的无限叠加功能*/
#pragma once
#include <osg/Matrix>
#include <osg/Array>
#include <osg/AnimationPath>
#include <osgDB/FileUtils>
#include <osg/Group>
#include <osg/Node>
#include <osgART/Scene>

#include "CPartData.h"

using namespace std;


	class CAnimData
	{  
	private:
		CPartData  partd;
		int    anim_ID;
		int    anim_TYPE;	//动画类型
		osg::Matrix  sm;	//起点矩阵
		osg::Matrix  em;	//终点矩阵
		osg::Vec3d	spos;	//起点位置
		osg::Vec3d  epos;	//终点位置
		osg::Quat   sori;	//起点姿态
		osg::Quat   eori;	//终点姿态
		
		/*osg::Vec3d	sscale;	//起点位置
		osg::Vec3d  escale;	//终点位置
		osg::Quat   soscale;	//起点姿态
		osg::Quat   eoscale;	//终点姿态*/

	public:		
		CAnimData();
		~CAnimData();

		//读取起点终点矩阵
		
		void SetAnimID()
		{
			anim_ID = partd.GetPartID();
		}
		void SetStartMatrix()
		{
			sm = partd.GetStartMatrix();
		}
		void SetEndMatrix()
		{
			em = partd.GetEndMatrix();
		}
		//设置起点终点位姿
		void SetStartPose(osg::Matrix sm)
		{
			osg::Vec3d a;
			osg::Quat  b;
			osg::Vec3d c;
			osg::Quat  d;
			sm.decompose(a,b,c,d);
			spos = a;
			sori = b;
			//sori = b;
		}
		void SetEndPose(osg::Matrix em)
		{
			osg::Vec3d a;
			osg::Quat  b;
			osg::Vec3d c;
			osg::Quat  d;
			em.decompose(a,b,c,d);
			epos = a;
			eori = b;

		}
		
		//设置动画类型
		void SetAnimType()
		{
			this->anim_TYPE = partd.GetAnimType();
		}
		//反复平移动画函数
		osg::AnimationPath* SegTransPath(osg::Vec3d a,osg::Vec3d b,osg::Quat c,osg::Quat d)
		{
			osg::AnimationPath* path1 = new osg::AnimationPath();
			path1->setLoopMode(osg::AnimationPath::NO_LOOPING);
			path1->insert(5.0*(anim_ID),osg::AnimationPath::ControlPoint(a,c));
			path1->insert(5.0*(anim_ID)+5.0,osg::AnimationPath::ControlPoint(b,d));
			//path1->insert(6.0,osg::AnimationPath::ControlPoint(a,c));
			return path1;
		}
		osg::ref_ptr<osg::MatrixTransform> SetAssAnim(CPartData partd);
		osg::ref_ptr<osg::MatrixTransform> mt;
		osg::ref_ptr<osg::MatrixTransform> getmt() const { return mt; }
		void setmt(osg::ref_ptr<osg::MatrixTransform> val) { mt = val; }
	};

