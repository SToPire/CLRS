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
		if (sum > max) {         //�������ֺ͸��������ʱ�����������������
			max = sum;
			lindex = temp;
			rindex = i;
		}
		else if (sum < 0) {      //���sum<0,˵����һ�����в�Ӧ��������λ�������������(1.��Ϊ��������ų�����һ���������п��Ը��� 2.��һ�����е�һ���ֿ��������ս��)
			sum = 0;			 //����sum,����һ����ʱ�����������µ����е����λ��
			temp = i + 1;        //����ǰ��2.��ԭ�򣬲���ֱ�Ӹ���lindex
		}
	}
	return { lindex,rindex,max };
}
auto dp(vector<int>&v, int begin, int end)->tuple<int, int, int> //��ϰ4.1-5,��̬�滮�������������飬���Ӷ�ΪO(n) 
{
	vector<tuple<int,int,int>> s(end - begin + 1); //s[j]��ʾ��v[j]��β�����������
	s[begin] = { begin,begin,v[begin] };
	for (int i = begin + 1; i <= end; ++i)
	{
		if (get<2>(s[i-1]) <= 0)   //�����v[i-1]��β�����������֮��Ϊ��������ô��v[i]��β��������������v[i]����
			s[i] = { i,i,v[i] };
		else
			s[i] = { get<0>(s[i - 1]),i,get<2>(s[i - 1]) + v[i] };//�����Ϊv[i-1]�����������ƴ����v[i]
	}
	int max = get<2>(s[begin]);
	int maxindex = 0;
	for (int i = begin + 1; i <= end; ++i) //�ҳ�����s[i]
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

