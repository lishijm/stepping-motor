#include<reg52.h>
#define unchar unsigned char
#define unint unsigned int
sbit pul=P1^0;
sbit dir=P1^1;
sbit en=P1^2;
unint flag=0;

void delay(unint delay){
    unint x,y;
    for(x=delay;x>0;x--){
        for(y=255;y>0;y--);
    }
}
void encoder_a() interrupt 0{
    if(flag==0){
        flag=1;
    }
    if(flag==2){
        flag=0;
    }
    pul=~pul;
}

void encoder_b() interrupt 2{
    if(flag==0){
        flag=2;
        dir=0;
    }
    if(flag==1){
        dir=1;
        flag=0;
    }
    pul=~pul;
}

void main(){
    EA=1;     //开启总中断
    EX0=1;	 //开启0号外部中断
    EX1=1;
    IT0=1;
    IT1=1;
    pul=0;
    dir=0;
    while(1);
}