#include <iostream>
#include <memory>
#include <cstring>

using namespace std;

char orlights[5];
char lights[5];
char result[5];

int GetBit(char c,int j){
    return (c>>j)&1;
}

void SetBit(char &c,int j,int v){
    if(v){
        c |= (1<<j);
    }
    else{
        c &= ~(1<<j);
    }
}

void FlipBit(char &c,int j) {
    c ^= (1 << j);
}

void OutputResult(int t,char result[]){
    cout << "PUZZLE #"<<t<<endl;
    for(int i =0;i<5;++i){
        for(int j=0;j<6;++j){
            cout << GetBit(result[i],j);
            if(j<5){
                cout << " ";
            }
        }
        cout << endl;
    }
}

int main(){
    int T;
    cin>>T;
    for(int t=1;t<=T;++t) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 6; j++) {
                int s;
                cin >> s;
                SetBit(orlights[i], j, s);
            }
        }
        for (int n = 0; n < 64; ++n)
        {
            int swtiches = n; // 枚举第一行的全部开关灯情况
            memcpy(lights, orlights, sizeof(orlights));
            for (int i = 0; i < 5; ++i) {
                //储存结果
                result[i] = swtiches;
                for (int j = 0; j < 6; ++j)
                {
                    // 64种中的一种关灯方式
                    if (GetBit(swtiches, j))
                    {

                        // 关一个灯引发的连锁反应，i+1行的影响后面会有
                        FlipBit(lights[i], j);
                        if (j > 0) {
                            FlipBit(lights[i], j - 1);
                        }
                        if (j < 5) {
                            FlipBit(lights[i], j + 1);
                        }

                    }
                }
                if (i < 4)
                {
                    lights[i + 1] ^= swtiches;
                }
                swtiches = lights[i];
            }
            if (lights[4] == 0) {
                OutputResult(t, result);
                break;
            }
        }
    }
    return 0;
}
