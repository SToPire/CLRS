#include<iostream>
#include<vector>
#include<tuple>
using namespace std;
auto find_max_cross_subarry(vector<int>& v, int begin, int mid, int end)-> tuple<int, int, int>
{
	int lmax = v[mid], rmax = v[mid + 1];
	int sum = v[mid];
	int lindex = mid, rindex = mid + 1;
	for (int i = mid - 1; i >= begin; --i)
	{
		sum += v[i];
		if (sum > lmax) {
			lmax = sum;
			lindex = i;
		}
	}
	sum = v[mid + 1];
	for (int i = mid + 2; i <= end; ++i)
	{
		sum += v[i];
		if (sum > rmax) {
			rmax = sum;
			rindex = i;
		}
	}
	return { lindex,rindex,lmax + rmax };
}
auto find_max_subarray(vector<int>& v, int begin, int end) ->tuple<int, int, int>
{
	if (begin == end) return{ begin,end,v[begin] };
	int mid = (begin + end) / 2;
	auto lres = find_max_subarray(v, begin, mid);
	auto rres = find_max_subarray(v, mid + 1, end);
	auto crossres = find_max_cross_subarry(v, begin, mid, end);
	if (get<2>(lres) >= get<2>(rres) and get<2>(lres) >= get<2>(crossres)) return lres;
	else if (get<2>(rres) >= get<2>(lres) and get<2>(rres) >= get<2>(crossres)) return rres;
	else return crossres;
}
auto linearComplexity(vector<int>& v, int begin, int end) ->tuple<int, int, int>
{
	int sum = 0, max = 0, lindex = 0, rindex = 0, temp = 0;
	for (int i = begin; i != end; ++i)
	{
		sum += v[i];
		if (sum > max) {         //仅当出现和更大的序列时，更新三个输出变量
			max = sum;
			lindex = temp;
			rindex = i;
		}
		else if (sum < 0) {      //如果sum<0,说明这一段序列不应该完整地位于最后结果序列中(1.因为结果序列排除掉这一段完整序列可以更大 2.这一段序列的一部分可能是最终结果)
			sum = 0;			 //重置sum,更新一个临时变量，代表新的序列的左端位置
			temp = i + 1;        //基于前述2.的原因，不能直接更新lindex
		}
	}
	return { lindex,rindex,max };
}
auto dp(vector<int>&v, int begin, int end)->tuple<int, int, int> //练习4.1-5,动态规划，遍历两遍数组，复杂度为O(n) 
{
	vector<tuple<int,int,int>> s(end - begin + 1); //s[j]表示以v[j]结尾的最大子数组
	s[begin] = { begin,begin,v[begin] };
	for (int i = begin + 1; i <= end; ++i)
	{
		if (get<2>(s[i-1]) <= 0)   //如果以v[i-1]结尾的最大子数组之和为负数，那么以v[i]结尾的最大子数组就是v[i]本身
			s[i] = { i,i,v[i] };
		else
			s[i] = { get<0>(s[i - 1]),i,get<2>(s[i - 1]) + v[i] };//否则就为v[i-1]的最大子数组拼接上v[i]
	}
	int max = get<2>(s[begin]);
	int maxindex = 0;
	for (int i = begin + 1; i <= end; ++i) //找出最大的s[i]
	{
		if (get<2>(s[i]) > max) {
			max = get<2>(s[i]);
			maxindex = i;
		}
	}
	return s[maxindex];
}
int main()
{
	vector<int> vi{ 13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7 };
	//auto res = find_max_subarray(vi, 0, vi.size() - 1);
	//auto res = linearComplexity(vi, 0, vi.size() - 1);
	auto res = dp(vi, 0, vi.size() - 1);
	cout << "Maximum subarray is:" << endl;
	for (int i = get<0>(res); i <= get<1>(res); ++i) cout << vi[i] << ' ';
	cout << endl << "with max sum of " << get<2>(res);
	system("pause");
}

