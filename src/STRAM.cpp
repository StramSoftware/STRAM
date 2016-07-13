#include <TApplication.h>
#include "TCanvas.h"
#include "THnSparse.h"
#include "TFile.h"
#include "TH2.h"
#include "TH1.h"
#include "TKey.h"
#include "TVirtualX.h"
#include "AbsorptionMap.h"
#include "TObject.h"
#include <TStyle.h>
#include <iostream>
#include <vector>


vector<TString> stringVector(int n, char **fileNames){
    vector<TString> vec;
    for (int i=1; i<n; i++) {
        vec.push_back(fileNames[i]);
    }
    return vec;
}

void help(){
    cerr << "List of files is missing" << endl;
}

int main(int argc, char **argv)
{
    if (argc<2) {
        help();
        return 1; // A non-zero return indicates something is wrong.
    }
    vector<TString> files = stringVector(argc, argv);
    
    TApplication theApp("STRAM", &argc, argv);
    
    AbsorptionMap *stramMap = new AbsorptionMap("stramMap", files);
    stramMap->SetResponseFunction("virtualRF.root");
    //stramMap->SetResponseFunction("RealGammaRF.root");
    TCanvas *c1 = new TCanvas;
    //TCanvas *c2 = new TCanvas("Radiation Map", "Radiation Map", 0,0,1366,350);
    c1->SetTitle("STRAM");
    stramMap->SetRadMapXTitle("x");
    stramMap->SetRadMapYTitle("y");
    stramMap->SetRadMapZTitle("#Phi (n/cm^{2}/s)");
    stramMap->SetAbsMapXTitle("x");
    stramMap->SetAbsMapYTitle("y");
    stramMap->SetAbsMapZTitle("D (Gy/h)");
    stramMap->SetRFXTitle("E (MeV)");
    stramMap->SetRFYTitle("Gy/h/#Phi");
    stramMap->SetRFTitle("Virtual neutron response function");
    //stramMap->SetAbsMapPaletteRange(0.00000000001, 0.0000001);
    stramMap->Draw("stramMap");

    theApp.Run();
    delete stramMap;
    return 0;

}