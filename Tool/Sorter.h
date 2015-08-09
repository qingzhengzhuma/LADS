#ifndef _SORTER_H_
#define _SORTER_H_

#include "../include/Functor.h"
#include <cstdlib>
#include <time.h>
using namespace MyDataStructure;

namespace MyTools
{
	template<typename Value,typename Compare = MyDataStructure::less<Value>>
	class Sorter
	{
	public:
		typedef Value ValueType;
	public:

		/**************************************************************/
		/*                                                            */
		/*                 以下说明均以从小到大排序为例               */
		/*                                                            */
		/**************************************************************/

		//冒泡排序，对数组做n-趟扫描，每一趟把未就位的元素中的最大的元素
		//放到他正确的位置上，每一趟扫描从输入数组第一个元素开始，依次与
		//它后一个元素比较，如果大于后一元素就交换两者，无论交换与否，在
		//这一趟的最大元素到达他应该在的位置之前，从原来后一元素所在的位
		//置开始重复上述过程
		void BufferSort(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				//i从后起,最大的元素放到最后一个位置嘛
				for (int i = end; i > start; --i)
				{
					//j < i，这就是“这一趟的最大元素到达他应
					//该在的位置之前”的意思
					for (int j = start; j < i; ++j)
					{
						if (comp(values[j + 1], values[j]))
						{
							swap(values[j + 1], values[j]);
						}
					}
				}
			}
		}

		//第一个元素是有序的，如果第二个元素小于第一个元素，交换二者的位置，
		//此时前面的两个元素是有序的，第三个元素看做是一个插入前面两个元素
		//组成的有序表中，加上它自己的位置，所以共有三个位置，所以第三个元
		//素可以找到自己位置，这个过程一直重复到输入数组的最后一个元素
		//但是实际上这个过程可以看成是以间隔为1的一趟shell排序
		void InsertSort(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				// gap = 1的一趟shell排序
				shell_sort_once(values, start, end, 1);
			}
		}

		//在简单插入排序中每个元素需要从后往前顺序在他前面的有序表中寻找自己的
		//位置，把这个查找过程使用二分查找，就形成了二分插入排序，假设一个元素
		//B应该放在元素A的位置后，而A有多个值，那么应该查找最后一个A的位置，然
		//后把B放到这个A的位置之后，这样可以减少元素移动的次数
		void BinaryInsertSort(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				for (int i = start + 1; i <= end; ++i)
				{
					ValueType temp = values[i];
					int low = start, high = i - 1, mid = (low + high) / 2;
					
					while (low <= high)
					{
						if (comp(temp, values[mid])) high = mid - 1;
						else low = mid + 1;
						mid = (low + high) / 2;
					}
					for (int k = i; k > low; --k) values[k] = values[k - 1];
					values[low] = temp;
				}
			}
		}
		void ShellSort(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				int gap = end - start + 1;
				do 
				{
					gap = gap / 3 + 1;
					shell_sort_once(values, start, end, gap);
				} while (gap > 1);
			}
		}

		//以数组中的某个元素作为枢纽，将小于枢纽的元素放到枢纽的左边，
		//大于枢纽的元素都放到枢纽的右边，这个过程叫做划分，然后在枢纽
		//左边的序列和枢纽左边的序列中不断划分，直到划分序列中只含有不
		//多于一个元素,划分结束后，排序也就完成了，快排的关键就是划分，
		//根据不同的划分方式，就得到了不同版本的快排程序
		void QuickSort(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				quick_sort(values, start, end);
			}
		}
		void RandomizedQuickSort(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				randomized_qsort(values, start, end);
			}
		}
		void Median3QuickSort(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				median3_qsort(values, start, end);
			}
		}
		//当一个划分序列元素个数为5~25时，继续使用划分递归地实现划分序列的排序往往
		//没有使用直接插入排序快，所以就可以把插入排序与快排结合起来加快排序速度
		void HybridQuickSort(ValueType values[], int start, int end,int m)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				hybrid_qsort(values, start, end, m);
			}
		}

		//有许多输入序列重复元素很多，极端例子是序列中全部元素都一样，
		//这时候再用原来的快排算法性能就太差了。针对这种情况，可以把与
		//枢纽元素一样大的元素都聚到中间，而在左边放置小于枢纽元素的元素，
		//右边放置大于枢纽元素的元素，然后再左右两个子序列中快排，这样的
		//快排算法叫做三路快排。三路快排关键是三路划分。
		void ThreeWayQuickSort(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				three_way_qsort(values, start, end);
			}
		}

		//先在输入数组中选择最小的值，如果它不是第一个元素，就把它与第一个位置上
		//的元素交换，在剩余的子数组继续这个过程，直到倒数第二个元素。这个过程就是
		//先选择最小的元素，然后选择第二小的元素……因此叫做选择排序
		void SelectSort(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				select_sort(values, start, end);
			}
		}
		//堆排序也算是一种选择排序，只是利用堆的性质加速了每一趟选择最小
		//元素的过程。因为最小堆的第一个元素是最小的，所以先在整个输入数组
		//中建堆，则最小的元素被放到了第一个位置，在剩下的元素序列中建堆，
		//不断重复这个过程，直到倒数第二个元素
		void HeapSort(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				for (int i = start; i < end; ++i)
				{
					build_heap(&values[i], 0, end - i);
				}
			}
		}

		//假设有两个排好序的序列，将它们和在一起，并要保持顺序性，那么就可以
		//这么做：每次从第一个序列或第二个序列中取走一个元素，哪个序列中的第
		//一个元素小就取哪个，当一个序列取完之后，把另一个序列直接接到按元素
		//取走顺序放置的那个序列后面，就得到了一个合并的有序列表。这个过程叫
		//做合并。把输入数组每两个元素合并一次，得到n/2个序列，最后一个序列可
		//能只有一个元素，把每个得到的序列看做一个元素，继续两两合并，直到合并
		//完所有的元素
		void MergeSort(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				merge_sort(values, start, end);
			}
		}

		//公开划分过程是因为划分算法还有其他应用，比如查找最小第k个数
		int Partition(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				return partition(values, start, end);
			}
			return -1;
		}
		int RandomizedPartition(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				return randomized_partition(values, start, end);
			}
			return -1;
		}
		int Median3Partition(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				return median3_partition(values, start, end);
			}
			return -1;
		}

	public:
		Compare comp;
	private:
		bool check_array_range(int start, int end,int n)
		{
			if (n <= 0 ||
				start < 0 ||
				end < 0 || start > end
				|| n > end - start + 1)
				return false;
			return true;
		}

		//一趟划分算法
		int partition(ValueType values[], int start, int end)
		{
			//以第一个元素作为枢纽,从数组两头向中间扫描
			ValueType pivot = values[start];
			while (start < end)
			{
				//先从后往前扫描，直到遇到一个小于枢纽的元素
				while (start < end && !comp(values[end], pivot)) --end;
				//把这个小于枢纽的元素放到start指向的位置上，
				//这是合理的，因为这个元素小于枢纽，要放到
				//枢纽最后的位置之前
				values[start] = values[end];
				//此时前指针指向一个小于枢纽的元素，所以下一个循环总是能推进前指针
				//从前往后扫描，直到前指针遇到一个大于枢纽的元素
				while (start < end && !comp(pivot, values[start])) ++start;
				//刚才后指针指向了一个小于枢纽的元素，这个元素放到了前指针推进
				//之前的位置上，前指针推进后，现在指向了一个大于枢纽的元素，
				//正好把它放到后指针指向的位置上
				values[end] = values[start];
				//此时,前指针指向的元素是一个大于枢纽的元素，但是这个元素是无效的，
				//如果start还没有遇到end，那么外层循环会继续，后指针也许就能找到
				//一个小于枢纽的元素，放到start位置上，如果后指针没有找到这样
				//一个元素，那么start会等于end，于是start不再推进，会
				//被自己的值赋值一次，不过这个位置上的元素还是无效的，外层循环结束
			}
			//外层循环结束后，start位置的值是无效的，它前面的值小于或等于枢纽，
			//后面的值大于或等于枢纽,于是把枢纽放到start位置上，就完成了一次划分
			values[start] = pivot;
			//start位置就是枢纽最后所在的位置
			return start;
		}

		//在划分区间随机选一个数作为枢纽，把它和第一个位置的元素交换，
		//再调用partition过程
		int randomized_partition(ValueType values[], int start, int end)
		{
			if (end == start) return start;
			if (end < start) return -1;
			srand(static_cast<unsigned>(time(nullptr)));
			int i = rand();
			i = static_cast<int>((i * 1.0 / RAND_MAX) * (end - start) + start);
			swap(values[i], values[start]);
			return partition(values, start, end);
		}
		//取区间首、尾、中间三个元素，求三个元素的中间值，然后把它和第一个
		//位置的元素交换，再调用partition过程
		int median3_partition(ValueType values[], int start, int end)
		{
			int mid = (start + end) / 2;
			int k = mid;
			if (comp(values[k], values[start]) && comp(values[start],values[end])) k = start;
			else if (comp(values[start], values[k]) && comp(values[end], values[start])) k = end;
			if (k != start) swap(values[k], values[start]);
			return partition(values, start, end);
		}
		//将区间划分为三段，前段是小于枢纽的元素，中间是与枢纽相等的元素，后端是
		//大于枢纽的元素.运行partition过程，有点区别就是如果前指针遇到一个与枢纽
		//相等的元素时，把它放到区间前段,后指针遇到一个与枢纽相等的元素是把它放
		//后段。partition过程运行完后，区间的排列如下（以6为枢纽举例）：666234567899666，
		//注意中间有一个枢纽，然后再将两边的枢纽交换到中间来
		void three_way_partition(ValueType values[], int start, int end, int &left_pivot, int &right_pivot)
		{
			ValueType pivot = values[start];
			int i = start,p = start,q = end,j = end;
			while (i < j)
			{

				while (i < j)
				{
					if (comp(pivot, values[j])) --j;
					else if (values[j] == pivot) swap(values[q--], values[j--]);
					else break;
				}
				values[i] = values[j];
				while (i < j )
				{
					if (comp(values[i], pivot)) ++i;
					else if (values[i] == pivot)  swap(values[p++], values[i++]);
					else break;
				}
				values[j] = values[i];
			}
			values[i] = pivot;
			j = i + 1;
			i  -= 1;
			while (i > start && comp(values[i],values[start])) swap(values[i++], values[start++]);
			while (j < end && comp(values[end], values[j])) swap(values[j++], values[end--]);
			left_pivot = i;
			right_pivot = j;
		}
		//一趟希尔排序。取定一个间隔gap，则原数组中每隔gap个数的数分为一组，
		//例如，原数组为12 11 10 9 8 7 6 5 4 3 2 1，gap为3，则12 9 6 3为一组，
		//11 8 5 2为一组，10 7 4 1为一组。然后对每一组进行插入排序。插入排序
		//是从第二个数起，按顺序将它插入到前面序列中的合适位置，以12 9 6 7为例，
		//9小于12，所以先将9，复制到一个临时变量中，然后将12后移到9所在的位置，
		//再将9复制到12原来的位置上，这样9 12就排好序了。6比前面两个数都小，先将
		//6复制到临时变量中，然后将9 12都后移一个位置，再将6放到9所在的位置，7小于9和
		//12，大于6，所以将9和12向后移一个位置，把7插入到空出来的位置上，于是排序完成
		void shell_sort_once(ValueType values[], int start, int end, int gap)
		{
			for (int i = start + gap; i <= end; ++i)   //交叉进行
			{
				if (comp(values[i], values[i - gap]))
				{
					ValueType temp = values[i];
					int j = i - gap;
					do
					{
						values[j + gap] = values[j];
						j -= gap;
					} while (j >= start && comp(temp, values[j]));
					values[j + gap] = temp;
				}
			}
		}
		void quick_sort(ValueType values[], int start, int end)
		{
			if (start < end)
			{
				int pivot = partition(values, start, end);
				quick_sort(values, start, pivot - 1);
				quick_sort(values, pivot + 1, end);
			}
		}
		void randomized_qsort(ValueType values[], int start, int end)
		{
			if (start < end)
			{
				int pivot = randomized_partition(values, start, end);
				randomized_qsort(values, start, pivot - 1);
				randomized_qsort(values, pivot + 1, end);
			}
		}
		void median3_qsort(ValueType values[], int start, int end)
		{
			if (start < end)
			{
				int pivot = median3_partition(values, start, end);
				median3_qsort(values, start, pivot - 1);
				median3_qsort(values, pivot + 1, end);
			}
		}
		void three_way_qsort(ValueType values[], int start, int end)
		{
			if (start < end)
			{
				int left, right;
				three_way_partition(values, start, end, left, right);
				three_way_qsort(values,start, left);
				three_way_qsort(values, right, end);
			}
		}
		void hybrid_qsort(ValueType values[], int start, int end,int m)
		{
			if (end - start <= m)
				shell_sort_once(values, start, end,1);
			else 
			{
				int pivot = randomized_partition(values, start, end);
				hybrid_qsort(values, start, pivot - 1,m);
				hybrid_qsort(values, pivot + 1, end,m);
			}
		}
		void select_sort(ValueType values[], int start, int end)
		{
			for (int i = start; i < end; ++i)
			{
				int k = i;
				ValueType val = values[k];
				for (int j = i; j < end; ++j)
				{
					if (comp(values[j + 1],val))
					{
						val = values[j + 1];
						k = j + 1;
					}
				}
				if (k != i) swap(values[k], values[i]);
			}
		}
		void sift_down(ValueType values[],int start, int end)
		{
			int i = start, j = 2 * i + 1;
			ValueType temp = values[i];
			while (j <= end)
			{
				if (j < end && comp(values[j + 1],values[j] )) ++j;
				if (!comp(values[j],temp )) break;
				else
				{
					values[i] = values[j];
					i = j;
					j = 2 * i + 1;
				}
			}
			values[i] = temp;
		}
		void build_heap(ValueType values[],int start,int end)
		{
			for (int i = (end - 1) / 2; i >= start; --i)
			{
				sift_down(values,i, end);
			}
		}
		//归并排序归并阶段操作
		void merge(ValueType values[], int start, int connect, int end)
		{
			int length1 = connect - start + 1,
				length2 = end - connect;
			//只需将前半段元素复制出来就行了，右半段就放在
			//原来的序列中，这样行得通是因为复制完前半段后，
			//将排序结果写回原序列时，要么把复制出来的元素
			//重新写回去，位置刚刚够。要么从原区间去一个数
			//放到前面，此时后半段区间空出一个位置，使得原
			//区间中剩余的可用位置数正好等于前半区间此时剩余
			//元素的个数
			ValueType* left = new ValueType[length1],    //每次调用merge都会分配内存，其实可
				                                         //以使用一个全局内存空间以提高性能
				*right = &values[connect + 1];// new ValueType[length2];
			for (int i = start,j = 0; i <= connect; )
				left[j++] = values[i++];
			/*for (int i = connect + 1, j = 0; i <= end;)
				right[j++] = values[i++];*/
			int i = start, j = 0, k = 0;
			while ( j < length1 && k < length2)
			{
				if (comp(left[j], right[k])) values[i++] = left[j++];
				else values[i++] = right[k++];
			}
			//前半区间还有剩余，那么说明后半区间已经取空，
			//直接把前半区间剩余元素复制到原区间中，否则，
			//后半区间还有剩余，并且已经就位
			while ( j < length1)
			{
				values[i++] = left[j++];
			}
			/*while( k < length2)
			{
				values[i++] = right[k++];
			}*/
			delete []left;
			//delete []right;
		}

		void merge_sort(ValueType values[], int start, int end)
		{
			if (start < end)
			{
				int connect = (start + end) / 2;
				merge_sort(values, start, connect);
				merge_sort(values, connect + 1, end);
				merge(values, start, connect, end);
			}
		}
		void swap(ValueType& val1, ValueType& val2)
		{
			ValueType temp = val1;
			val1 = val2;
			val2 = temp;
		}
	};
}

#endif