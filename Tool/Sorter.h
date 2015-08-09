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
		/*                 ����˵�����Դ�С��������Ϊ��               */
		/*                                                            */
		/**************************************************************/

		//ð�����򣬶�������n-��ɨ�裬ÿһ�˰�δ��λ��Ԫ���е�����Ԫ��
		//�ŵ�����ȷ��λ���ϣ�ÿһ��ɨ������������һ��Ԫ�ؿ�ʼ��������
		//����һ��Ԫ�رȽϣ�������ں�һԪ�ؾͽ������ߣ����۽��������
		//��һ�˵����Ԫ�ص�����Ӧ���ڵ�λ��֮ǰ����ԭ����һԪ�����ڵ�λ
		//�ÿ�ʼ�ظ���������
		void BufferSort(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				//i�Ӻ���,����Ԫ�طŵ����һ��λ����
				for (int i = end; i > start; --i)
				{
					//j < i������ǡ���һ�˵����Ԫ�ص�����Ӧ
					//���ڵ�λ��֮ǰ������˼
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

		//��һ��Ԫ��������ģ�����ڶ���Ԫ��С�ڵ�һ��Ԫ�أ��������ߵ�λ�ã�
		//��ʱǰ�������Ԫ��������ģ�������Ԫ�ؿ�����һ������ǰ������Ԫ��
		//��ɵ�������У��������Լ���λ�ã����Թ�������λ�ã����Ե�����Ԫ
		//�ؿ����ҵ��Լ�λ�ã��������һֱ�ظ���������������һ��Ԫ��
		//����ʵ����������̿��Կ������Լ��Ϊ1��һ��shell����
		void InsertSort(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				// gap = 1��һ��shell����
				shell_sort_once(values, start, end, 1);
			}
		}

		//�ڼ򵥲���������ÿ��Ԫ����Ҫ�Ӻ���ǰ˳������ǰ����������Ѱ���Լ���
		//λ�ã���������ҹ���ʹ�ö��ֲ��ң����γ��˶��ֲ������򣬼���һ��Ԫ��
		//BӦ�÷���Ԫ��A��λ�ú󣬶�A�ж��ֵ����ôӦ�ò������һ��A��λ�ã�Ȼ
		//���B�ŵ����A��λ��֮���������Լ���Ԫ���ƶ��Ĵ���
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

		//�������е�ĳ��Ԫ����Ϊ��Ŧ����С����Ŧ��Ԫ�طŵ���Ŧ����ߣ�
		//������Ŧ��Ԫ�ض��ŵ���Ŧ���ұߣ�������̽������֣�Ȼ������Ŧ
		//��ߵ����к���Ŧ��ߵ������в��ϻ��֣�ֱ������������ֻ���в�
		//����һ��Ԫ��,���ֽ���������Ҳ������ˣ����ŵĹؼ����ǻ��֣�
		//���ݲ�ͬ�Ļ��ַ�ʽ���͵õ��˲�ͬ�汾�Ŀ��ų���
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
		//��һ����������Ԫ�ظ���Ϊ5~25ʱ������ʹ�û��ֵݹ��ʵ�ֻ������е���������
		//û��ʹ��ֱ�Ӳ�������죬���ԾͿ��԰Ѳ�����������Ž�������ӿ������ٶ�
		void HybridQuickSort(ValueType values[], int start, int end,int m)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				hybrid_qsort(values, start, end, m);
			}
		}

		//��������������ظ�Ԫ�غܶ࣬����������������ȫ��Ԫ�ض�һ����
		//��ʱ������ԭ���Ŀ����㷨���ܾ�̫���ˡ����������������԰���
		//��ŦԪ��һ�����Ԫ�ض��۵��м䣬������߷���С����ŦԪ�ص�Ԫ�أ�
		//�ұ߷��ô�����ŦԪ�ص�Ԫ�أ�Ȼ�������������������п��ţ�������
		//�����㷨������·���š���·���Źؼ�����·���֡�
		void ThreeWayQuickSort(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				three_way_qsort(values, start, end);
			}
		}

		//��������������ѡ����С��ֵ����������ǵ�һ��Ԫ�أ��Ͱ������һ��λ����
		//��Ԫ�ؽ�������ʣ������������������̣�ֱ�������ڶ���Ԫ�ء�������̾���
		//��ѡ����С��Ԫ�أ�Ȼ��ѡ��ڶ�С��Ԫ�ء�����˽���ѡ������
		void SelectSort(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				select_sort(values, start, end);
			}
		}
		//������Ҳ����һ��ѡ������ֻ�����öѵ����ʼ�����ÿһ��ѡ����С
		//Ԫ�صĹ��̡���Ϊ��С�ѵĵ�һ��Ԫ������С�ģ���������������������
		//�н��ѣ�����С��Ԫ�ر��ŵ��˵�һ��λ�ã���ʣ�µ�Ԫ�������н��ѣ�
		//�����ظ�������̣�ֱ�������ڶ���Ԫ��
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

		//�����������ź�������У������Ǻ���һ�𣬲�Ҫ����˳���ԣ���ô�Ϳ���
		//��ô����ÿ�δӵ�һ�����л�ڶ���������ȡ��һ��Ԫ�أ��ĸ������еĵ�
		//һ��Ԫ��С��ȡ�ĸ�����һ������ȡ��֮�󣬰���һ������ֱ�ӽӵ���Ԫ��
		//ȡ��˳����õ��Ǹ����к��棬�͵õ���һ���ϲ��������б�������̽�
		//���ϲ�������������ÿ����Ԫ�غϲ�һ�Σ��õ�n/2�����У����һ�����п�
		//��ֻ��һ��Ԫ�أ���ÿ���õ������п���һ��Ԫ�أ����������ϲ���ֱ���ϲ�
		//�����е�Ԫ��
		void MergeSort(ValueType values[], int start, int end)
		{
			if (check_array_range(start, end, end - start + 1))
			{
				merge_sort(values, start, end);
			}
		}

		//�������ֹ�������Ϊ�����㷨��������Ӧ�ã����������С��k����
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

		//һ�˻����㷨
		int partition(ValueType values[], int start, int end)
		{
			//�Ե�һ��Ԫ����Ϊ��Ŧ,��������ͷ���м�ɨ��
			ValueType pivot = values[start];
			while (start < end)
			{
				//�ȴӺ���ǰɨ�裬ֱ������һ��С����Ŧ��Ԫ��
				while (start < end && !comp(values[end], pivot)) --end;
				//�����С����Ŧ��Ԫ�طŵ�startָ���λ���ϣ�
				//���Ǻ���ģ���Ϊ���Ԫ��С����Ŧ��Ҫ�ŵ�
				//��Ŧ����λ��֮ǰ
				values[start] = values[end];
				//��ʱǰָ��ָ��һ��С����Ŧ��Ԫ�أ�������һ��ѭ���������ƽ�ǰָ��
				//��ǰ����ɨ�裬ֱ��ǰָ������һ��������Ŧ��Ԫ��
				while (start < end && !comp(pivot, values[start])) ++start;
				//�ղź�ָ��ָ����һ��С����Ŧ��Ԫ�أ����Ԫ�طŵ���ǰָ���ƽ�
				//֮ǰ��λ���ϣ�ǰָ���ƽ�������ָ����һ��������Ŧ��Ԫ�أ�
				//���ð����ŵ���ָ��ָ���λ����
				values[end] = values[start];
				//��ʱ,ǰָ��ָ���Ԫ����һ��������Ŧ��Ԫ�أ��������Ԫ������Ч�ģ�
				//���start��û������end����ô���ѭ�����������ָ��Ҳ������ҵ�
				//һ��С����Ŧ��Ԫ�أ��ŵ�startλ���ϣ������ָ��û���ҵ�����
				//һ��Ԫ�أ���ôstart�����end������start�����ƽ�����
				//���Լ���ֵ��ֵһ�Σ��������λ���ϵ�Ԫ�ػ�����Ч�ģ����ѭ������
			}
			//���ѭ��������startλ�õ�ֵ����Ч�ģ���ǰ���ֵС�ڻ������Ŧ��
			//�����ֵ���ڻ������Ŧ,���ǰ���Ŧ�ŵ�startλ���ϣ��������һ�λ���
			values[start] = pivot;
			//startλ�þ�����Ŧ������ڵ�λ��
			return start;
		}

		//�ڻ����������ѡһ������Ϊ��Ŧ�������͵�һ��λ�õ�Ԫ�ؽ�����
		//�ٵ���partition����
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
		//ȡ�����ס�β���м�����Ԫ�أ�������Ԫ�ص��м�ֵ��Ȼ������͵�һ��
		//λ�õ�Ԫ�ؽ������ٵ���partition����
		int median3_partition(ValueType values[], int start, int end)
		{
			int mid = (start + end) / 2;
			int k = mid;
			if (comp(values[k], values[start]) && comp(values[start],values[end])) k = start;
			else if (comp(values[start], values[k]) && comp(values[end], values[start])) k = end;
			if (k != start) swap(values[k], values[start]);
			return partition(values, start, end);
		}
		//�����仮��Ϊ���Σ�ǰ����С����Ŧ��Ԫ�أ��м�������Ŧ��ȵ�Ԫ�أ������
		//������Ŧ��Ԫ��.����partition���̣��е�����������ǰָ������һ������Ŧ
		//��ȵ�Ԫ��ʱ�������ŵ�����ǰ��,��ָ������һ������Ŧ��ȵ�Ԫ���ǰ�����
		//��Ρ�partition�����������������������£���6Ϊ��Ŧ��������666234567899666��
		//ע���м���һ����Ŧ��Ȼ���ٽ����ߵ���Ŧ�������м���
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
		//һ��ϣ������ȡ��һ�����gap����ԭ������ÿ��gap����������Ϊһ�飬
		//���磬ԭ����Ϊ12 11 10 9 8 7 6 5 4 3 2 1��gapΪ3����12 9 6 3Ϊһ�飬
		//11 8 5 2Ϊһ�飬10 7 4 1Ϊһ�顣Ȼ���ÿһ����в������򡣲�������
		//�Ǵӵڶ������𣬰�˳�������뵽ǰ�������еĺ���λ�ã���12 9 6 7Ϊ����
		//9С��12�������Ƚ�9�����Ƶ�һ����ʱ�����У�Ȼ��12���Ƶ�9���ڵ�λ�ã�
		//�ٽ�9���Ƶ�12ԭ����λ���ϣ�����9 12���ź����ˡ�6��ǰ����������С���Ƚ�
		//6���Ƶ���ʱ�����У�Ȼ��9 12������һ��λ�ã��ٽ�6�ŵ�9���ڵ�λ�ã�7С��9��
		//12������6�����Խ�9��12�����һ��λ�ã���7���뵽�ճ�����λ���ϣ������������
		void shell_sort_once(ValueType values[], int start, int end, int gap)
		{
			for (int i = start + gap; i <= end; ++i)   //�������
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
		//�鲢����鲢�׶β���
		void merge(ValueType values[], int start, int connect, int end)
		{
			int length1 = connect - start + 1,
				length2 = end - connect;
			//ֻ�轫ǰ���Ԫ�ظ��Ƴ��������ˣ��Ұ�ξͷ���
			//ԭ���������У������е�ͨ����Ϊ������ǰ��κ�
			//��������д��ԭ����ʱ��Ҫô�Ѹ��Ƴ�����Ԫ��
			//����д��ȥ��λ�øոչ���Ҫô��ԭ����ȥһ����
			//�ŵ�ǰ�棬��ʱ��������ճ�һ��λ�ã�ʹ��ԭ
			//������ʣ��Ŀ���λ�������õ���ǰ�������ʱʣ��
			//Ԫ�صĸ���
			ValueType* left = new ValueType[length1],    //ÿ�ε���merge��������ڴ棬��ʵ��
				                                         //��ʹ��һ��ȫ���ڴ�ռ����������
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
			//ǰ�����仹��ʣ�࣬��ô˵����������Ѿ�ȡ�գ�
			//ֱ�Ӱ�ǰ������ʣ��Ԫ�ظ��Ƶ�ԭ�����У�����
			//������仹��ʣ�࣬�����Ѿ���λ
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