#include <iostream>
#include <time.h>
#include <memory>

using namespace std;

clock_t start,end1;

int main(){
	start = clock();
	//程序体
	for(int i = 0;i<1e7;i++){
		int * q= new int(0);
		delete q;
	}
	end1 = clock();
	double endtime = (double)(end1 - start) / CLOCKS_PER_SEC;
	cout << endtime*1000 << endl; //ms为单位
	return 0;
}