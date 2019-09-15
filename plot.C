#include <TTree.h>
#include <TLorentzVector.h>
#include <TCanvas.h>
#include <TDatabasePDG.h>
#include <TParticlePDG.h>
#include <TEllipse.h>
#include <TColor.h>
#include <TVector3.h>
#include <TRandom2.h>
#include <TPaveLabel.h>
#include <TFile.h>

#include <iostream>

//#include "circle.c"

TRandom2 rnd;

class particle
{
    public:
    TVector3 p;
    TLorentzVector l;
    int pdg;
    Float_t time;
    
    Float_t getScale(Float_t time) {
    	 double beta = l.Beta();
	 double gamma = l.Gamma();
	 return beta*time/l.P();
    }
    Float_t GetX() { return p.X()+l.Px()*getScale(time);}
    Float_t GetY() { return p.Y()+l.Py()*getScale(time);}
    Float_t GetZ() { return p.Z()+l.Pz()*getScale(time);}
    
};

struct comparePy
{
    inline bool operator() (particle& p1, particle& p2)
    {
        return (p1.GetY() < p2.GetY());
    }    
};

void genSph(TVector3 &r)
{
    static Float_t rPb=7.;
    r.SetX(1000);
    while (r.Mag()>rPb) {	 
       r.SetX(rnd.Rndm()*rPb*2-rPb);
       r.SetY(rnd.Rndm()*rPb*2-rPb);
       r.SetZ((rnd.Rndm()*rPb*2-rPb)/5020./2);
    }
}


int circle(float x,float y,float z,float r,float c,float flag)
{
   static int begin=1;
   const int nColor=40;
   static int mesonColor[nColor], baryonColor[nColor];
   if (begin==1) {
      TColor *color;
      for (int i=0;i<nColor;i++)
      {
         mesonColor[i]=1180+i;
         double f=(i)/(double)nColor;
	 color = new TColor(mesonColor[i],f,f,f);
         baryonColor[i]=1180+nColor+i;
         color = new TColor(baryonColor[i],0.,0.,f*0.4+0.6);
      }
   
      begin=0;
   }
//   if (fabs(y)>10) return 0; 
   
   double size=200;   //  size of the canvas

   double px=x/size+0.5;
   double py=y/size+0.5;
   double pz=z/size+0.5;
   double rad=r/size;

   int cset=0;
   int particle=c;
   if (fabs(particle)<2000) {cset=kGray;}     // meson
   if (fabs(particle)>2000) {cset=kBlue;}     // baryon
   if (flag==4) cset=kRed;
   if (particle==197)      {cset=kBlue;};   // disk
   if (particle==0) cset=kBlack;
   
//   if (cset==kRed||cset==kBlack) {
//      cset=kRed;
   if (cset!=kGray&&cset!=kBlue) {
      TEllipse* ell1 = new TEllipse(pz,px,rad,rad);
      ell1->SetFillColor(cset);
      ell1->SetLineColor(cset);
   
      ell1->Draw();
        
   } else {
      int grad=nColor-1	;
      for (int n=1;n<=grad;n++){
         double rad2=rad*(grad-n)/(double)grad;
         TEllipse* ell = new TEllipse(pz+n/(double)nColor*0.2/size,px+n/(double)nColor*0.2/size,rad2,rad2);
         int col;
         if (cset==kGray) col = mesonColor[n];
         if (cset==kBlue) col = baryonColor[n];
         ell->SetFillColor(col);
         ell->SetLineColor(col);
         ell->Draw();
      }
   }
   
   return 0;
}
   
   


int plot(int evtNum=1,double time=0,int id=0, bool qgpOnly = false)
{
   cout <<time<<endl;
   TCanvas *c = new TCanvas("c","",0,0,1600,1600);
   circle(0,0,0,500,0,2);
   cout <<"I am alive"<<endl;
   TFile *inf = new TFile("sample/outFile_HYDJET1p9_5p02TeVPbPb_MB_MERGED_20180817.root");
   TTree *genTree = (TTree*)inf->Get("genTree");
   cout <<genTree<<endl;

   Float_t         bGen;
   Float_t         nBColl;
   Float_t         nBPart;
   Int_t           nGen;
   vector<float>   *genPt = nullptr;
   vector<float>   *genPhi = nullptr;
   vector<float>   *genEta = nullptr;
   vector<int>     *genID = nullptr;
   
   

   // List of branches
   TBranch        *b_bGen;   //!
   TBranch        *b_nBColl;   //!
   TBranch        *b_nBPart;   //!
   TBranch        *b_nGen;   //!
   TBranch        *b_genPt;   //!
   TBranch        *b_genPhi;   //!
   TBranch        *b_genEta;   //!
   TBranch        *b_genID;   //!

   genTree->SetBranchAddress("bGen", &bGen, &b_bGen);
   genTree->SetBranchAddress("nBColl", &nBColl, &b_nBColl);
   genTree->SetBranchAddress("nBPart", &nBPart, &b_nBPart);
   genTree->SetBranchAddress("nGen", &nGen, &b_nGen);
   genTree->SetBranchAddress("genPt", &genPt, &b_genPt);
   genTree->SetBranchAddress("genPhi", &genPhi, &b_genPhi);
   genTree->SetBranchAddress("genEta", &genEta, &b_genEta);
   genTree->SetBranchAddress("genID", &genID, &b_genID);


   cout <<"I am alive"<<endl;
   Long64_t nentries = genTree->GetEntries();
   cout <<nentries<<endl;
   cout <<"I am alive"<<endl;
   Long64_t nbytes = 0;

   TLorentzVector l; 
   
   genTree->GetEntry(evtNum);
   vector<particle> particles;

   if (genPt == nullptr) {
      cout <<"invalid event"<<endl;
   } else {
      for (int j=0;j<208;j++){
	 particle p;
	 p.l.SetPxPyPzE(0.,0,-2510,sqrt(2510*2510+0.938*0.938));
	 genSph(p.p);
	 p.time=time;
	 p.pdg=197;
	 particles.push_back(p);
      
      }
      for (int j=0;j<208;j++){
	 particle p;
	 p.l.SetPxPyPzE(0.,0,2510,sqrt(2510*2510+0.938*0.938));
	 genSph(p.p);
	 p.time=time;
	 p.pdg=197;
	 particles.push_back(p);
      
      }
      if (time>0) {
      for (unsigned int j=0;j<genPt->size();j++)
      {
         if ((*genID)[j]==22) continue;
         TParticlePDG *partRoot = TDatabasePDG::Instance()->GetParticle((*genID)[j]);
	 particle p;
	 p.l.SetPtEtaPhiM((*genPt)[j],(*genEta)[j],(*genPhi)[j],partRoot->Mass());
	 p.pdg=(*genID)[j];
	 genSph(p.p);
	 p.time=time;
	 particles.push_back(p);
      }
      }     
      sort (particles.begin(), particles.end(), comparePy());
      for (unsigned int j=0;j<particles.size();j++)
      {
	 double beta = particles[j].l.Beta();
	 double gamma = particles[j].l.Gamma();
	 int flag = 5;
	 if (time/gamma<1) flag=4; 
	 for (unsigned int k=1;k<particles.size();k++)
	 {
	    
	    if ((j<k)||flag==4) continue;
	    double dy=particles[j].GetY()-particles[j-k].GetY();
	    if (dy>1) continue;
	    TVector3 tmp(particles[j].GetX()-particles[j-k].GetX(),
	                 particles[j].GetY()-particles[j-k].GetY(),
			 particles[j].GetZ()-particles[j-k].GetZ());
	    if (tmp.Mag()<1.) {
	       flag=4;		 // overlap
	    }
	 }

         for (unsigned int k=1;k<particles.size();k++)
	 {
	    if ((j+k>=particles.size())||flag==4) continue;
	    double dy=particles[j].GetY()-particles[j+k].GetY();
	    if (dy>1) continue;
	    TVector3 tmp(particles[j].GetX()-particles[j+k].GetX(),
	                 particles[j].GetY()-particles[j+k].GetY(),
			 particles[j].GetZ()-particles[j+k].GetZ());
	    if (tmp.Mag()<1.) {
	       flag=4;		 // overlap
	    }
	 }	 
	 //cout <<particles[j].l.Py()<<" "<<particles[j].pdg<<" "<<time/gamma<<" "<<flag<<endl;
	 double scale = beta*time/particles[j].l.P();
         if (qgpOnly&&flag!=4&&particles[j].pdg!=197) continue;
         circle(particles[j].p.X()+particles[j].l.Px()*scale,
	        particles[j].p.Y()+particles[j].l.Py()*scale,
		particles[j].p.Z()+particles[j].l.Pz()*scale
		,1,particles[j].pdg,flag);
      }
   }      
   TPaveLabel *timeLabel = new TPaveLabel(0.8,0,0.8,0.1,Form(" T= %.2f fm/c ",time));
   timeLabel->SetFillColor(1);
   timeLabel->SetFillStyle(0); 
   timeLabel->SetTextColor(5); 
   timeLabel->SetTextSize(0.3);
   timeLabel->Draw(); 

   TPaveLabel *groupLabel = new TPaveLabel(0.4,0.9,0.4,1," MIT Heavy Ion Event Display: Pb+Pb 5.02 TeV ");
   groupLabel->SetFillColor(1); 
   groupLabel->SetFillStyle(0); 
   groupLabel->SetTextColor(0); 
   groupLabel->SetTextSize(0.3);
   groupLabel->Draw(); 

   TPaveLabel *codeLabel = new TPaveLabel(0.3,0.0,0.3,0.1," Yen-Jie Lee, Andre S. Yoon and Wit Busza ");
   codeLabel->SetFillColor(1); 
   codeLabel->SetFillStyle(0); 
   codeLabel->SetTextColor(0); 
   codeLabel->SetTextSize(0.3);
   codeLabel->Draw(); 


   c->SaveAs(Form("plot/result-%05d.png",id));
   return 1;
}
