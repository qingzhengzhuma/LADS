#ifndef _UNIONFINDSET_H_
#define _UNIONFINDSET_H_
#include "Vector.h"
namespace MyDataStructure
{
	class UnionFindSet
	{
	public:
		UnionFindSet(){}
		UnionFindSet(int capacity)
		{
			for (int i = 0; i < capacity;++i)
			{
				set.PushBack(-1);
			}
		}
		UnionFindSet(const UnionFindSet& rhs)
		{
			set = rhs.set;
		}
		UnionFindSet& operator = (const UnionFindSet& rhs)
		{
			set = rhs.set;
			return *this;
		}
		int Find(int index)
		{
			if (index < 0 || index >= set.Size()) return -1;
			else if (set[index] < 0)
				return index;
			else
			{
				return set[index] = Find(set[index]);
			}
		}
		bool Union(int root1, int root2)
		{
			int s1 = Find(root1), s2 = Find(root2);
			if (s1 >= 0 && s2 >= 0 && s1 != s2)
			{
				if (set[s1] <= set[s2])
				{
					set[s1] += set[s2];
					set[s2] = s1;
					
				}
				else
				{
					set[s2] += set[s1];
					set[s1] = s2;
				}
				return true;
			}
			return false;
		}
	private:
		Vector<int> set;
	};
}

#endif