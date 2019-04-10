#include<iostream>
#include<vector>
using namespace std;
void fun_8_2_b(vector<int>& a, int i, int j)
{
	int l = i, r = j;
	while (1) {
		while (l <= j && a[l] == 0) l++;
		while (r >= i && a[r] == 1) r--;
		if (l > r) return;
		else swap(a[l], a[r]);
	}
}
void fun_8_2_e(vector<int>& a, int i, int j,int k)
{
	vector<int> pos1(k+2,0);
	for (int m = i; m <= j; m++) {
		pos1[a[m]+1]++;
	}
	for (int n = 2; n <= k+1; n++) {
		pos1[n] += pos1[n - 1];
	}
	vector<int> pos2 = pos1;
	//↑类似于计数排序中辅助数组的生成，pos[i]代表a中小于等于i-1的数的个数，pos[0]为0
	//这里把pos拷贝了一份，pos1不做修改，用于检验一个数是否在正确位置上；pos2像计数排序中那样进行修改
	for (int m = j; m >= i; ) {
		if ((m - i + 1) <= pos1[a[m] + 1] && (m - i + 1) > pos1[a[m]]) { //如果一个数在正确位置上
			pos2[a[m] + 1]--;
			m--;																							 //前移指针
		}
		else {																							 //否则把它交换到正确的位置上，不移动指针
			int temp = a[m];
			swap(a[m], a[i - 1 + pos2[a[m] + 1]]);
			pos2[temp + 1]--;
		}
	}
}
int main()
{
	/*
	cout << "请输入输入规模:";
	int n; cin >> n;
	vector<int> vi1(n);
	cout << "请输入" << n << "个0或1的数:";
	for (int i = 0; i < n; i++) {
		cin >> vi1[i];
	}
	fun_8_2_b(vi1, 0, n-1);
	for (auto a : vi1)cout << a << ' ';
	*/

	/*
	cout << "请输入输入规模:";
	int n; cin >> n;
	vector<int> vi2(n);
	cout << "请输入" << n << "个数:";
	int max = 0;
	for (int i = 0; i < n; i++) {
		cin >> vi2[i];
		if (vi2[i] > max) max = vi2[i];
	}
	fun_8_2_e(vi2, 0,n-1,max);
	for (auto a : vi2)cout << a << ' ';
	*/
	system("pause");
}