#include "TPaletteAxis.h"
#include "TCanvas.h"
#include "THnSparse.h"
#include "TFile.h"
#include "TH3.h"
#include "TH2.h"
#include "TH1.h"
#include "TAxis.h"
#include "TKey.h"
#include "TROOT.h"
#include "TExec.h"
#include "TSystem.h"
#include "TMath.h"
#include "TImage.h"
#include <TStyle.h>
#include <TString.h>
#include <sstream>
#include <string>
#include <limits.h>
#include <unistd.h>
#include <iostream>

using namespace std;

#ifndef AbsorptionMAP_H // If not defined
#define AbsorptionMAP_H

class AbsorptionMap { //: public TObject {
    
private:
    // Member variables
    vector<TString>         fFileNames;             // Names of imported files
    const char              *fName;                 // -> Pointer to object name
    const char              *fRadName;              // -> Pointer to radiation map name
    const char              *fAbsName;              // -> Pointer to absorption map name
    Int_t                   fNumberOfFiles;         // Number of imported files
    vector<THnSparseF*>     fRmesh;                 // Imported mesh grids
    Int_t                   fMeshCount;             // Number of imported mesh grids
    THnSparseF              *fRadMap;               // -> Pointer to radiation map
    Int_t                   fRadMax;                // Logarithmic maximum value of bin content in radiation map
    Int_t                   fRadMin;                // Logarithmic minimum value of bin content in radiation map
    Int_t                   fAbsMax;                // Logarithmic maximum value of bin content in absorption map
    Int_t                   fAbsMin;                // Logarithmic minimum value of bin content in radiation map
    TString                 fRFName;                // Response function file name
    TH1F                    *fRF;                   // -> Pointer to response function histogram
    THnSparseF              *fAbsMap;               // -> Pointer to absorption map
    
    Bool_t                  fIsAbsMap;              // Flag to generate absorption map
    Int_t                   fX;                     // Number of bins x dimension of radiation map
    Int_t                   fY;                     // Number of bins y dimension of radiation map
    Int_t                   fZ;                     // Number of bins z dimension of radiation map
    Int_t                   fRFBins;                // Number of bins in response function histogram
    static Bool_t           fAutoUpdate;            // Flag to enable/disable auto update of energy spectra for maps
    TH2                     *fRadMapProjection;     // -> Pointer to radiation map projection
    TH2                     *fAbsMapProjection;     // -> Pointer to absorption map projection
    
    // Member functions
    void                    GetMeshGrids();
    void                    CreateMesh(TString);
    void                    GenerateRadMap();
    Double_t                GetAbsContent(Int_t, Double_t);
    void                    GenerateAbsMap();

public:
    // Constructor
    AbsorptionMap(const char*, vector<TString>);
    
    // Destructor
    virtual                 ~AbsorptionMap();
    
    // Accessor Functions
    virtual void            Draw(Option_t *option="");
    static void             AbsExec(THnSparseF *hist, TPad *pad, Int_t, Int_t, Int_t, Int_t, TH1F *rfhist = 0);
    static void             RFExec(TH1F *h, TPad *pad);
    static void             LogoExec(TImage *img, TPad *pad);
    
    // Mutator Functions
    void                    SetResponseFunction(const char*);
    void                    SetRadMapXTitle(const char*);
    void                    SetRadMapYTitle(const char*);
    void                    SetRadMapZTitle(const char*);
    void                    SetRadMapTitle(const char*);
    void                    SetAbsMapXTitle(const char*);
    void                    SetAbsMapYTitle(const char*);
    void                    SetAbsMapZTitle(const char*);
    void                    SetAbsMapTitle(const char*);
    void                    SetRFXTitle(const char*);
    void                    SetRFYTitle(const char*);
    void                    SetRFTitle(const char*);
    void                    SetAbsMapPaletteRange(Double_t, Double_t);


    ClassDef(AbsorptionMap, 1); // Radiation absorption map of a given device in a given environment
};

#endif