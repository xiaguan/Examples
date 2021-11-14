#include <iostream>
#include <time.h>

using namespace std;

clock_t start,end1;

int main(){
	start = clock();
	//程序体
	
	end1 = clock();
	double endtime = (double)(end1 - start) / CLOCKS_PER_SEC;
	cout << endtime*1000 << endl; //ms为单位
	return 0;
}