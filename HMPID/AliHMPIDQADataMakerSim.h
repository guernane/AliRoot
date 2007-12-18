#ifndef AliHMPIDQADataMakerSim_H
#define AliHMPIDQADataMakerSim_H
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */


/* $Id$ */

//
//  Produces the data needed to calculate the quality assurance. 
//  All data must be mergeable objects.
//  A. Mastroserio



// --- ROOT system ---


class TH1F ; 
class TH2F ;
class TH1I ; 

// --- Standard library ---
#include <TString.h>
// --- AliRoot header files ---

#include "AliQADataMakerSim.h"

class AliHMPIDQADataMakerSim: public AliQADataMakerSim {

public:
  AliHMPIDQADataMakerSim() ;          // ctor
  AliHMPIDQADataMakerSim(const AliHMPIDQADataMakerSim& qadm) ;   
  AliHMPIDQADataMakerSim& operator = (const AliHMPIDQADataMakerSim& qadm) ;
  virtual ~AliHMPIDQADataMakerSim() {;} // dtor

private:
  virtual void   InitHits() ;      //book hit QA histo 
  virtual void   InitDigits() ;    //book Digit QA histo
  virtual void   InitSDigits() ;   //book SDigits QA histo
  virtual void   MakeHits(TObject * hits) ;       //Fill hit QA histo
  virtual void   MakeDigits(TObject * digits) ;   //Fill Digit QA histo
  virtual void   MakeSDigits(TObject * sdigits) ; //Fill SDigit QA histo

  TH1F *fhHitQdc;                  // Hit Q distr
  TH2F *fhHitMap[7];               // Hit Q positions
  TH1F  *fhSDigits ;               // SDigit Q distr
  TH1F  *fhDigPcEvt;               // Pc occupancy per event
  TH1F *fhDigChEvt;                // Chamber occupancy per event
  TH1F *fhDigQ;                    // Digit Q distr

//  TH1F *fhCluEvt;                  // N clusters per chamber
//  TH1F *fhCluChi2;                 // Chi2
//  TH1F *fhCluQ;                    // cluster Q distr
//  TH1F *fhCluFlg;                  // resolved cluster flag
//  TH1F *fhCluSize;                 // raw cluster size
//  TH1F *fhMipCluSize;              // mip cluster size

//  TH2F *fhCkovP;                   // thetaC vs P
//  TH2F *fhSigP;                    // sigmaC vs P
//  TH2F *fhMipXY;                   // mip position on PC
//  TH2F *fhDifXY;                   // mip(X,Y) - extrapolated track(X,Y)
//  TH1F *fhPid[5];                  // Pid responses

  ClassDef(AliHMPIDQADataMakerSim,1)  // description 

};

#endif // AliHMPIDQADataMakerSim_H
