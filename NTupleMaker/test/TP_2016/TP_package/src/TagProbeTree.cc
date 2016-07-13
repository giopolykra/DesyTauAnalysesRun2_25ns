#define TagProbeTree_cxx
#include "DesyTauAnalyses/NTupleMaker/interface/TagProbeTree.h"

//Inizialization
TagProbeTree::TagProbeTree(TTree *tree) : fChain(0) {
  lock = false;
  ientry = -2;
  
  if (!tree) return;
  
  Init(tree);
}

void TagProbeTree::Init(TTree *tree){
  if(!tree) return;
	      
  if(tree->GetEntries())
    ReadInit(tree);
  else
    WriteInit(tree);
}

// Destructors
TagProbeTree::~TagProbeTree(){
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

// Read methods
void TagProbeTree::ReadInit(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   if (lock) return;
   ReadReset();
   
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("evt", &evt, &b_evt);  
   
   fChain->SetBranchAddress("pt_tag", &pt_tag, &b_pt_tag); 
   fChain->SetBranchAddress("eta_tag", &eta_tag, &b_eta_tag); 
   fChain->SetBranchAddress("phi_tag", &phi_tag, &b_phi_tag); 

   fChain->SetBranchAddress("pt_probe", &pt_probe, &b_pt_probe); 
   fChain->SetBranchAddress("eta_probe", &eta_probe, &b_eta_probe); 
   fChain->SetBranchAddress("phi_probe", &phi_probe, &b_phi_probe); 

   fChain->SetBranchAddress("m_vis", &m_vis, &b_m_vis); 

   fChain->SetBranchAddress("id_probe", &id_probe, &b_id_probe);
   fChain->SetBranchAddress("iso_probe", &iso_probe, &b_iso_probe);

   fChain->SetBranchAddress("hlt_1_probe", &hlt_1_probe, &b_hlt_1_probe);
   fChain->SetBranchAddress("hlt_2_probe", &hlt_2_probe, &b_hlt_2_probe);
   fChain->SetBranchAddress("hlt_3_probe", &hlt_3_probe, &b_hlt_3_probe);
   fChain->SetBranchAddress("hlt_4_probe", &hlt_4_probe, &b_hlt_4_probe);
   fChain->SetBranchAddress("hlt_5_probe", &hlt_5_probe, &b_hlt_5_probe);
   fChain->SetBranchAddress("hlt_6_probe", &hlt_6_probe, &b_hlt_6_probe);
   fChain->SetBranchAddress("hlt_7_probe", &hlt_7_probe, &b_hlt_7_probe);
   fChain->SetBranchAddress("hlt_8_probe", &hlt_8_probe, &b_hlt_8_probe);
   fChain->SetBranchAddress("hlt_9_probe", &hlt_9_probe, &b_hlt_9_probe);
   fChain->SetBranchAddress("hlt_10_probe", &hlt_10_probe, &b_hlt_10_probe);

   fChain->SetBranchAddress("mcweight", &mcweight, &b_mcweight); 
   fChain->SetBranchAddress("pu_weight", &pu_weight, &b_pu_weight); 


   lock=true;

}

void TagProbeTree::ReadReset(){
  ientry = -2;
}

Long64_t TagProbeTree::GetEntries(){
  if (!fChain) return -1;
  
  return fChain->GetEntriesFast();
}

Long64_t TagProbeTree::LoadTree(Long64_t entry){
  // Set the environment to read one entry
  if (!fChain) return -5;
  
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  
  if (fChain->GetTreeNumber() != fCurrent)
    fCurrent = fChain->GetTreeNumber();

  ientry = entry;
  return centry;
}

Long64_t TagProbeTree::GetEntry(Long64_t entry){
  // Read contents of entry.
  // Sequential reading if entry < 0
  
  if (!fChain) return -1;

  if (entry < 0){
    if(ientry < 0) ientry = -1;

    ++ientry;
    entry = ientry;
  }

  if (LoadTree(entry) < 0) return -1;

  return fChain->GetEntry(entry);
}

Long64_t TagProbeTree::LoadedEntryId(){
  return ientry;
}

void TagProbeTree::Show(Long64_t entry){
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

Int_t TagProbeTree::Cut(Long64_t entry){
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}

void TagProbeTree::WriteInit(TTree *tree) {
  if (!tree) return;
   
  fChain = tree;
  fCurrent = -1;

  fChain->Branch("run", &run, "run/I");
  fChain->Branch("lumi", &lumi, "lumi/I");
  fChain->Branch("evt", &evt, "evt/I");

  fChain->Branch("pt_tag", &pt_tag, "pt_tag/F");
  fChain->Branch("eta_tag", &eta_tag, "eta_tag/F");
  fChain->Branch("phi_tag", &phi_tag, "phi_tag/F");

  fChain->Branch("pt_probe", &pt_probe, "pt_probe/F");
  fChain->Branch("eta_probe", &eta_probe, "eta_probe/F");
  fChain->Branch("phi_probe", &phi_probe, "phi_probe/F");

  fChain->Branch("m_vis", &m_vis, "m_vis/F");


  fChain->Branch("id_probe", &id_probe, "id_probe/B");
  fChain->Branch("iso_probe", &iso_probe, "iso_probe/F");

  fChain->Branch("hlt_1_probe", &hlt_1_probe, "hlt_1_probe/I");
  fChain->Branch("hlt_2_probe", &hlt_2_probe, "hlt_2_probe/I");
  fChain->Branch("hlt_3_probe", &hlt_3_probe, "hlt_3_probe/I");
  fChain->Branch("hlt_4_probe", &hlt_4_probe, "hlt_4_probe/I");
  fChain->Branch("hlt_5_probe", &hlt_5_probe, "hlt_5_probe/I");
  fChain->Branch("hlt_6_probe", &hlt_6_probe, "hlt_6_probe/I");
  fChain->Branch("hlt_7_probe", &hlt_7_probe, "hlt_7_probe/I");
  fChain->Branch("hlt_8_probe", &hlt_8_probe, "hlt_8_probe/I");
  fChain->Branch("hlt_9_probe", &hlt_9_probe, "hlt_9_probe/I");
  fChain->Branch("hlt_10_probe", &hlt_10_probe, "hlt_10_probe/I");

  fChain->Branch("mcweight", &mcweight, "mcweight/F");
  fChain->Branch("pu_weight", &pu_weight, "pu_weight/F");

}

void TagProbeTree::Fill(){
  if(!fChain) return;
  if(lock) return;

  fChain->Fill();
}