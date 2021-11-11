#include <cstdio>
#include <cstdlib>
#include <cstring>

struct Node{
    int key;
    Node *next,*pre;
};

Node *nil;

Node* listSearch(int x){
    Node *cur = nil->next;
    while(cur != nil && cur->key != x){
        cur = cur->next;
    }
    return cur;
}

void init(){
    nil = (Node *)malloc(sizeof(Node));
    nil->next = nil;
    nil->next = nil;
}

void printfList(){
    Node *cur = nil->next;
    while(cur!=nil){
        printf("%d",cur->key);
        if(cur->next!=nil)printf(" ");
        cur = cur->next;
    }
    printf("\n");
}

void deleteNode(Node * t){
    if( t==nil) return;
    t->pre->next = t->next;
    t->next->pre = t->pre;
    free(t);
}

void deleteFirst(){
    deleteNode(nil->next);
}

void deleteLast(){
    deleteNode(nil->pre);
}

void deleteKey(int key){
    deleteNode(listSearch(key));
}

void insert(int key){
    Node *x = (Node *)malloc(sizeof(Node));
    x->key = key;
    x->next = nil->next;
    nil->next->pre = x;
    nil->next = x;
    x->pre = nil;
}

int main(){
    int n ;
    int  size = 0;
    init();
    int np=0,nd=0;
    scanf("%d",&n);
    while(n--){
        char op[20];
        int key;

        scanf("%s%d",op,&key);

        if(op[0]=='i'){
            insert(key);np++,size++;
        }
        else if(op[0]=='d')
        {
            if(strlen(op)>6){
                if(op[6]=='F'){
                    deleteFirst();
                }
                if(op[6]=='L'){
                    deleteLast();
                }
            }else{
                deleteKey(key);nd++;
            }
            size--;
        }
    }
    printfList();
    return 0;
}
