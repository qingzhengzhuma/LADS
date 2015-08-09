#ifndef _SEARCHTREEITERATORBASE_H_
#define _SEARCHTREEITERATORBASE_H_

namespace MyDataStructure
{
	//����������������
	struct  SearchTreeIteratorBase
	{
		typedef BinaryNodeBase::BasePtr BasePtr;
		BasePtr node;

		//�õ������ƶ�����һ���ڵ�
		void Increament()
		{
			//���������ָʾ�Ľڵ������ӽڵ㣬
			//���Ը����ӽڵ�Ϊ����������Сֵ��
			//�������һ����������ָʾ�Ľڵ�
			if (node->right) node = node->right->minimum();
			else
			{
				//���������ǰָʾ�Ľڵ������ӽ�
				//�㣬����Ҫ����������һ���������ӽڵ�
				//�Ľڵ㣬�����ǰָʾ�Ľڵ������ӽڵ㣬
				//��ô���ڵ�����ˡ���ͼ���ݲ���������������
				//�ĵ��㷨
				BasePtr p = node->parent;
				//���ڵ�ĸ��ڵ�Ϊnullptr,��Ҫע��
				while (p && p->right == node)
				{
					node = p;
					p = p->parent;
				}
				node = p;
			}
		}

		//�õ������ƶ�����һ���ڵ㣬��Increament
		//�㷨��ͬС�죬�ԳƵؿ���
		void Decreament()
		{
			if (node->left) node = node->left->maximum();
			else
			{
				BasePtr p = node->parent;
				while (p && p->left == node)
				{
					node = p;
					p = p->parent;
				}
				node = p;
			}
		}

		//ģ��ָ����Ϊ����������һ������ָ��
		bool operator ==(const SearchTreeIteratorBase& it)
		{
			return this->node == it.node;
		}

		bool operator != (const SearchTreeIteratorBase& it)
		{
			return this->node != it.node;
		}
	};
}

#endif