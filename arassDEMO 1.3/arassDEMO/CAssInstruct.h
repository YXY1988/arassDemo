/********功能：统一 CPartData 和 CAnimData， 
/********根据CPartData生成相应的AnimData，保存在CAssInstruct里*/

#include "CAnimData.h"
#include "CPartData.h"

#include <list>

using namespace std;

class CAssInstruct
{
private:
	int Ass_Num;//装配总步数=关键帧总数
	int Part_Num;//零件总数
	
	//零件信息形成的链表
	list <CPartData*> PartList;

	//生成动画链表
	vector<CAnimData*> AnimVector;

public:

	CAssInstruct();
	~CAssInstruct();

	int GetPartID();
	int GetAnimID();

	void SetAssStepNum(int a)
	{
		Ass_Num = a;
	}

	//打开文件并读入零件信息，建立链表
	void ReadFromFile(ifstream& infile);

	//用零件链表构建动画顺序链表
	void GenAnimVector();

	//依次返回更新动画节点，用迭代器控制
	void RunAssAnim(osg::ref_ptr<osg::MatrixTransform> mt);

};

