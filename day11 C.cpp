#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#define ll long long
#define Sca(a) scanf("%d",&a)
#define Scall(a) scanf("%lld",&a)
#define Pri(a) printf("%d",&a)
#define Prill(a) printf("%lld",&a)
#define FAST_IO ios::sync_with_stdio(false)
using namespace std;
const int INF=0x3f3f3f3f;
const ll INFL=0x3f3f3f3f3f3f3f3f;
using namespace std;

int trie[1000010][26];    //数组形式定义字典树，值存储的是下一个字符的位置
int num[1000010]={0};    //附加值，以某一字符串为前缀的单词的数量
int pos = 1;

void Insert(char word[])    //在字典树中插入某个单词
{
    int i;
    int c = 0;
    for(i=0;word[i];i++){
        int n = word[i]-'a';
        if(trie[c][n]==0)    //如果对应字符还没有值
            trie[c][n] = pos++;
        c = trie[c][n];
        num[c]++;
    }
}
int Find(char word[])    //返回以某个字符串为前缀的单词的数量
{
    int i;
    int c = 0;
    for(i=0;word[i];i++){
        int n = word[i]-'a';
        if(trie[c][n]==0)
            return 0;
        c = trie[c][n];
    }
    return num[c];
}

int main()
{
    char word[11];
    while(gets(word)){
        if(word[0]==NULL)    //空行。gets读入的回车符会自动转换为NULL。
            break;
        Insert(word);
    }
    while(gets(word))
        printf("%d\n",Find(word));
    return 0;
}
