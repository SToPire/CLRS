#include<iostream>
#include<vector>
#include<windows.h>
#include<math.h>
using namespace std;
void Merge(vector<int>& a, int p, int q, int r)
{
	const int MAX = 1e9;
	int n1 = q - p + 1;
	int n2 = r - q;
	int *left = new int[n1 + 1];
	int *right = new int[n2 + 1];
	for (int i = 0; i < n1; i++)
		left[i] = a[p + i];
	for (int i = 0; i < n2; i++)
		right[i] = a[p + n1 + i];
	left[n1] = right[n2] = MAX;
	for (int i = 0, j = 0, k = p; k <= r; ++k)
	{
		if (left[i] < right[j]) {
			a[k] = left[i];
			++i;
		}
		else {
			a[k] = right[j];
			++j;
		}
	}
}
void Merge_sort(vector<int>& a, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		Merge_sort(a, p, q);
		Merge_sort(a, q + 1, r);
		Merge(a, p, q, r);
	}
}
void Insertion_sort(vector<int>& a, int p, int r)
{
	for (int k = p + 1; k <= r; ++k)
	{
		int temp = a[k];
		int i = k - 1;
		while (i >= 0 and a[i] > temp)
		{
			a[i + 1] = a[i];
			--i;
		}
		a[i + 1] = temp;
	}
}
void Merge_Insertion_sort(vector<int>& a, int p, int r, int k) //在问题规模<=k时转为插入排序
{
	if (r - p + 1 > k and p < r)
	{
		int q = (p + r) / 2;
		Merge_Insertion_sort(a, p, q, k);
		Merge_Insertion_sort(a, q + 1, r, k);
		Merge(a, p, q, r);
	}
	else
		Insertion_sort(a, p, r);
}
int main(void)
{
	vector<int> vi(10000);
	for (int i = 0; i < 10000; i++) vi[i] = 10000 - i;
	DWORD b, e;
	b = GetTickCount();
	Insertion_sort(vi, 0, vi.size() - 1);
	e = GetTickCount();
	cout << "Insertion sort finished in " << e - b << " ms." << endl;
	b = GetTickCount();
	Merge_sort(vi, 0, vi.size() - 1);
	e = GetTickCount();
	cout << "Merge sort finished in " << e - b << " ms." << endl;
	b = GetTickCount();
	Merge_Insertion_sort(vi, 0, vi.size() - 1, log(vi.size()) / log(2));
	e = GetTickCount();
	cout << "Merge sort with insertion sort optimization finished in " << e - b << " ms." << endl;
	system("pause");
}

