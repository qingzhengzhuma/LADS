#ifndef _BINARYNODEBASE_H_
#define _BINARYNODEBASE_H_

namespace MyDataStructure
{
	//将node结构分为两层，可以带来一定的弹性，节点
	//基类只负责节点连接的功能，而子类增加了实际的
	//数据成员，所谓的弹性在这里得到了体现，本例的
	//子类只需要拥有一个数据成员，而对于红黑树而言，
	//子类还需要表示颜色的成员，所有使用分层结构可以
	//复用
	struct BinaryNodeBase
	{
		typedef BinaryNodeBase* BasePtr;
		BasePtr parent; //为了支持迭代器，增设该指针
		BasePtr left;
		BasePtr right;

		//查找以本节点为根的树中的最小值，
		//如果有左子树，则一直左转到最左边
		//的节点，否则本身为最小
		BasePtr minimum()
		{
			BinaryNodeBase* res = this;
			while (res->left)
			{
				res = res->left;
			}
			return res;
		}

		//查找以本节点为根的树中的最大值，
		//如果有右子树，则一直右转到最右边
		//的节点，否则本身为最大
		BasePtr maximum()
		{
			BinaryNodeBase* res = this;
			while (res->right)
			{
				res = res->right;
			}
			return res;
		}

	};
}



#endif