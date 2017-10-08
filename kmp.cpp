#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>   

using namespace std;

//kmp的next算法
void getNextList();
void testKmp();
void nextval_from_one();
int kmp(string str, string t, int pos=0);

int main()
{
    testKmp();
    //nextval_from_one();
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


//符合程序逻辑的从0开始，next的改进版本
void getNextList(string& str, int next[])
{
    //next是保存结果的数组
    int i=0;    //需要找到P1P2...Pi中的那个k，也就是当前需要求next的下标（也就是当前匹配失败的下边）-1
    int j=-1;    //当前需要求next的下边的上一个对应的next值，也就是next[i]

    next[0]=-1;

    int length = str.length();
    while(i < length-1){
        if(j==-1 || str[i]==str[j]){   //这个时候要单独处理，因为此时并不存在str[j]
            j++;    //下一次从第1个开始比较
            i++;    //求下一个的next
            if(str[i]!=str[j]){
                next[i]=j;
            }else{
                next[i]=next[j];
            }
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

//按照算法从1开始的nextval版本

//改进的点是：当前根据递推关系，在已经有的p1...pk=...pj-1的关系上又得到了p1...pkpk+1=...pj-1pj这个关系，但是不是这样就完了，还需要检测pj+1是否等于pk+1，因为如果相等的话，主串中的s[w]和pj+1比较失败后按理是应该和next[j+1]=Pk+1比较，但是此时pk+1是等于pj+1 != s[p]的，所以应该是直接和next[pk+1]比较，也就是节省这一步
void nextval_from_one()
{
    string str="0aaaab";
    int nextval[100];  //保存结果的数组，没有使用next[0]
    int i=1;    //需要找到P1P2...Pi中的那个k，也就是当前需要求next的下标（也就是当前匹配失败的下标）-1
    int j=0;    //当前需要求next的下标的上一个对应的next值，也就是next[i]

    nextval[1]=0;

    int length = str.length();
    while(i < length){
        //j==0和第二种情况可以合并
        if(j==0){   //这个时候要单独处理，因为此时并不存在str[j]
            j++;    //下一次从第1个开始比较
            i++;    //求下一个的next
            
            if(str[i]!=str[j]){ 
                nextval[i]=j;
            }else{
                nextval[i]=nextval[j];
            }

        }else if(str[i]==str[j]){
            j++;    //说明需要比较的是j的下一个
            i++;    //求下一个的next
            //nextval[i]=j; 老版本直接是这个结果，注意下边j代表的意义，就是老版本的nextval[i]

            //p84页的next改进意见,针对P1...Pk=...Pm-1中存在的Pm=Pk这种情况的处理
            if(str[i]!=str[j]){ //i和j已经自增过了，此时的i代表的是当前需要求next的下标（也就是当前与主串匹配失败的那一位），也就是上边说的m，而j代表的是上边的k（未改进版本的k），此时也就是检测是不是存在pk=pm这种情况
                nextval[i]=j;
            }else{
                nextval[i]=nextval[j];  //如果存在pk=pm，则
            }


        }else{
            j=nextval[j];
        }    
    }

    return;
}