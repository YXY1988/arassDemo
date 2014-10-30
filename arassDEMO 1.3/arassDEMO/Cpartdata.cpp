/**************************************************************************************/
/**零件信息读取，只负责生成零件对象，存储零件对象信息，可以用GetPartMes调用存储的信息**/
/***操作步名|零件数=装配步数|动画类型|零件起点|零件终点|零件模型路径|文字|音频|工具****/
/**************************************************************************************/
#pragma once

#include <osgDB//ReadFile>
#include <osg/Matrix>
#include <sstream>
#include <iostream>
#include <osg/Array>
#include "CPartData.h"

using namespace std;


#define SPIRAL           0
#define TRANSLATIONAL    1  //默认平移动画
#define TOOLS            0
#define HANDY            1  //默认徒手装配
#define BASE             0
#define CURRENT          1  //默认模型为当前件

//构造函数,初始化对象
CPartData::CPartData()
{
	Ass_Num    = 0;
	Ass_Name   = "";
	part_CID    = -1;
	part_TYPE  = CURRENT;
	anim_TYPE  = TRANSLATIONAL;
	tool_TYPE  = HANDY;
	CurrentPartPath = "";
	BasePartPath    = "";
	ToolPath		= "";
	AudioPath		= "";
	TextString		= ""; 
}

CPartData::~CPartData()
{
	Ass_Num    = 0;
	Ass_Name   = "";
	part_CID    = -1;
	part_TYPE  = CURRENT;
	anim_TYPE = TRANSLATIONAL;
	tool_TYPE  = HANDY;
	CurrentPartPath = "";
	BasePartPath    = "";
	ToolPath		= "";
	AudioPath		= "";
	TextString		= ""; 
}

void CPartData::ReadPartData(ifstream& infile)
{
	int r_Num,r_CID,r_BID;
	double CPSmArray [4][4];
	double CPEmArray [4][4];
	string str,r_aName,r_CPath,r_BPath,r_aTYPE,r_pTYPE;

	//读入零件开始标志
	infile>>str;
	if(str!="PartBegin")
	{
		cout<<"Bad luck"<<endl;
		exit(0);
	}

	//读入当前任务名称
	infile>>str;
	SetStepName(r_aName);

	//读入基准件ID
	infile>>r_BID;
	SetPartBID(r_BID);

	//读入当前件ID
	infile>>r_CID;
	SetPartCID(r_CID);

/*
	//设置步骤名称
	stringstream ss;
	string sID;
	ss<<r_CID;
	ss>>sID;
	Ass_Name = "Ass_Name" + sID;

*/
	//读入装配动画类型
	infile>>r_aTYPE;
	SetAnimType(r_aTYPE);

	//读入零件类型
	infile>>r_pTYPE;
	SetPartType(r_pTYPE);

	//读入当前零件起点矩阵
	infile>>str;
	if(str!="SMatrixBegin")
	{
		cout<<"Bad luck"<<endl;
		exit(0);
	}

	infile>>CPSmArray[0][0];
	infile>>CPSmArray[0][1];
	infile>>CPSmArray[0][2];
	infile>>CPSmArray[0][3];
	infile>>CPSmArray[1][0];
	infile>>CPSmArray[1][1];
	infile>>CPSmArray[1][2];
	infile>>CPSmArray[1][3];
	infile>>CPSmArray[2][0];
	infile>>CPSmArray[2][1];
	infile>>CPSmArray[2][2];
	infile>>CPSmArray[2][3];
	infile>>CPSmArray[3][0];
	infile>>CPSmArray[3][1];
	infile>>CPSmArray[3][2];
	infile>>CPSmArray[3][3];

	CPSm.set(CPSmArray[0][0],CPSmArray[0][1],CPSmArray[0][2],CPSmArray[0][3],
		CPSmArray[1][0],CPSmArray[1][1],CPSmArray[1][2],CPSmArray[1][3],
		CPSmArray[2][0],CPSmArray[2][1],CPSmArray[2][2],CPSmArray[2][3],
		CPSmArray[3][0],CPSmArray[3][1],CPSmArray[3][2],CPSmArray[3][3]);

	//读入当前零件终点矩阵
	infile>>str;
	if(str!="EMatrixBegin")
	{
		cout<<"Bad luck"<<endl;
		exit(0);
	}

	infile>>CPEmArray[0][0];
	infile>>CPEmArray[0][1];
	infile>>CPEmArray[0][2];
	infile>>CPEmArray[0][3];
	infile>>CPEmArray[1][0];
	infile>>CPEmArray[1][1];
	infile>>CPEmArray[1][2];
	infile>>CPEmArray[1][3];
	infile>>CPEmArray[2][0];
	infile>>CPEmArray[2][1];
	infile>>CPEmArray[2][2];
	infile>>CPEmArray[2][3];
	infile>>CPEmArray[3][0];
	infile>>CPEmArray[3][1];
	infile>>CPEmArray[3][2];
	infile>>CPEmArray[3][3];

	CPEm.set(CPEmArray[0][0],CPEmArray[0][1],CPEmArray[0][2],CPEmArray[0][3],
		CPEmArray[1][0],CPEmArray[1][1],CPEmArray[1][2],CPEmArray[1][3],
		CPEmArray[2][0],CPEmArray[2][1],CPEmArray[2][2],CPEmArray[2][3],
		CPEmArray[3][0],CPEmArray[3][1],CPEmArray[3][2],CPEmArray[3][3]);

	//读入当前零件模型路径
	infile>>r_CPath;
	SetCurrentPartPath(r_CPath);
	
/*
	//读入基准零件模型路径，基准零件未必是上一个零件
	infile>>r_BPath;
	SetBasePartPath(r_BPath); */

	infile>>str;
	if (str!="PartEnd")
	{
		cout<<"Bad luck"<<endl;
		exit(0);
	}
	else
		cout<<"All done, good luck"<<endl;
	
}

