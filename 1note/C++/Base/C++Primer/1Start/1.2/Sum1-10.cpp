#include <iostream>

using namespace std;

int main(void)
{
	int sum = 0,val = 1;
	//只要val的值小于等于10，while循环就会持续执行
	while (val <= 10)
	{
		sum += val;
		++val;
	}
	cout << "Sum of 1 to 10 inclusive is "
		 << sum << endl;
	return 0;
}
