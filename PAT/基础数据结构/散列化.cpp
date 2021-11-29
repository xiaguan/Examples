#include <iostream>
#include <cstring>
using namespace std;

const int M = 1046527;
const int NIL = -1;
const int L = 14;

char H[M][L];

int getChar(char ch){
    if(ch=='A') return 1;
    if(ch=='C') return 2;
    if(ch=='G') return 3;
    if(ch=='F') return 4;
    else return 0;
}

long long getKey(const string& s){
    long long sum = 0,p=1,i;
    for(i = 0;i<s.size();i++){
        sum += p*(getChar(s[i]));
        p *= 5;
    }
    return sum;
}

int h1(int key){return key%M;}
int h2(int key){return 1+(key%(M-1));}


int find(const string& s){
    long long key,i,h;
    key = getKey(s);
    for(i=0;;i++){
        h = (h1(key) + i*h2(key)) % M;
        if(strcmp(H[h],s.c_str()) == 0) return 1;
        else if(strlen(H[h]) == 0) return 0;
    }
    return 0;
}

int insert(char str[]){
    long long key, i ,h;
    key = getKey(str);
    for(i=0;;i++){
        h = (h1(key) + i*h2(key)) % M;
        if(strcmp(H[h],str) == 0) return 1;
        else if(strlen(H[h])==0){
            strcpy(H[h],str);
            return 0;
        }
    }
    return 0;
}
int main(){
    int i,n,h;
    char str[L],com[9];
    for(int i = 0;i<M;i++) H[i][0] = '\0';
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        scanf("%s %s",com,str);

        if(com[0]=='i')
        {
            insert(str);
        } else{
            if(find(str)){
                puts("yes");
            }else{
                puts("no");
            }
        }
    }
    return 0;
}