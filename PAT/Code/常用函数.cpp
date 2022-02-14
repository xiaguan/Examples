//查质数

int find_zhi(int n){
    if(n<2) return -1;
    else{
        for(int i = n;;i++){
            bool flag = true;
            for(int j = 2;j*j<=i;j++){
                if(i%j==0) flag = false;
            }
            if(flag) return i;
        }
    }
}