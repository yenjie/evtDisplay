#include <stdio.h>
#include <iostream>

using namespace std;
//#include <math.h>
#include "shellSort.h"
//#include "circle.c"

#define npara 7
#define maxNum 10000
#define minTime 0
#define maxTime 400

// opt = 3 -> draw zx plane
// opt = 4 -> draw xy plane

#define mode 3

void readData(float a[][10]);
void divideData();
int selection(float tmp[]);
void drawInRoot(int dataTime);


int main()
{
  int t;

  divideData();
 

  for(t=minTime; t<= maxTime;t++)
  {
   drawInRoot(t);
  }

}




void divideData()
{
   FILE *dataFile = fopen("./input.dat","r");
   int flag=1; 
   char *tmp= new char[100];   
   float tmpData[10];
   int counter=0;

   // clean old files.
   cout <<"Initializing...";
   for (int i=minTime;i<=maxTime;i++)
   {
      char buffer[50];
      sprintf (buffer, ".data-%d",i);
      FILE *dataFile1 = fopen(buffer,"w");
      fclose (dataFile1);
   }
   cout <<endl;
   cout <<"Data file opened, reading the content...";

   while (flag == 1)
   {
      counter++;
      if ((counter%100000)==0) cout <<"."<<endl;
      for (int i=0;i<npara;i++)
      {	
         flag=fscanf(dataFile,"%s",tmp);
         tmpData[i]=atof(tmp);
      }
      
      if (flag!=1) 
      {
         cout <<"done."<<endl; 
      } else 
      {
         if (selection(tmpData)==1)
         {
            // write into file
            char buffer[50];
            int dataTime=(int)tmpData[0];
            sprintf (buffer, ".data-%d",dataTime);
            FILE *dataFile1 = fopen(buffer,"a");
 
            for (int i=0;i<npara;i++)
            {
               fprintf(dataFile1,"%f ",tmpData[i]);
            }
            fprintf(dataFile1,"\n");
            fclose(dataFile1);
         }
       } 
   }

   fclose(dataFile);
}

void drawInRoot(int dataTime)
{

  char buffer[50],tmp[100];
  float data[maxNum][10];
  int flag=1,nEvents=0;
  char com=34;
 
  sprintf (buffer, ".data-%d",dataTime);

  cout <<"Processing"<<buffer<<"...";
  
  FILE *dataFile1 = fopen(buffer,"r");
   
  cout <<"opened...";
   while (flag == 1)
   {  
      for (int i=0;i<npara;i++)
      {	
         flag=fscanf(dataFile1,"%s",tmp);
         data[nEvents][i]=atof(tmp);
      }
      nEvents++;
   }  
  nEvents--;
  fclose(dataFile1);
  cout <<nEvents<<"event(s) loaded...sorting";

  shellSort(data,nEvents,mode,npara);

  cout <<"...sorted"<<endl;

  
     FILE *macroFile=fopen("drawEvt.c","w");
     
     fprintf(macroFile,"void plot()\n");
     fprintf(macroFile,"{\n");
     
     for (int i=0;i<nEvents;i++)
     {

     if (mode==3) // draw zx plane;
     {
              fprintf(macroFile,"circle(%f,%f,%f,1,%f,%f);\n",data[i][2],data[i][3],data[i][4],data[i][5],data[i][6]);
     } 
     
     if (mode==4)
     {
              fprintf(macroFile,"circle1(%f,%f,%f,1,%f,%f);\n",data[i][2],data[i][3],data[i][4],data[i][5],data[i][6]);     
     }
     
     }

     fprintf(macroFile,"}\n");
     fclose(macroFile);
     
     FILE *macroFile1=fopen("drawit.macro","w");
     fprintf(macroFile1,"\n\n\n");
     fprintf(macroFile1,".L circle.c\n");
     fprintf(macroFile1,"c1 = new TCanvas(%c %c, %c %c,0,0,800,800)\n",com,com,com,com);
     fprintf(macroFile1,"circle(0,0,0,500,0,2)\n");
     fprintf(macroFile1,".L drawEvt.c\n");
     fprintf(macroFile1,"plot()\n");
     fprintf(macroFile1,"TPaveLabel HELLO(1,0,0.7,0.1,%c T= %.2f fm/c %c);\n",com,dataTime/10.0,com);
     fprintf(macroFile1,"HELLO.SetFillColor(1); \n");
     fprintf(macroFile1,"HELLO.SetTextColor(5); \n");
     fprintf(macroFile1,"HELLO.SetTextSize(0.3); \n");
     fprintf(macroFile1,"HELLO.Draw(); \n");
     fprintf(macroFile1,"c1->SaveAs(%cplot%d.gif%c);\n",com,dataTime,com);
     fprintf(macroFile1,".q\n");
     
     fclose(macroFile1);
     system("root -l <drawit.macro >> ./draw.log");
  
}



int selection (float tmp[])
{

   if (tmp[6]>-1) return 1;
//   if (fabs(tmp[3])>1) return 0;
   return 0;

}
