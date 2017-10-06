#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>   

using namespace std;

//kmp的next算法
void getNextList();
void testKmp();
int kmp(string str, string t, int pos=0);

int main()
{
    testKmp();
    return 0;
}

//严蔚敏老师的书中的get_next实际上是把while里边的两种情况合并了
//《数据结构 第五版》p83
//CPP的默认参数：默认参数可以放在函数声明或者定义中，但只能放在二者之一
//变量名尽量按照书上来的

//简单测试
void testKmp()
{
    string lowerStr="abcdefghijklmnopqrstuvwxyz~!@#$%^&*()_+";

    string upperStr="ASSDWREREFDSFDGTYTUDF"; 

    string subStr="";

    int lowerStrLen = lowerStr.length();
    int upperStrLen = upperStr.length();

    int start;  //开始截取的位置
    int length; //截取的长度
    int result; //正确的结果
    int kmpResult;

    srand((unsigned)time(0));  
    for(int i=0; i < 100 ; i++){
        if(i%2==0){     //测试找到的情况
            start=rand()%(lowerStrLen-2);
            length=rand()%(lowerStrLen-start);
            subStr=lowerStr.substr(start,length);
            result=length ==0 ? -1 : start; //传入空字符串的时候返回-1
        }else{  //根本找不到
            start=rand()%(upperStrLen-2);
            length=rand()%(upperStrLen-start);
            subStr=upperStr.substr(start,length);
            result=-1;
        }
        
        if(kmpResult=kmp(lowerStr,subStr)!=result){
            cout<<"测试失败："<<endl<<"正确的返回结果："<<result<<"，实际返回结果："<<kmpResult
            <<endl<<"截取的字符串："<<subStr<<endl;
        }else{
            cout<<"done"<<endl;
        }
    }
}


//符合程序逻辑的从0开始
void getNextList(string& str, int next[])
{
    //next是保存结果的数组
    int i=0;    //需要找到P1P2...Pi中的那个k，也就是当前需要求next的下标（也就是当前匹配失败的下边）-1
    int j=-1;    //当前需要求next的下边的上一个对应的next值，也就是next[i]

    next[0]=-1;

    int length = str.length();
    while(i < length-1){
        if(j==-1){   //这个时候要单独处理，因为此时并不存在str[j]
            j++;    //下一次从第1个开始比较
            i++;    //求下一个的next
            next[i]=0;
        }else if(str[i]==str[j]){
            j++;    //说明需要比较的是j的下一个
            i++;    //求下一个的next
            next[i]=j;
        }else{
            j=next[j];
        }    
    }

    return;
}

int kmp(string str, string t, int pos)
{
    int i=pos;  //开始搜索的下标
    int j=0;    //指向t的下标

    int strLen=str.length();
    int tLen=t.length();
    
    if(tLen==0){
        return -1;
    }

    int *next = new int[strLen];
    getNextList(str,next);

    while(i < strLen && j < tLen){
        if(j==-1){  //说明此时next已经失效，必须从0开始重新匹配
            i++;
            j++;
        }else if(str[i]==t[j]){ //匹配成功
            i++;
            j++;
        }else{  //匹配失败，利用next的值回滚
            j=next[j];
        }
    }

    delete[] next;

    if(j == tLen){
        return i-tLen;
    }else{
        return -1;
    }
}

//按照算法从1开始的next版本
void next_from_one()
{
    string str="0abaabcac";
    int next[100];  //保存结果的数组，没有使用next[0]
    int i=1;    //需要找到P1P2...Pi中的那个k，也就是当前需要求next的下标（也就是当前匹配失败的下边）-1
    int j=0;    //当前需要求next的下边的上一个对应的next值，也就是next[i]

    next[1]=0;

    int length = str.length();
    while(i < length){
        if(j==0){   //这个时候要单独处理，因为此时并不存在str[j]
            j++;    //下一次从第1个开始比较
            i++;    //求下一个的next
            next[i]=1;
        }else if(str[i]==str[j]){
            j++;    //说明需要比较的是j的下一个
            i++;    //求下一个的next
            next[i]=j;
        }else{
            j=next[j];
        }    
    }

    return;
}