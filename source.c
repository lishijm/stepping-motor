//10KHz定时器，产生5KHz脉冲信号
#include<reg52.h>
#define unchar unsigned char
#define unint unsigned int
sbit pul=P1^0;
sbit dir=P1^1;
sbit en=P1^2;
sbit s1=P3^4;
sbit s2=P3^5;
sbit s3=P3^6;
sbit s4=P3^7;
unint temp;
unint ti;
unint state,pause;

void delay(unint delay){
    unint x,y;
    for(x=delay;x>0;x--){
        for(y=255;y>0;y--);
    }
}

void states(){
    P3=0Xfe;
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0){
        delay(10);
        if(temp!=0xf0){
            switch(temp){
                case 0xe0:
                    pause=0;
                    break;
                case 0xd0:
                    pause=1;
                    break;
                case 0xb0:
                    dir=0;
                    break;
                case 0x70:
                    dir=1;
                    break;
            }
        }//因为段选锁存器写在判断逻辑内，所以不用松手检测
    }
    P3=0Xfd;
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0){
        delay(10);
        if(temp!=0xf0){
            switch(temp){
                case 0xe0:
                    state=20;
                    break;
                case 0xd0:
                    state=10;
                    break;
                case 0xb0:
                    state=2;
                    break;
                case 0x70:
                    state=1;
                    break;
            }
        }//因为段选锁存器写在判断逻辑内，所以不用松手检测
    }
}

void timer0() interrupt 1{
    TH0=(65536-92)/256;
    TL0=(65536-92)%256;
    ti++;
    states();
    if(pause==0){
        if(ti==state){
            ti=0;
            pul=~pul;
        }
        else if(ti>=state){
            ti=0;
        }
    }
}

void main(){
    ti=0;
    TMOD=0x01;
    TH0=(65536-92)/256;
    TL0=(65536-92)%256;
    EA=1;
    ET0=1;
    EX0=1;
    TR0=1;
    pul=0;
    dir=0;
    pause=1;
    state=20;
    while(1);
}