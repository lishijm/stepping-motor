#include<reg52.h>
#define unchar unsigned char
#define unint unsigned int
sbit pul=P1^0;
sbit dir=P1^1;
sbit en=P1^2;
unint ti;
unint state,flag=0;

void delay(unint delay){
    unint x,y;
    for(x=delay;x>0;x--){
        for(y=255;y>0;y--);
    }
}

void timer0() interrupt 1{
    TH0=(65536-92)/256;
    TL0=(65536-92)%256;
    ti++;
    if(ti==1){
        ti=0;
        //pul=~pul;
        switch(state){
            case 0:
                pul=pul;
                break;
            case 1:
                if(flag==20){
                    flag=0;
                    pul=~pul;
                }
                flag++;
                break;
            case 2:
                if(flag==10){
                    flag=0;
                    pul=~pul;
                }
                flag++;
                break;
            case 3:
                if(flag==2){
                    flag=0;
                    pul=~pul;
                }
                flag++;
                break;
            case 4:
                pul=~pul;
                break;
        }
    }
}

void clwise(){
    dir=0;
}

void anticlwise(){
    dir=1;
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
    while(1){
        clwise();
        state=4;
        /*anticlwise();
        state=0;
        delay(500);
        state=1;
        delay(500);
        state=2;
        delay(500);
        state=1;
        delay(500);*/
    }
}