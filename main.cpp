//
//  main.cpp
//  rsa_itp
//
//  Created by 王俊 on 2017/11/8.
//  Copyright © 2017年 王俊. All rights reserved.
//

#include <iostream>
using namespace std;
long fastMod(long a,long b, long n)
{
    long result = 1;   //首先将result设为1,1是模乘法的单位元
    while (b>0)       //自底向上的迭代求解
    {
        if (b % 2 == 1)   //如果指数没法整除2
            result = (result*a) % n;   //那么相当于多了一个a出来，用result来记录向上求解过程中多出来a的情况
        a = (a*a) % n;          //  a^2b%n=(a^b%n*a^b%n)%n;
        b /= 2;                 //上面平方，b除2
    }
    return result;
}
long exgcd(long a,long b,long &x,long &y)  //扩展欧几里得算法
{
       if(b==0)   //结束条件
       {
          x=1;
          y=0;
       return a;
       }
    long r=exgcd(b,a%b,x,y);
    long t=x;
    x=y;
    y=t-a/b*y;
    return r;
}
int main(int argc, const char * argv[]) {
    // c1=m^e1%n,c2=m^e2%n;
    //要知道m，必须知道m%n的值，必须使指数为1，而由于e1和e2互质，gcd(e1,e2)=xe1+ye2=1;
    //由此可解出明文
    long e1=1021763679,e2=519424709,c1=1244183534,c2=732959706,n=1889570071;
    long x1=0,y1=0,x2=0,y2=0;
    exgcd(e1,e2,x1,y1);  //扩展欧几里得
    long result;   //由于x或y中有可能出现负数，出现负数时即再进行一次扩展欧几里得求其逆元
    if(x1>0)  //如果大于0正常处理
        c1=fastMod(c1,x1,n);//快指数幂求模
    else
    {
        exgcd(c1, n, x2, y2);
        x1=-x1;
        while(x2<0)//求逆元如果逆元小于0，一直加n使其变正
            x2+=n;
        c1=fastMod(x2, x1, n);
    }
    if(y1>0)
        c2=fastMod(c2,y1,n);
    else
    {
        exgcd(c2, n, x2, y2);
        y1=-y1;
        while(x2<0)
            x2+=n;
        c2=fastMod(x2, y1, n);
    }
    result=(c1*c2)%n;
    cout<<result<<endl;
    return 0;
}
