#include<iostream>
#include<vector>
using namespace std;
void print(vector<int>& a, vector<int>& ans, int i)
{
	if (ans[i] != -1) print(a, ans, ans[i]);
	cout << a[i] << ' ';
}
int main()
{
	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<int> l(n,1);
	vector<int> ans(n, -1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (a[j] < a[i] && l[i] < l[j] + 1) {
				l[i] = l[j] + 1;
				ans[i] = j; //记录当前l[i]是在哪个l[j]的基础上+1得来，亦即LIS上一项的下标
			}
		}
	}
	int max = 0, init;
	for (int i = 0; i < n; i++) {
		if (l[i] > max) {
			max = l[i];
			init = i;
		}
	}
	print(a, ans, init);
	system("pause");
}