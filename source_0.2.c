#include<reg52.h>
#define unchar unsigned char
#define unint unsigned int
sbit pul=P1^0;
sbit dir=P1^1;
sbit en=P1^2;
unint flag=0;
/*
sbit s1=P3^4;
sbit s2=P3^5;
sbit s3=P3^6;
sbit s4=P3^7;
unint temp;
unint ti;
unint state,pause;
*/
void delay(unint delay){
    unint x,y;
    for(x=delay;x>0;x--){
        for(y=255;y>0;y--);
    }
}
/*
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
        }
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
        }
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
*/
void encoder_a() interrupt 0{
    if(flag==0){
        flag=1;
    }
    pul=~pul;
}

void encoder_b() interrupt 2{
    if(flag==1){
        dir=1;
        flag=2;
    }
    pul=~pul;
}

void main(){
    /*ti=0;
    TMOD=0x01;
    TH0=(65536-92)/256;
    TL0=(65536-92)%256;
    //ET0=1;
    //TR0=1;
    */
    EA=1;     //开启总中断
    EX0=1;	 //开启0号外部中断
    EX1=1;
    IT0=1;
    IT1=1;
    pul=0;
    dir=0;
    //pause=1;
    //state=20;
    while(1);
}