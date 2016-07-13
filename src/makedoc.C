makedoc()
//$ cat builddocs.C
{
    gSystem->Load("libAbsorptionMap.so");
    THtml html;
//    html.SetOutputDir("/Users/johanneskazantzidis/Documents/ESS/macros/STRAM/htmldoc/");
    //html.SetInputDir("$(ROOTSYS)");
    //html.SetInputDir("/Users/johanneskazantzidis/Documents/ESS/root/");
    //html.MakeAll();
    //html.SetInputDir("$(ROOTSYS):$(ROOTSYS)/include");
    //html.SetSourceDir("/Users/johanneskazantzidis/Documents/ESS/macros/STRAM/src/");
    html.SetProductName("Absorption map");
    html.MakeClass("AbsorptionMap");
}
