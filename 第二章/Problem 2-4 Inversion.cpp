//对于归并排序的微调
#include<iostream>
#include<vector>
using namespace std;
int Merge(vector<int>& a, int p, int q, int r)
{
	int count_inversion = 0;
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
			if(left[i]!=MAX) count_inversion += n1 - i ;
		}
	}
	return count_inversion;
}
int Merge_inversion_count(vector<int>& a,int p,int r) 
{
	int count_inversion = 0;
	if (p < r)
	{
		int q = (p + r) / 2;
		count_inversion += Merge_inversion_count(a, p, q);
		count_inversion += Merge_inversion_count(a, q + 1, r);
		count_inversion += Merge(a, p, q, r);
	}
	return count_inversion;
}
int main(void) 
{
	vector<int> vi{6,5,4,3,2,1};
	cout<<Merge_inversion_count(vi, 0, vi.size() - 1);
	system("pause");
}

