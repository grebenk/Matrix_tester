#include "Arduino.h"
//#include "PCF8575.h"

#define enice_a 26
#define enice_b 24
#define enice_c 36
#define enice_d 34
#define enice_e 32
#define enice_f 28
#define enice_g 30

#define desetice_a 40
#define desetice_b 38
#define desetice_c 48
#define desetice_d 50
#define desetice_e 52
#define desetice_f 44
#define desetice_g 46

//PCF8575 pcf8575(0x20);

//definicije ADC vrednosti in zastopane tipke
#define tipka1 2
#define vrednost2 3
int adc_tipkovnice[25]={206,255,340,512,1020,105,116,131,151,179,70,75,81,88,98,52,54,57,61,66,40,43,45,47,50};//tipka1,tipka2...
                      //1-3 vrsta +-3,4 rsta +-2,5 vrsta +-1
//int obmocje_adc=2;
//int cifre[14]={enice_a,enice_b,enice_c,enice_d,enice_e,enice_f,enice_g,desetice_a,desetice_b,desetice_c,desetice_d,desetice_e,desetice_f,desetice_g};



#define tipkovnica A0
//#define vhod_za_nakljucje A2
//const byte vhod_za_nakljucje = 7;
/*#define vrstica1 3
#define vrstica2 4
#define vrstica3 5
#define vrstica4 6
#define vrstica5 7
#define stolpec1 8
#define stolpec2 9
#define stolpec3 10
#define stolpec4 11
#define stolpec5 12*/



int vrstica1=3;
int vrstica2=4;
int vrstica3=5;
int vrstica4=6;
int vrstica5=7;
int stolpec1=8;
int stolpec2=9;
int stolpec3=10;
int stolpec4=11;
int stolpec5=12;
#define MUX_SDA A4
#define MUX_SCL A5
#define MUX_INT 2
#define start_gumb 13
#define start_led 22

//int led_na_traku =

int cilj[100];//tabela, ki vsebuje vrednosti 1-25, ki zaznamujejo mesta tipk/luck
int izbor[100];
int stopnja=0;
int izguba=2;

void setup()
{
//Serial.begin(115200);
pinMode(tipkovnica,INPUT);
pinMode(A2, INPUT);
pinMode(start_gumb,INPUT_PULLUP);
pinMode(vrstica1,OUTPUT);
pinMode(vrstica2,OUTPUT);
pinMode(vrstica3,OUTPUT);
pinMode(vrstica4,OUTPUT);
pinMode(vrstica5,OUTPUT);
pinMode(stolpec1,OUTPUT);
pinMode(stolpec2,OUTPUT);
pinMode(stolpec3,OUTPUT);
pinMode(stolpec4,OUTPUT);
pinMode(stolpec5,OUTPUT);
pinMode(MUX_INT,OUTPUT);
pinMode(MUX_SDA,OUTPUT);
pinMode(MUX_SCL,OUTPUT);

randomSeed(analogRead(A2));

for(int i=22;i<53;i+=2){pinMode(i,OUTPUT);}//nastavi izhode za zaslon na OUTPUT
/*
pcf8575.pinMode(P0,OUTPUT);//desetice, A
pcf8575.pinMode(P1,OUTPUT);//desetice, B
pcf8575.pinMode(P2,OUTPUT);//desetice, C
pcf8575.pinMode(P3,OUTPUT);//desetice, D
pcf8575.pinMode(P4,OUTPUT);//desetice, E
pcf8575.pinMode(P5,OUTPUT);//desetice, F
pcf8575.pinMode(P6,OUTPUT);//desetice, G

pcf8575.pinMode(P10,OUTPUT);//enice, A
pcf8575.pinMode(P11,OUTPUT);//enice, B
pcf8575.pinMode(P12,OUTPUT);//enice, C
pcf8575.pinMode(P13,OUTPUT);//enice, D
pcf8575.pinMode(P14,OUTPUT);//enice, E
pcf8575.pinMode(P15,OUTPUT);//enice, F
pcf8575.pinMode(P7,OUTPUT);//enice, G
pcf8575.begin();
*/
}

void loop()
{
  //delay(2000);
  // put your main code here, to run repeatedly:
//for(int i=0;i<14;i++){digitalWrite(cifre[i],1);delay(1000);digitalWrite(cifre[i],0);}
//for(int i=0;i<10;i++){zaslon(i*10+i);delay(500);}


if(izguba==2||izguba==1){
  //animacija_okvirja(0);zaslon(0);
  int lucka=0;
  //Serial.println("pritisni za zacetzek");
  delay(2);
  if(izguba==2)zaslon(0);
  while(digitalRead(start_gumb)!=0){++lucka;delay(100);digitalWrite(start_led,(lucka%2)==0);}
  digitalWrite(start_led,0);
  //Serial.println("igra!");
  delay(2);
  zaslon(0);
  izguba=0;
  delay(300);
  //animacija_okvirja(4);
  }
izziv(random(1,26),stopnja);
igra();


////Serial.println(branje_tipkovnice());
////Serial.println(branje_tipkovnice());
/*
int stolpci[5]={stolpec1,stolpec2,stolpec3,stolpec4,stolpec5};
int vrstice[5]={vrstica1,vrstica2,vrstica3,vrstica4,vrstica5};
for(int a=0;a<5;a++){
  for(int b=0;b<5;b++){
  digitalWrite(vrstice[a],1);
  digitalWrite(stolpci[b],1);
  //Serial.print(vrstice[a]);//Serial.println(stolpci[b]);
    //Serial.print("vrstica: ");//Serial.print(a);//Serial.print(" stolpec: ");//Serial.println(b);
  delay(500);
  digitalWrite(vrstice[a],0);
  digitalWrite(stolpci[b],0);
  }
}
*/
//digitalWrite(stolpec4,1);digitalWrite(vrstica2,1);
//for(int a=1;a<14;a++)digitalWrite(a,1);
// pcf8575.digitalWrite(P1,1);
//delay(300);

}

int branje_tipkovnice()
{unsigned long meritev=0;int obmocje_adc;
//Serial.println("Cakam vnos");
delay(1);
while(analogRead(tipkovnica)<20){delay(2);}
for(int r=0;r<300;r++)meritev+=analogRead(tipkovnica);
//return(meritev/=300);
meritev/=300;
for(int p=0;p<25;p++)
  {if(p<15)obmocje_adc=3;//1,2,3. vrsta ima območje +/- 3
  else if(15<p&&p<20)obmocje_adc=2;//4. vrsta ima območje +/- 2
  else obmocje_adc=1;//5. vrsta ima območje +/- 1
  if((adc_tipkovnice[p]-obmocje_adc)<=meritev&&meritev<=(adc_tipkovnice[p]+obmocje_adc))return(p+1);
  }
 
//if((tipka1-obmocje_adc)=<meritev&&meritev=<(tipka1+obmocje_adc))
/*
switch (analogRead(tipkovnica)){
  case vrednost1: return 1;
  case vrednost2: return 2;
//preveri vrednosti nap.delilnika,mogoce vnaprej naj bodo definirane?*/
}


void animacija_okvirja(int stanje)
{
  //Serial.print("okvir");
  switch(stanje)
  {
  case 0:{//idle
  zaslon(0);
  digitalWrite(vrstica3,1);
  digitalWrite(stolpec3,1);
  }
  case 1:{ //zmaga
  for(int i=1;i<5;i++)
  {
    if(i%2==0)zaslon(stopnja);
    else ugasni_zaslon();
    delay(100);
  }
  }
  case 2:{ //izguba
  ugasni_zaslon();
  for(int i=1;i<8;i++)
    {
      if(i%2==0)
      {
//        pcf8575.digitalWrite(P6,1);
//        pcf8575.digitalWrite(P7,1);
      }
      else ugasni_zaslon();
    }
    delay(100);
  //gumb za zac?
  stopnja=0;
  }
  case 4:{//zacetek igre
  digitalWrite(vrstica3,0);
  digitalWrite(stolpec3,0);
  }
}
}

void izziv(int vrednost,int mesto)
{
cilj[mesto]=vrednost;
stopnja++;
for(int t=0;t<stopnja;t++)//animacija za Simon Says
  {delay(300);
  //digitalWrite(cilj[t]/5+3,1);//prizig vrstice
  if((cilj[t]%5)==0){digitalWrite(cilj[t]/5+2,1);digitalWrite(12,1);}//ce je ostanek 0 prizge zadnji stolpec
  else{digitalWrite(cilj[t]%5+7,1);digitalWrite(cilj[t]/5+3,1);}
  delay(200);
  digitalWrite(cilj[t]/5+3,0);//prizig vrstice
if((cilj[t]%5)==0){digitalWrite(cilj[t]/5+2,0);digitalWrite(12,0);}//ce je ostanek 0 prizge zadnji stolpec
  else{digitalWrite(cilj[t]%5+7,0);digitalWrite(cilj[t]/5+3,0);}
  //delay(200);
  //Serial.print(cilj[t]);//Serial.print("  ");
  }
//Serial.print("stopnja: ");//Serial.print(stopnja);//Serial.print("  tipka: ");//Serial.println(vrednost);
}

int igra()
{
for(int runda=0;(runda<stopnja)&&(izguba!=1);runda++)
  {
  delay(10);
  izbor[runda]=branje_tipkovnice();
  if(izbor[runda]!=cilj[runda]){
  //animacija_okvirja(2);
  //Serial.print(izbor[runda]);//Serial.print("  ");//Serial.println(cilj[runda]);
  //Serial.println("You lose");
  delay(2);animacija_tipkovnice(1);izguba=1;
//for(int i=0;i<stopnja;i++){izbor[i];
stopnja=0;}
  else{izguba=0;delay(2);}
  if(izguba!=1){
  //animacija_okvirja(1);
  //Serial.println("Nice!");
  delay(2);
}
  while(analogRead(tipkovnica)>20){delay(2);}
delay(10);
  }

//zaslon(stopnja);
zaslon(stopnja);
}

void animacija_tipkovnice(int izzid)
{
  switch(izzid){
  case 1:{
    int stolpci[5]={stolpec1,stolpec2,stolpec3,stolpec4,stolpec5};
int vrstice[5]={vrstica1,vrstica2,vrstica3,vrstica4,vrstica5};
for(int c=1;c<6;c++){
  delay(200);
for(int a=0;a<5;a++){
  for(int b=0;b<5;b++){
  if(c%2==0){digitalWrite(vrstice[a],1);
  digitalWrite(stolpci[b],1);
  ////Serial.print(vrstice[a]);//Serial.println(stolpci[b]);
  //   //Serial.print("vrstica: ");//Serial.print(a);//Serial.print(" stolpec: ");//Serial.println(b);
  //delay(500);
  }
  else{
  digitalWrite(vrstice[a],0);
  digitalWrite(stolpci[b],0);
  }}
}}break;
  }
  case 2:{int utrip=1;
  while(utrip<3){
  utrip++;
  if(utrip%2==0){digitalWrite(vrstica3,1);digitalWrite(stolpec3,1);}
  else{digitalWrite(vrstica3,0);
  digitalWrite(stolpec3,0);}
  delay(100);
  }break;}
}}

void zaslon(int dosezek)
{
if(dosezek>99)while(1){ugasni_zaslon();delay(100);zaslon(88);delay(100);}
ugasni_zaslon();
//Serial.println(dosezek);
switch(dosezek/10)
{
  case(0):
  {
  digitalWrite(desetice_a,1);
  digitalWrite(desetice_b,1);
  digitalWrite(desetice_c,1);
  digitalWrite(desetice_d,1);
  digitalWrite(desetice_e,1);
  digitalWrite(desetice_f,1);
  break;
  }
  case(1):
  {
  digitalWrite(desetice_b,1);
  digitalWrite(desetice_c,1);
  break;
  }
  case(2):
  {
  digitalWrite(desetice_a,1);
  digitalWrite(desetice_b,1);
  digitalWrite(desetice_d,1);
  digitalWrite(desetice_e,1);
  digitalWrite(desetice_g,1);
  break;
  }
  case(3):
  {
  digitalWrite(desetice_a,1);
  digitalWrite(desetice_b,1);
  digitalWrite(desetice_c,1);
  digitalWrite(desetice_d,1);
  digitalWrite(desetice_g,1);
  break;
  }
  case(4):
  {
  digitalWrite(desetice_b,1);
  digitalWrite(desetice_c,1);
  digitalWrite(desetice_f,1);
  digitalWrite(desetice_g,1);
  break;
  }
  case(5):
  {
  digitalWrite(desetice_a,1);
  digitalWrite(desetice_c,1);
  digitalWrite(desetice_d,1);
  digitalWrite(desetice_f,1);
  digitalWrite(desetice_g,1);
  break;
  }
  case(6):
  {
  digitalWrite(desetice_a,1);
  digitalWrite(desetice_c,1);
  digitalWrite(desetice_d,1);
  digitalWrite(desetice_e,1);
  digitalWrite(desetice_f,1);
  digitalWrite(desetice_g,1);
  break;
  }
  case(7):
  {
  digitalWrite(desetice_a,1);
  digitalWrite(desetice_b,1);
  digitalWrite(desetice_c,1);
  break;
  }
  case(8):
  {
  digitalWrite(desetice_a,1);
  digitalWrite(desetice_b,1);
  digitalWrite(desetice_c,1);
  digitalWrite(desetice_d,1);
  digitalWrite(desetice_e,1);
  digitalWrite(desetice_f,1);
  digitalWrite(desetice_g,1);
  break;
  }
  case(9):
  {
  digitalWrite(desetice_a,1);
  digitalWrite(desetice_b,1);
  digitalWrite(desetice_c,1);
  digitalWrite(desetice_d,1);
  digitalWrite(desetice_f,1);
  digitalWrite(desetice_g,1);
  break;
  }
}
switch(dosezek%10)
{
  case(0):
  {
  digitalWrite(enice_a,1);
  digitalWrite(enice_b,1);
  digitalWrite(enice_c,1);
  digitalWrite(enice_d,1);
  digitalWrite(enice_e,1);
  digitalWrite(enice_f,1);
  break;
  }
  case(1):
  {
  digitalWrite(enice_b,1);
  digitalWrite(enice_c,1);
  break;
  }
  case(2):
  {
  digitalWrite(enice_a,1);
  digitalWrite(enice_b,1);
  digitalWrite(enice_d,1);
  digitalWrite(enice_e,1);
  digitalWrite(enice_g,1);
  break;
  }
  case(3):
  {
  digitalWrite(enice_a,1);
  digitalWrite(enice_b,1);
  digitalWrite(enice_c,1);
  digitalWrite(enice_d,1);
  digitalWrite(enice_g,1);
  break;
  }
  case(4):
  {
  digitalWrite(enice_b,1);
  digitalWrite(enice_c,1);
  digitalWrite(enice_f,1);
  digitalWrite(enice_g,1);
  break;
  }
  case(5):
  {
  digitalWrite(enice_a,1);
  digitalWrite(enice_c,1);
  digitalWrite(enice_d,1);
  digitalWrite(enice_f,1);
  digitalWrite(enice_g,1);
  break;
  }
  case(6):
  {
  digitalWrite(enice_a,1);
  digitalWrite(enice_c,1);
  digitalWrite(enice_d,1);
  digitalWrite(enice_e,1);
  digitalWrite(enice_f,1);
  digitalWrite(enice_g,1);
  break;
  }
  case(7):
  {
  digitalWrite(enice_a,1);
  digitalWrite(enice_b,1);
  digitalWrite(enice_c,1);
  break;
  }
  case(8):
  {
  digitalWrite(enice_a,1);
  digitalWrite(enice_b,1);
  digitalWrite(enice_c,1);
  digitalWrite(enice_d,1);
  digitalWrite(enice_e,1);
  digitalWrite(enice_f,1);
  digitalWrite(enice_g,1);
  break;
  }
  case(9):
  {
  digitalWrite(enice_a,1);
  digitalWrite(enice_b,1);
  digitalWrite(enice_c,1);
  digitalWrite(enice_d,1);
  digitalWrite(enice_f,1);
  digitalWrite(enice_g,1);
  break;
  }
}
}

void ugasni_zaslon()
{
  digitalWrite(desetice_a,0);
  digitalWrite(desetice_b,0);
  digitalWrite(desetice_c,0);
  digitalWrite(desetice_d,0);
  digitalWrite(desetice_e,0);
  digitalWrite(desetice_f,0);
  digitalWrite(desetice_g,0);

  digitalWrite(enice_a,0);
  digitalWrite(enice_b,0);
  digitalWrite(enice_c,0);
  digitalWrite(enice_d,0);
  digitalWrite(enice_e,0);
  digitalWrite(enice_f,0);
  digitalWrite(enice_g,0);
}

/*void zaslon_mux(int dosezek)
{
if(dosezek>99)while(1){ugasni_zaslon();delay(100);zaslon(88);delay(100);}
//Serial.println(dosezek);
switch(dosezek/10)
{
  case(0):
  {
  pcf8575.digitalWrite(P10,1);
  pcf8575.digitalWrite(P11,1);
  pcf8575.digitalWrite(P12,1);
  pcf8575.digitalWrite(P13,1);
  pcf8575.digitalWrite(P14,1);
  pcf8575.digitalWrite(P15,1);
  }
  case(1):
  {
  pcf8575.digitalWrite(P11,1);
  pcf8575.digitalWrite(P12,1);
  }
  case(2):
  {
  pcf8575.digitalWrite(P10,1);
  pcf8575.digitalWrite(P11,1);
  pcf8575.digitalWrite(P7,1);
  pcf8575.digitalWrite(P13,1);
  pcf8575.digitalWrite(P14,1);
  }
  case(3):
  {
  pcf8575.digitalWrite(P10,1);
  pcf8575.digitalWrite(P11,1);
  pcf8575.digitalWrite(P12,1);
  pcf8575.digitalWrite(P13,1);
  pcf8575.digitalWrite(P7,1);
  }
  case(4):
  {
  pcf8575.digitalWrite(P11,1);
  pcf8575.digitalWrite(P12,1);
  pcf8575.digitalWrite(P15,1);
  pcf8575.digitalWrite(P7,1);
}
  case(5):
  {
  pcf8575.digitalWrite(P10,1);
  pcf8575.digitalWrite(P15,1);
  pcf8575.digitalWrite(P7,1);
  pcf8575.digitalWrite(P12,1);
  pcf8575.digitalWrite(P13,1);
  }
  case(6):
  {
  pcf8575.digitalWrite(P10,1);
  pcf8575.digitalWrite(P15,1);
  pcf8575.digitalWrite(P7,1);
  pcf8575.digitalWrite(P12,1);
  pcf8575.digitalWrite(P13,1);
  pcf8575.digitalWrite(P14,1);
  }
  case(7):
  {
  pcf8575.digitalWrite(P10,1);
  pcf8575.digitalWrite(P11,1);
  pcf8575.digitalWrite(P12,1);
  }
  case(8):
  {
  pcf8575.digitalWrite(P10,1);
  pcf8575.digitalWrite(P11,1);
  pcf8575.digitalWrite(P12,1);
  pcf8575.digitalWrite(P13,1);
  pcf8575.digitalWrite(P14,1);
  pcf8575.digitalWrite(P15,1);
  pcf8575.digitalWrite(P7,1);
  }
  case(9):
  {
  pcf8575.digitalWrite(P10,1);
  pcf8575.digitalWrite(P11,1);
  pcf8575.digitalWrite(P12,1);
  pcf8575.digitalWrite(P13,1);
  pcf8575.digitalWrite(P15,1);
  pcf8575.digitalWrite(P7,1);
  }
}
switch(dosezek%10)
{
  case(0):
  {
  pcf8575.digitalWrite(P0,1);
  pcf8575.digitalWrite(P1,1);
  pcf8575.digitalWrite(P2,1);
  pcf8575.digitalWrite(P3,1);
  pcf8575.digitalWrite(P4,1);
  pcf8575.digitalWrite(P5,1);
  }
  case(1):
  {
  pcf8575.digitalWrite(P1,1);
  pcf8575.digitalWrite(P2,1);
  }
  case(2):
  {
  pcf8575.digitalWrite(P0,1);
  pcf8575.digitalWrite(P1,1);
  pcf8575.digitalWrite(P6,1);
  pcf8575.digitalWrite(P3,1);
  pcf8575.digitalWrite(P4,1);
  }
  case(3):
  {
  pcf8575.digitalWrite(P0,1);
  pcf8575.digitalWrite(P1,1);
  pcf8575.digitalWrite(P2,1);
  pcf8575.digitalWrite(P3,1);
  pcf8575.digitalWrite(P6,1);
  }
  case(4):
  {
  pcf8575.digitalWrite(P1,1);
  pcf8575.digitalWrite(P2,1);
  pcf8575.digitalWrite(P5,1);
  pcf8575.digitalWrite(P6,1);
}
  case(5):
  {
  pcf8575.digitalWrite(P0,1);
  pcf8575.digitalWrite(P5,1);
  pcf8575.digitalWrite(P6,1);
  pcf8575.digitalWrite(P2,1);
  pcf8575.digitalWrite(P3,1);
  }
  case(6):
  {
  pcf8575.digitalWrite(P0,1);
  pcf8575.digitalWrite(P5,1);
  pcf8575.digitalWrite(P6,1);
  pcf8575.digitalWrite(P2,1);
  pcf8575.digitalWrite(P3,1);
  pcf8575.digitalWrite(P4,1);
  }
  case(7):
  {
  pcf8575.digitalWrite(P0,1);
  pcf8575.digitalWrite(P1,1);
  pcf8575.digitalWrite(P2,1);
  }
  case(8):
  {
  pcf8575.digitalWrite(P0,1);
  pcf8575.digitalWrite(P1,1);
  pcf8575.digitalWrite(P2,1);
  pcf8575.digitalWrite(P3,1);
  pcf8575.digitalWrite(P4,1);
  pcf8575.digitalWrite(P5,1);
  pcf8575.digitalWrite(P6,1);
}
  case(9):
  {
  pcf8575.digitalWrite(P0,1);
  pcf8575.digitalWrite(P1,1);
  pcf8575.digitalWrite(P2,1);
  pcf8575.digitalWrite(P3,1);
  pcf8575.digitalWrite(P5,1);
  pcf8575.digitalWrite(P6,1);
}
}
}*/
/*
void ugasni_zaslon()
{
  pcf8575.digitalWrite(P0,0);
  pcf8575.digitalWrite(P1,0);
  pcf8575.digitalWrite(P2,0);
  pcf8575.digitalWrite(P3,0);
  pcf8575.digitalWrite(P4,0);
  pcf8575.digitalWrite(P5,0);
  pcf8575.digitalWrite(P6,0);

  pcf8575.digitalWrite(P10,0);
  pcf8575.digitalWrite(P11,0);
  pcf8575.digitalWrite(P12,0);
  pcf8575.digitalWrite(P13,0);
  pcf8575.digitalWrite(P14,0);
  pcf8575.digitalWrite(P15,0);
  pcf8575.digitalWrite(P7,0);
}
*/
//neuporabljene funkcije:

/* //izvedba animacije z WS2812 LED trakom
void animacija_okvirja(int stanje)
{
  switch(stanje)
  {
  case 0:{
  for(int i=0;i<255;i++)
    {
    for(int c=0;c<led_na_traku;c++)
      {
      pixels.setPixelColor(c,pixels.Color(i,i,i));
      }
    pixels.show();
    delay(50); //cas prehoda pri prikazu
    pixels.clear();
    }
  }
  case 1:{
  for(int i=0;i<255;i++)
    {
    for(int c=0;c<led_na_traku;c++)
      {
      pixels.setPixelColor(c,pixels.Color(0,i,0));
      }
    pixels.show();
    delay(20); //cas prehoda pri prikazu
    pixels.clear();
    }
  }
  case 2:{
  for(int i=0;i<255;i++)
    {
    for(int c=0;c<led_na_traku;c++)
      {
      pixels.setPixelColor(c,pixels.Color(i,0,0));
      }
    pixels.show();
    delay(20); //cas prehoda pri prikazu
    pixels.clear();
    }
  }
}
}

*/

/*
void prizig_lucke(int vrstica, int stolpec, int cas)
{
digitalWrite(vrstica,1);
digitalWrite(stolpec,1);
delay(cas);
digitalWrite(vrstica,0);
digitalWrite(stolpec,0);
}
*/
