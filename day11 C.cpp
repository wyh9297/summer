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

int trie[1000010][26];    //������ʽ�����ֵ�����ֵ�洢������һ���ַ���λ��
int num[1000010]={0};    //����ֵ����ĳһ�ַ���Ϊǰ׺�ĵ��ʵ�����
int pos = 1;

void Insert(char word[])    //���ֵ����в���ĳ������
{
    int i;
    int c = 0;
    for(i=0;word[i];i++){
        int n = word[i]-'a';
        if(trie[c][n]==0)    //�����Ӧ�ַ���û��ֵ
            trie[c][n] = pos++;
        c = trie[c][n];
        num[c]++;
    }
}
int Find(char word[])    //������ĳ���ַ���Ϊǰ׺�ĵ��ʵ�����
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
        if(word[0]==NULL)    //���С�gets����Ļس������Զ�ת��ΪNULL��
            break;
        Insert(word);
    }
    while(gets(word))
        printf("%d\n",Find(word));
    return 0;
}
