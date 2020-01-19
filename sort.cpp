#include <iostream>
#include <string>
#include <cmath>
#include <math.h>

using namespace std;
typedef long int elemtype;
int N;

void bubble_sort(long int a[])
{
	for (int i = 0; i < N; i++)
	{
		int flag = 0;
		for (int j = 0; j < N - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				long int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				flag = 1;
			}
		}
		if (flag == 0)
		{
			return;
		}
	}
}

void Insert_sort(elemtype a[], int n )
{
	for (int i = 1; i < n; i++)
	{
		int j;
		elemtype tmp = a[i];
		for (j = i; j > 0 && tmp < a[j - 1]; j--)
		{
			a[j] = a[j - 1];
		}
		a[j] = tmp;
	}
}

void Shell_sort(elemtype a[])
{
	int k;
	int Increment = N / 2;
	for (Increment = N / 2; Increment >= 1; Increment /= 2)
	{
		for (int j = Increment; j < N; j++)
		{
			int tmp = a[j];
			for (k = j; k - Increment >= 0; k -= Increment)
			{
				if (tmp < a[k - Increment])
				{
					a[k] = a[k - Increment];
				}
				else break;
			}
			a[k] = tmp;
		}
	}
}

void swap(elemtype* a, elemtype* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void percdown(elemtype a[], int r, int N)//此函数作用：在根节点，左子和右子之间，选出最大的一个作为新的根节点，循环的作用：使得交换数据后的子节点为根的树同样满足根节点最大的条件（可以用递归实现）。
{
	int child;
	int temp;
	//for (i = N / 2; 2*i + 1 < N; i = child)
	temp = a[r]; // temp 不需要动
	for (; 2 * r + 1 < N; r = child)
	{
		child = 2 * r + 1;
		if (2 * r + 2 < N && a[2 * r + 2] > a[2 * r + 1]) //如果下标不越界而且右子大于左子
			child++;//child更新为右子的下标
		if (a[child] > temp&& child < N) //如果子确实大于个根，则交换二者的值，否则不进行任何操作，直接退出。这一步实际上完成了：根，左，右三者比较且选出最大的一个值作为根节点。
		{
			a[r] = a[child];
			a[child] = temp;
		}
		else
			break;
	}
	//a[r] = temp; //即a[child] = temp实现了a[r] 与 a[child]进行数据交换。
}

void Heap_Sort(elemtype a[])
{
	//build heap
	for (int i = N / 2; i >= 0; i--)//从每一个根节点开始调用percdown（0 - N/2）
	{
		percdown(a, i, N);
	}
	//delete max
	for (int i = N - 1; i > 0; i--) //交换数组的第一个数据和最后一个数据，然后进行一次percdown调整为大顶堆，再进行下一次循环。
	{
		swap(&a[0], &a[i]);
		percdown(a, 0, i);
	}
}

void merge(elemtype a[], elemtype tmp[], int L, int R, int RE)
{
	int LE = R - 1;
	int num = RE - L + 1;
	int L2 = L;
	while (L <= LE && R <= RE)
	{
		if (a[L] <= a[R])
		{
			tmp[L2++] = a[L++];
		}
		else if (a[R] < a[L])
		{
			tmp[L2++] = a[R++];
		}
	}
	while (L <= LE)
	{
		tmp[L2++] = a[L++];
	}
	while (R <= RE)
	{
		tmp[L2++] = a[R++];
	}
	for (int i = 0; i < num; i++, RE--)
	{
		a[RE] = tmp[RE];
	}
}

void Msort(elemtype a[], elemtype tmp[], int L, int R)
{
	int C;
	if (L < R)
	{
		C = (L + R) / 2;
		Msort(a, tmp, L, C);
		Msort(a, tmp, C + 1, R);
		merge(a, tmp, L, C + 1, R);
	}
}

void Merge_sort(elemtype a[])
{
	elemtype* tmp = new elemtype[N * sizeof(elemtype)];
	if (NULL == tmp)
	{
		cerr << "error" << endl;
		return;
	}
	else
	{
		Msort(a, tmp, 0, N - 1);
		delete[]tmp;
	}
}

elemtype median3(elemtype a[], int L, int R)
{
	int C = (L + R) / 2;
	if (a[L] > a[C]) swap(&a[L], &a[C]);
	if (a[L] > a[R]) swap(&a[L], &a[R]);
	if (a[C] > a[R]) swap(&a[C], &a[R]);
	//swap(&a[R], &a[R - 1]);
	swap(&a[R-1], &a[C]);
	return a[R-1];
}

void Qsort(elemtype a[], int L, int R)
{
	int pivot,i,j;
     
	if (L + 3 <= R)
	{    
        i = L; 
        j = R - 1;
        pivot = median3(a, L, R);
			while (1)
			{
				while (a[++i] < pivot) {}
				while (a[--j] > pivot) {}
				if (i < j)
				{
					swap(&a[i], &a[j]);
				}
				else
					break;
			}
		swap(&a[i], &a[R - 1]);	
		Qsort(a, L, i-1);
		Qsort(a, i + 1, R);
	}
    else
	Insert_sort(a + L, R - L + 1);
}

void Quick_sort(elemtype a[])
{
	Qsort(a, 0, N - 1);
}

int main()
{
	cin >> N;
	long int* a = new long int[N];
	for (int i = 0; i < N; i++)
	{
		int temp;
		cin >> temp;
		a[i] = temp;
	}
	//bubble_sort(a);
	//Insert_sort(a, N);
	//Shell_sort(a);
	//Heap_Sort(a);
	//Merge_sort(a);
	Quick_sort(a);

	for (int i = 0; i < N; i++)
	{
		if (i == N - 1)
			cout << a[i];
		else
			cout << a[i] << " ";
	}

	return 0;
}
