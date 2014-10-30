/**************************************************************************************/
/**零件信息读取，只负责生成零件对象，存储零件对象信息，可以用GetPartMes调用存储的信息**/
/***操作步名|零件数=装配步数|动画类型|零件起点|零件终点|零件模型路径|文字|音频|工具****/
/**************************************************************************************/

#pragma once
#include <osgDB/ReadFile>
#include <osg/Matrix>
#include <sstream>
#include <iostream>
#include <list>

#define SPIRAL           0
#define TRANSLATIONAL    1  //默认平移动画
#define TOOLS            0
#define HANDY            1  //默认徒手装配
#define BASE             0
#define CURRENT          1  //默认模型为当前件

using namespace std;


	class CPartData
	{
	private:
		int Ass_Num;	//零件总数目=装配步骤总数目
		string Ass_Name;//对应装配步骤名称;
		int part_BID;   //基准件ID
		int part_CID;   //零件ID
		int anim_TYPE;//动画类型，TRANSLANTIONAL=1, SPIRAL=0
		int part_TYPE; //零件类型，CURRENT=1，BASE=0
		int tool_TYPE; //工具类型，TOOLS=0，HANDY=1
		osg::Matrix CPSm;//起始位置矩阵
		osg::Matrix CPEm;//终止位置矩阵
		string CurrentPartPath;//模型存放路径
		string BasePartPath;//基准件模型路径
		string ToolPath;//工具模型路径
		string AudioPath;//音频信息路径
		string TextString;//文字内容
	public: 
		
		CPartData();
		~CPartData();

		void SetAssStepNum(int r_Num)
		{
			Ass_Num=r_Num;
		}
		int GetAssStepNum()
		{
			return Ass_Num;
		}
		void SetStepName(string r_Name)
		{
			Ass_Name = r_Name;
		}
		string	GetStepName()
		{
			return Ass_Name ;
		}
		void SetPartBID(int r_BID)
		{
			part_BID=r_BID;
		}
		int GetPartBID()
		{
			return part_BID;
		}
		void SetPartCID(int r_CID)
		{
			part_CID=r_CID;
		}
		int GetPartID()
		{
			cout<<part_CID<<endl;
			return part_CID;
		}
		void SetAnimType(string r_aTYPE)
		{
			if(r_aTYPE=="TRANSLATIONAL")
				anim_TYPE = TRANSLATIONAL;
			else if(r_aTYPE == "SPIRAL")
				anim_TYPE = SPIRAL;
			else exit(0);
			cout<<"anim_TYPE"<<" "<<anim_TYPE<<endl;
		}
		int GetAnimType()
		{
			return anim_TYPE;
		}
		void SetPartType(string r_pTYPE)
		{
			if (r_pTYPE=="BASE")
				part_TYPE = BASE;
			else if (r_pTYPE=="CURRENT")
				part_TYPE = CURRENT;
			else exit(0);
			cout<<"part_TYPE"<<" "<<part_TYPE<<endl;
		}
		int GetPartType()
		{
			return part_TYPE;
		}
		void SetStartMatrix();
		osg::Matrix GetStartMatrix()
		{
			return CPSm;
		}
		void SetEndMatrix();
		osg::Matrix GetEndMatrix()
		{
			return CPEm;
		}		
		void SetCurrentPartPath(string r_CPath)
		{
			CurrentPartPath=r_CPath;
		}
		string GetCurrentPartPath()
		{
			return CurrentPartPath;
		}
		void SetBasePartPath(string r_BPath)
		{
			BasePartPath=r_BPath;
		}
		string GetBasePartPath()
		{
			return BasePartPath;
		}
		void ReadPartData(ifstream& infile);

		/*暂时不考虑的内容：工具，音频，文字*/
		/*
		void SetToolPath(string r_ToolPath)
		{
			ToolPath=r_ToolPath;
		}
		string GetToolPath()
		{
			return ToolPath;
		}
		void SetAudioPath(string r_AudioPath)
		{
			AudioPath = r_AudioPath;
		}
		string GetAudioPath()
		{
			return AudioPath;
		}
		void SetTextString(string r_Text)
		{
			TextString = r_Text;
		}
		string GetTextString()
		{
			return TextString;
		}
		*/
	};
