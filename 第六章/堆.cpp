#include<iostream>
#include<vector>
using namespace std;

class min_heap {
private:
	vector<int> _vi;
	int _heapSZ;
	void MIN_HEAPIFY_DOWN(int i)
	{
		int min;
		int l = 2 * i + 1, r = 2 * i + 2;
		if (l < _heapSZ && _vi[l] < _vi[i]) min = l;
		else min = i;
		if (r < _heapSZ && _vi[r] < _vi[min]) min = r;
		if (i != min) {
			swap(_vi[i], _vi[min]);
			MIN_HEAPIFY_DOWN(min);
		}
	}
	void MIN_HEAPIFY_UP(int i)
	{
		bool flag = true;
		if (i == 0) flag = false;
		while (flag) {
			if (_vi[i] < _vi[(i - 1) / 2])
				swap(_vi[i], _vi[(i - 1) / 2]);
			else flag = false;
			i = (i - 1) / 2;
		}
	}
	void BUILD_MIN_HEAP()
	{
		_heapSZ = _vi.size();
		for (int i = _heapSZ / 2; i >= 0; i--) {
			MIN_HEAPIFY_DOWN(i);
		}
	}
public:
	min_heap() :_vi(), _heapSZ(0) {};
	min_heap(vector<int> vi) : _vi(vi),_heapSZ(vi.size()) {
		BUILD_MIN_HEAP();
	}
	bool empty()
	{
		return !_heapSZ;
	}
	void push(int i)
	{
		_vi.push_back(i);
		_heapSZ++;
		MIN_HEAPIFY_UP(_heapSZ - 1);
	}
	void pop()
	{
		if (this->empty()) {
			cout << "Error.";
			return;
		}
		swap(*_vi.begin(), *_vi.rbegin());
		_vi.erase(--_vi.end());
		_heapSZ--;
		MIN_HEAPIFY_DOWN(0);
	}
	int ask()
	{
		if (this->empty()) {
			cout << "Error.";
			return -1;
		}
		return _vi[0];
	}
};
int main(void)
{
	min_heap mh;
}
