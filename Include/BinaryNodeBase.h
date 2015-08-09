#ifndef _BINARYNODEBASE_H_
#define _BINARYNODEBASE_H_

namespace MyDataStructure
{
	//��node�ṹ��Ϊ���㣬���Դ���һ���ĵ��ԣ��ڵ�
	//����ֻ����ڵ����ӵĹ��ܣ�������������ʵ�ʵ�
	//���ݳ�Ա����ν�ĵ���������õ������֣�������
	//����ֻ��Ҫӵ��һ�����ݳ�Ա�������ں�������ԣ�
	//���໹��Ҫ��ʾ��ɫ�ĳ�Ա������ʹ�÷ֲ�ṹ����
	//����
	struct BinaryNodeBase
	{
		typedef BinaryNodeBase* BasePtr;
		BasePtr parent; //Ϊ��֧�ֵ������������ָ��
		BasePtr left;
		BasePtr right;

		//�����Ա��ڵ�Ϊ�������е���Сֵ��
		//���������������һֱ��ת�������
		//�Ľڵ㣬������Ϊ��С
		BasePtr minimum()
		{
			BinaryNodeBase* res = this;
			while (res->left)
			{
				res = res->left;
			}
			return res;
		}

		//�����Ա��ڵ�Ϊ�������е����ֵ��
		//���������������һֱ��ת�����ұ�
		//�Ľڵ㣬������Ϊ���
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