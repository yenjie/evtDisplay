/*
Draw a circle in root canvas

Usage: circle (x,y,radius,color)
*/

#include <TEllipse.h>

void setColor(int a[][10]);

int circle(float x,float y,float z,float r,float c,float flag)
{

//if (fabs(y)>=1) return 0;
int colset[10][10];
int cset=1;

setColor(colset);

//if (flag==0){ return 1; }

// calculate the position of the particle

double size=80;   //  size of the canvas

double px=x/size+0.5;
double py=y/size+0.5;
double pz=z/size+0.5;
double rad=r/size;
int d;


// flag = 1 -> particle which is produced at that instance
// flag = 0 -> particle which is not yet produced.
// flag = 5 -> normal particle

if (c==0){
TEllipse* ell1 = new TEllipse(pz,px,rad,rad);
ell1->SetFillColor(1);
ell1->SetLineColor(1);
ell1->Draw();
return 0;
}

if (flag!=5&&flag!=10){
//return 0;
TEllipse* ell1 = new TEllipse(pz,px,rad,rad);

int color;

if (flag==0) color=100;
if (flag==1) color=98;
if (flag==2) color=97;
if (flag==3) color=96;
if (flag==4) color=95;

ell1->SetFillColor(color);
ell1->SetLineColor(color);
ell1->Draw();
return 0;
}


int particle=c;
if (abs(particle)<2000) {cset=4;}     // meson
if (abs(particle)>2000) {cset=6;}     // baryon
if (particle==197)      {cset=5;};   // disk


int n=1;

int grad=9;
if (cset!=-11) {
for (n=1;n<=grad;n++){
double rad2=rad*(grad-n+1.0)/(double)grad;
TEllipse* ell = new TEllipse(pz+0.05*(n-1.0)/size,px+0.05*(n-1.0)/size,rad2,rad2);
int col=colset[cset][n];

ell->SetFillColor(col);
ell->SetLineColor(col);
ell->Draw();
}
}
return 1;
}

void setColor(int colset[][10])
{
colset[0][1]=209;
colset[0][2]=103;
colset[0][3]=210;
colset[0][4]=211;
colset[0][5]=78;
colset[0][6]=80;
colset[0][7]=212;
colset[0][8]=89;
colset[0][9]=10;

colset[1][1]=211;
colset[1][2]=153;
colset[1][3]=79;
colset[1][4]=81;
colset[1][5]=83;
colset[1][6]=85;
colset[1][7]=87;
colset[1][8]=89;
colset[1][9]=5;

colset[2][1]=2;
colset[2][2]=99;
colset[2][3]=98;
colset[2][4]=97;
colset[2][5]=96;
colset[2][6]=95;
colset[2][7]=94;
colset[2][8]=93;
colset[2][9]=92;

colset[3][1]=128;
colset[3][2]=149;
colset[3][3]=148;
colset[3][4]=147;
colset[3][5]=127;
colset[3][6]=126;
colset[3][7]=125;
colset[3][8]=124;
colset[3][9]=123;

colset[4][1]=112;
colset[4][2]=113;
colset[4][3]=12;
colset[4][4]=114;
colset[4][5]=13;
colset[4][6]=115;
colset[4][7]=116;
colset[4][8]=14;
colset[4][9]=15;

colset[5][1]=56;
colset[5][2]=57;
colset[5][3]=58;
colset[5][4]=59;
colset[5][5]=60;
colset[5][6]=61;
colset[5][7]=62;
colset[5][8]=63;
colset[5][9]=64;

colset[6][1]=61;
colset[6][2]=62;
colset[6][3]=63;
colset[6][4]=64;
colset[6][5]=65;
colset[6][6]=66;
colset[6][7]=67;
colset[6][8]=69;
colset[6][9]=71;

}
