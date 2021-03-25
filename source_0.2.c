#include<reg52.h>
#define unchar unsigned char
#define unint unsigned int
sbit pul=P1^0;
sbit dir=P1^1;
sbit en=P1^2;
sbit ecapin=P3^2;
sbit ecbpin=P3^3;
unint flag=0;
unint count=0;

void delay(unint delay){
    unint x,y;
    for(x=delay;x>0;x--){
        for(y=255;y>0;y--);
    }
}
void encoder_a() interrupt 0{
    if(ecbpin==1){
        flag=1;
    }
    if(ecbpin==0){
        flag=2;
    }
    pul=~pul;
    pul=~pul;
    pul=~pul;
    pul=~pul;
    count++;
    if(count==5){
        pul=~pul;
        count=0;
    }
}

void encoder_b() interrupt 2{
    if(flag==1&&ecapin==0){
        dir=1;
        flag=0;
    }
    if(flag==2&&ecapin==1){
        dir=0;
        flag=0;
    }
}

void main(){
    EA=1;    //开启总中断
    EX0=1;	 //开启0号外部中断
    EX1=1;
    IT0=1;   //中断方式1，下降沿触发
    IT1=1;
    pul=0;
    dir=0;
    while(1);
}