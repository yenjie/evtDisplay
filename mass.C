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
#include <TH1D.h>

#include <iostream>

//#include "circle.c"

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


int mass(int evt=1,bool drawIt=0)
{
   
   TFile *inf = new TFile("sample/outFile_HYDJET1p9_5p02TeVPbPb_MB_MERGED_20180817.root");
   TTree *genTree = (TTree*)inf->Get("genTree");
   TFile *outf = new TFile(Form("output/output-%d.root",evt),"recreate");

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
   


   Long64_t nentries = genTree->GetEntries();
   Long64_t nbytes = 0;

   TLorentzVector l; 
   
   TH1D *hD = new TH1D("hD","",60,1.7,2);
   TH1D *hB = new TH1D("hB","",50,5,6);
   //TCanvas *c = new TCanvas("c","",600,600);
   
   vector<particle> particles;

   genTree->GetEntry(evt);
      for (unsigned int j=0;j<genPt->size();j++)
      {
         if ((*genID)[j]==22) continue;
         TParticlePDG *partRoot = TDatabasePDG::Instance()->GetParticle((*genID)[j]);
	 if (partRoot->Charge()==0) continue;
	 if (fabs((*genEta)[j])>2.4) continue;
	 if (fabs((*genPt)[j])<0.5) continue;
	 particle p;
	 p.l.SetPtEtaPhiM((*genPt)[j],(*genEta)[j],(*genPhi)[j],partRoot->Mass());
	 p.pdg=(*genID)[j];
	 particles.push_back(p);
      }
      for (unsigned int j=0;j<particles.size();j++)
      {
	 for (unsigned int k=j+1;k<particles.size();k++)
	 {
	    l=particles[j].l+particles[k].l;
	    hD->Fill(l.Mag());
	 }
      }

      for (unsigned int j=0;j<particles.size();j++)
      {
         if (fabs(particles[j].pdg)!=13) continue;
	 for (unsigned int k=j+1;k<particles.size();k++)
	 {
            if (fabs(particles[k].pdg)!=13) continue;
	    for (unsigned int q=k+1;q<particles.size();q++)
	    {
	     l=particles[j].l+particles[k].l+particles[q].l;
	     hB->Fill(l.Mag());
	    }
	 }
      }


   if (drawIt) {
    TCanvas *c = new TCanvas("c","",600,600);
    hD->Draw();
    TCanvas *c2 = new TCanvas("c2","",600,600);
    hB->Draw();
   }
   hD->Write();
   hB->Write();
   
   return 1;
}
