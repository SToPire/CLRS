#include<iostream>
#include<vector>
using namespace std;
int fun_7_1_2(vector<int>& A, int p, int r) 
{
	int count = 0;
	int i = p - 1;
	for (int j = p; j <= r - 1; j++) {
		if (A[j] == A[r]) count++;
		else if (A[j] < A[r]) {
			i++;
			swap(A[i], A[j]);
		}
	}
	swap(A[i + 1], A[r]);
	return i + 1 + count / 2;
}
//注：该分割算法并不能保证相等元素都连续地位于中间部分，只是适用于此题，并能正确进行快速排序而已
int main()
{
	vector<int> vi(100, 1);
	for (int i = 1; i <= 99; i++) {
		for (int j = i+1; j <= 99; j++) {
			if (fun_7_1_2(vi, i, j) != (i + j) / 2) cout << "false" << endl;
		}
	}
	system("pause");
}