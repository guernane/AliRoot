#ifndef ALITRACKREFERENCE_H
#define ALITRACKREFERENCE_H
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */

#include "TObject.h"
#include "TMath.h"

class AliTrackReference : public TObject {
public:
  AliTrackReference();
  virtual ~AliTrackReference() {}
  virtual Int_t GetTrack() const {return fTrack;}
  virtual Int_t Label() const {return fTrack;}
  virtual void SetTrack(Int_t track) {fTrack=track;}
  virtual void SetLabel(Int_t track) {fTrack=track;}
  virtual void SetLength(Float_t length){fLength=length;}
  virtual Float_t GetLength(){return fLength;}
  virtual Float_t X() const {return fX;}
  virtual Float_t Y() const {return fY;}
  virtual Float_t Z() const {return fZ;}
  virtual Float_t R() const {return TMath::Sqrt(fX*fX+fY*fY);}
  virtual Float_t Px() const {return fPx;}
  virtual Float_t Py() const {return fPy;}
  virtual Float_t Pz() const {return fPz;}
  virtual Float_t Pt() const {return TMath::Sqrt(fPx*fPx+fPy*fPy);}
  virtual Float_t Phi() const {return TMath::Pi()+TMath::ATan2(-fPy,-fPx);}
  virtual Float_t Theta() const {return (fZ==0)?TMath::Pi()/2:TMath::ACos(fZ/TMath::Sqrt(fX*fX+fY*fY+fZ*fZ)); }
  virtual void SetPosition(Float_t x, Float_t y, Float_t z){fX=x; fY=y; fZ=z;}
  virtual void SetMomentum(Float_t px, Float_t py, Float_t pz){fPx=px; fPy=py; fPz=pz;}
  
protected:
  Int_t     fTrack;  // Track number
  Float_t   fX;      // X reference position of the track
  Float_t   fY;      // Y reference position of the track
  Float_t   fZ;      // Z reference position of the track
  Float_t   fPx;     // momentum
  Float_t   fPy;     // momentum
  Float_t   fPz;     // momentum
  Float_t   fLength; // track lenght from its origin

  ClassDef(AliTrackReference,2)  //Base class for all Alice track references
};
#endif
