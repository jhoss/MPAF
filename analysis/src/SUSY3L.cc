/*****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Multi-Purpose Analysis Framework                                     **
**                                                                          **
** Jan Hoss, ETHZ, 12/2014                                  **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/

#include "analysis/src/SUSY3L.hh"


/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
SUSY3L::SUSY3L(std::string cfg){
    /* 
        constructs the SUSY3L class 
        parameters: configuration_file
        return: none
    */
	
    //_verbose->Class("SUSY3L");
    startExecution(cfg);
    initialize();

    _hltLines.push_back("HLT_DoubleMu");
    _hltLines.push_back("HLT_DoubleEl");
    _hltLines.push_back("HLT_MuEG");
    _hltLines.push_back("HLT_DoubleMuHT");
    _hltLines.push_back("HLT_DoubleElHT");
    _hltLines.push_back("HLT_SingleMu");
    _hltLines.push_back("HLT_SingleEl");

}


//____________________________________________________________________________
SUSY3L::~SUSY3L(){
    /* 
        destructs the SUSY3L class 
        parameters: none
        return: none
    */

}


//____________________________________________________________________________
void SUSY3L::initialize(){
    /*
        initializes the SUSY3L class
        parameters: none
        return: none
    */

    // define variables using _vc varibale class
    // _vc->registerVar("name"           , "type");
    _vc->registerVar("run"                             );    //run number
    _vc->registerVar("lumi"                            );    //lumi section number
    _vc->registerVar("evt"                             );    //event number
    _vc->registerVar("isData"                          );    //identify data
    
    _vc->registerVar("nLepGood"                        );    //number of leptons in event
    _vc->registerVar("LepGood_pdgId"                   );    //identifier for leptons (11: electron, 13: muon)
    _vc->registerVar("LepGood_pt"                      );    //pT of leptons
    _vc->registerVar("LepGood_eta"                     );    //eta of leptons track
    _vc->registerVar("LepGood_etaSc"                   );    //eta of leptons super cluster in Ecal
    _vc->registerVar("LepGood_phi"                     );    //phi of leptons
    _vc->registerVar("LepGood_charge"                  );    //charge of lepton +1 or -1
    _vc->registerVar("LepGood_relIso03"                );    //relative isolation of the lepton, cone dimensions?
    _vc->registerVar("LepGood_miniRelIso"              );    //relIso with pt dependent cone
    _vc->registerVar("LepGood_jetPtRatio"              );    //pt lepton over pt aka4 jet
    _vc->registerVar("LepGood_jetPtRatio_LepAwareJECv2" );   //
    _vc->registerVar("LepGood_jetPtRel"                );    //
    _vc->registerVar("LepGood_jetPtRelv2"              );    //
    
    
    _vc->registerVar("LepGood_dz"                      );    //difference to reconstructed primary vertex in z direction
    _vc->registerVar("LepGood_dxy"                     );    //difference to reconstructed primary vertex in xy plane
    _vc->registerVar("LepGood_sip3d"                   );    //similar observable as dxy, also vertex cut
    _vc->registerVar("LepGood_tightCharge"             );    //indicates reliability of charge measurement, values 0,1,2
    _vc->registerVar("LepGood_eleCutIdCSA14_50ns_v1"   );    //indicates reliability of electron identification [-1;4]
    _vc->registerVar("LepGood_convVeto"                );    //0 (veto) or 1 (no veto), calculated from partner track
    _vc->registerVar("LepGood_lostHits"                );    //number of missing hits in pixel detector
    _vc->registerVar("LepGood_tightId"                 );    //0 or 1 (loose and tight criteria?)
    _vc->registerVar("LepGood_dEtaScTrkIn"             );    //delta eta between track and supercluster in Ecal
    _vc->registerVar("LepGood_dPhiScTrkIn"             );    //delta phi between track and supercluster in Ecal
    _vc->registerVar("LepGood_hadronicOverEm"          );    //
    _vc->registerVar("LepGood_sigmaIEtaIEta"           );    //
    _vc->registerVar("LepGood_eInvMinusPInv"           );    //
    _vc->registerVar("LepGood_mediumMuonId"            );    //mva medium wp muon identification
    _vc->registerVar("LepGood_mvaIdPhys14"             );    //mva electron ID
     
    _vc->registerVar("nTauGood"                        );    //number of taus in event
    _vc->registerVar("TauGood_pdgId"                   );    //identifier for taus (15)
    _vc->registerVar("TauGood_pt"                      );    //pT of tau
    _vc->registerVar("TauGood_eta"                     );    //eta of tau
    _vc->registerVar("TauGood_phi"                     );    //phi of tau
    _vc->registerVar("TauGood_charge"                  );    //charge of tau +1 or -1
    _vc->registerVar("TauGood_idAntiMu"                );     //tau muon discriminator
    _vc->registerVar("TauGood_idAntiE"                 );     //tau electron discriminator
    _vc->registerVar("TauGood_idDecayMode"             );     //
    _vc->registerVar("TauGood_isoCI3hit"               );     //
    
    _vc->registerVar("nJet"                            );    //number of jets in the event
    _vc->registerVar("Jet_pt"                          );    //pT of each of the nJet jets
    _vc->registerVar("Jet_eta"                         );    //eta of each of the nJet jets
    _vc->registerVar("Jet_phi"                         );    //phi of each of the nJet jets
    _vc->registerVar("Jet_id"                          );    //jet identifier (>=1: 8TeV loose recommendation)
    _vc->registerVar("Jet_btagCSV"                     );     //b-tagging quantity (-1 or [0;1]
    _vc->registerVar("Jet_muEF"                        );     //fraction of muon pt in jet
    _vc->registerVar("Jet_mass"                        );     //jet mass

    _vc->registerVar("met_pt"                          );     //missing tranvers momentum
    _vc->registerVar("met_phi"                         );     //phi of missing transvers momentum
    _vc->registerVar("HLT_DoubleMu"                    );     //HLT trigger path decition (1 fired, 0 else)
    _vc->registerVar("HLT_SingleMu"                    );
    _vc->registerVar("HLT_DoubleEl"                    );
    _vc->registerVar("HLT_SingleEl"                    );
    _vc->registerVar("HLT_MuEG"                        );
    _vc->registerVar("HLT_DoubleMuHT"                  );
    _vc->registerVar("HLT_DoubleElHT"                  );
    
    _vc->registerVar("genWeight"                       );       //generator weight to account for negative weights in MCatNLO
    _vc->registerVar("vtxWeight"                       );       //number of vertices for pile-up reweighting 



    //additional counter categories
    _au->addCategory( kElId, "el Id");
    _au->addCategory( kMuId, "muon Id");
    _au->addCategory( kTauId, "tau Id");
    _au->addCategory( kJetId, "jet Id");
    _au->addCategory( kBJetId, "b-jet Id");
    _au->addCategory( conZEvents, "Z events");
                 
    //config file input variables
    _pairmass = getCfgVarS("pairMass");
    _selectMuons = getCfgVarS("selectMuons");
    _selectElectrons = getCfgVarS("selectElectrons");
    _selectTaus = getCfgVarS("selectTaus");
    _BR = getCfgVarS("baselineRegion");
    _SR = getCfgVarS("signalRegion");

    //workflows
    //addWorkflow( kWZCR, "WZCR");
    

}


//____________________________________________________________________________
void SUSY3L::modifyWeight() {
    /*
        modifies the event weight for every entry in the tree
        parameters: none
        return: none
    */ 
    if (_vc->get("isData") != 1){
        _weight *= _vc->get("genWeight");
        _weight *= _vc->get("vtxWeight");
    }

}


//____________________________________________________________________________
void SUSY3L::run(){

    // clear object category vectors from previous event
    _els.clear();
    _mus.clear();
    _taus.clear();
    _elIdx.clear();
    _muIdx.clear();
    _tauIdx.clear();
    _jets.clear();
    _bJets.clear();
    _leps.clear();
    
    // increment event counter, used as denominator for yield calculation
    counter("denominator");

    //check HLT trigger decition, only let triggered events pass
    if(!passMultiLine(false)) return;
    counter("HLT");

    //initialize multiIso working points
    setMultiIsoWP();
    
    // do the minimal selection and collect kinematic variables for events passing it
    collectKinematicObjects();

    // initialization of baseline region cuts, baseline event selection, and filling of
    // event based observables in plots
    setBaselineRegion();
    
    //check if event goes into baseline selection
    //if(!makeCut(baseSelection(),"base selection")){	
    if(!(baseSelection())){	
        //if event fails baseline selection check if it goes to WZ control region
        //wzCRSelection();
        //back to global workflow
        //setWorkflow(kGlobal);
        return;
    }

    //fillSkimTree();
    fillEventPlots();

    // initialization of signal region cuts, categorization of events passing the baseline 
    // selection into different signal regions, and filling of plots
    
    //setSignalRegion();
    //if(!srSelection()) return;	
    //fillEventPlots("SR");
   
}



/*****************************************************************************
******************************************************************************
** DEFINE INPUTS AND OUTPUTS                                                **
******************************************************************************
*****************************************************************************/

//____________________________________________________________________________
void SUSY3L::defineOutput(){
    /*
        defines and reserves all output that is produced in this class
        parameters: none
        return: none
    */
    
    //event based observables for baseline region 
    _hm->addVariable("HT"        , 1000,   0.0, 1000.0, "H_T [GeV]"                      );
    _hm->addVariable("MET"       , 1000,   0.0, 1000.0, "#slash{E}_T [GeV]"              );
    _hm->addVariable("NBJets"    ,   20,   0.0,   20.0, "b-jet multiplicity"             );
    _hm->addVariable("NJets"     ,   20,   0.0,   20.0, "jet multiplicity"               ); 

    //additional observables
    _hm->addVariable("Zmass"            ,  150,     0.0,  150.0,    "Z candidate mass [GeV]"            );
    _hm->addVariable("Zpt"              ,  150,     0.0,  150.0,    "Z candidate pt [GeV]"              );
    _hm->addVariable("MT2"              ,  400,     0.0,  400.0,    "MT2 [GeV]"                         );
    _hm->addVariable("MT"               ,  400,     0.0,  400.0,    "MT [GeV]"                          );
    _hm->addVariable("3rd_lepton_flavor",  40,      -20,  20.0,    "3rd lepton pdgId"                   );
    _hm->addVariable("deltaR_elmu"      ,  500,     0.0,  10.0,     "delta R between el and mu"         );
    _hm->addVariable("el_multiplicity"  ,  10,      0.0,  10.0,     "electron multiplicity"             );
    _hm->addVariable("mu_multiplicity"  ,  10,      0.0,  10.0,     "muon multiplicity"                 );
    _hm->addVariable("tau_multiplicity" ,  10,      0.0,  10.0,     "tau multiplicity"                  );
    _hm->addVariable("lep_multiplicity" ,  10,      0.0,  10.0,     "lepton multiplicity"               );
    _hm->addVariable("pt_1st_lepton"    ,  200,     0.0,  200.0,    "pt of leading lepton [GeV]"        );
    _hm->addVariable("pt_2nd_lepton"    ,  200,     0.0,  200.0,    "pt of 2nd lepton [GeV]"            );
    _hm->addVariable("pt_3rd_lepton"    ,  200,     0.0,  200.0,    "pt of 3rd lepton [GeV]"            );
    _hm->addVariable("lowMll"           ,  400,     0.0,  400.0,    "smallest ossf pair mll [GeV]"      );
    _hm->addVariable("muon_SIP3d"       ,   50,     0.0,    5.0,    "muon SIP3d"                        );
    _hm->addVariable("muon_dxy"         ,  600,     0.0,  600.0,    "muon dxy [um]"                     );
    _hm->addVariable("muon_dz"          ,  600,     0.0,  600.0,    "muon dz [um]"                      );
    _hm->addVariable("muon_JetPtRatio"  ,   60,     0.0,    2.0,    "muon jet pt ratio [GeV]"           );
    _hm->addVariable("muon_JetPtRel"    ,   40,     0.0,  100.0,    "muon jet pt rel [GeV]"             );
    _hm->addVariable("muon_miniRelIso"  ,   40,     0.0,    0.4,    "muon isolation"                    );
    _hm->addVariable("el_SIP3d"         ,   50,     0.0,    5.0,    "electron SIP3d"                    );
    _hm->addVariable("el_dxy"           ,  600,     0.0,  600.0,    "electron dxy [um]"                 );
    _hm->addVariable("el_dz"            ,  600,     0.0,  600.0,    "electron dz [um]"                  );
    _hm->addVariable("el_JetPtRatio"    ,   60,     0.0,    2.0,    "electron jet pt ratio [GeV]"       );
    _hm->addVariable("el_JetPtRel"      ,   40,     0.0,  100.0,    "electron jet pt rel [GeV]"         );
    _hm->addVariable("el_miniRelIso"    ,   40,     0.0,    0.4,    "electron isolation"                );

}


//____________________________________________________________________________
void SUSY3L::loadInput(){
    /*
        loads all input from the cache or from the database
        parameters: none
        return: none
    */

    // define function in MPAF for loading histograms, text files, histograms from database 
}





//____________________________________________________________________________
void SUSY3L::writeOutput(){
    /*
        writes all output of this class to the disk
        paramters: none
        return: none
    */

    //_hm -> saveHistos("SUSY3L", _cfgName);
    //_au -> saveNumbers("SUSY3L", _cfgName);

}


//____________________________________________________________________________
void SUSY3L::modifySkimming(){
// if adding variables to the skimmed tree is needed...

}


/******************************************************************************
*******************************************************************************
*** OBJECT SELECTIONS                                                        **
*******************************************************************************
******************************************************************************/

void SUSY3L::collectKinematicObjects(){

    /*
        collects all kinematic objects needed in the code, i.e. applies all object selections
        parameters: none
        return: none
    */
  
    if(_selectMuons == "true"){ 
    // loop over all nLepGood leptons in this event and select muons
    for(int i = 0; i < _vc->get("nLepGood"); ++i){
        // check which of the nLepGood leptons are muons, identifier 13
        if(std::abs(_vc->get("LepGood_pdgId",i)) == 13){
            //select muons
            if(muonSelection(i)) {
                _mus.push_back( Candidate::create(_vc->get("LepGood_pt", i),
                                                  _vc->get("LepGood_eta", i),
                                                  _vc->get("LepGood_phi", i),
                                                  _vc->get("LepGood_pdgId", i),
                                                  _vc->get("LepGood_charge", i),
                                                  0.105) );     //muon mass
                _muIdx.push_back(i);
            }
        }
    }
    }
    //number of muons in event   
    _nMus = _mus.size();
    
    if(_selectElectrons == "true"){ 
    // loop over all nLepGood leptons in this event and select electrons
    for(int i = 0; i < _vc->get("nLepGood"); ++i){
        // check which of the nLepGood leptons are electrons, identifier 11
        if(std::abs(_vc->get("LepGood_pdgId",i)) == 11){
            //select electrons
            if(electronSelection(i)) {
                //if electron passes electron selection, create electron candidate 
                //with respective kinematic variables and append it to _els vector
                _els.push_back( Candidate::create(_vc->get("LepGood_pt", i),
                                                  _vc->get("LepGood_eta", i),
                                                  _vc->get("LepGood_phi", i),
                                                  _vc->get("LepGood_pdgId", i),
                                                  _vc->get("LepGood_charge", i),
                                                  0.0005) );    //electron mass
                _elIdx.push_back(i);
            }
        }
    }
    }
  
    //number of electrons in the event
    _nEls = _els.size();


    if(_selectTaus == "true"){ 
    // loop over all taus and apply selection
    for(int i = 0; i < _vc->get("nTauGood"); ++i){
        // check which of the taus have tau identifier 15 (actually not needed)
        if(std::abs(_vc->get("TauGood_pdgId",i)) == 15){
            //select taus
            if(tauSelection(i)){
                _taus.push_back( Candidate::create(_vc->get("TauGood_pt", i),
                                                   _vc->get("TauGood_eta", i),
                                                   _vc->get("TauGood_phi", i),
                                                   _vc->get("TauGood_pdgId", i),
                                                   _vc->get("TauGood_charge", i),
                                                   1.777) );     //tau mass
                _tauIdx.push_back(i);
            }
        }
    }
    }
    //number of taus in the event
    _nTaus = _taus.size();


    // loop over all jets of the event
    for(int i = 0; i < _vc->get("nJet"); ++i){
        //if jet passes good jet selection, create a jet candidate and fetch kinematics  
        if(goodJetSelection(i)) {
            _jets.push_back( Candidate::create(_vc->get("Jet_pt", i),
                                               _vc->get("Jet_eta", i),
                                               _vc->get("Jet_phi", i)));
        }
    }
    //number of jets in event
    _nJets = _jets.size();
    
    // loop over all jets of the event
    for(int i = 0; i < _vc->get("nJet"); ++i){
        //if jet passes bjet selection, create a b-jet candidate and fetch kinematics  
        if(bJetSelection(i) ) {
            _bJets.push_back( Candidate::create(_vc->get("Jet_pt", i),
                                                _vc->get("Jet_eta", i),
                                                _vc->get("Jet_phi", i)));
        }
    }

    //number of (b-)jets in the event
    _nBJets = _bJets.size();
    _nJets = _jets.size();
   
    //compute sum of jet pT's 
    _HT = HT();

    //create met candidate for every event
    _met = Candidate::create(_vc->get("met_pt"), _vc->get("met_phi") );

}


//____________________________________________________________________________
bool SUSY3L::electronSelection(int elIdx){
    /*
        selection of electrons
        parameters: elIdx
        return: true (if the electron is accepted as an electron), false (else)
    */
    
    //count electron candidates
    counter("ElectronDenominator", kElId);

    //define cuts for electrons
    float pt_cut = 10.;
    float eta_cut = 2.5;
    //float eta_cut = 1.479;
    float eta_veto_low = 1.4442;
    float eta_veto_high = 1.566;
    float isolation_cut = 0.15;
    float vertex_dz_cut = 0.1;      //in cm
    float vertex_dxy_cut = 0.05;    //in cm
    float sip3d_cut = 4;
    float deltaR = 0.1;
    bool isolated = false;
    
    //multiIso working points
    int kLoose = 0;
    int kMedium = 1;
    int kTight = 2;
    int kVeryTight = 3;
    int kHyperTight = 4;
 
    //apply the cuts
    //makeCut(variable to cut on, cut value, direction of acception, name, 2nd cut value, counter)
    if(!makeCut<float>( _vc->get("LepGood_pt", elIdx) , pt_cut, ">"  , "pt selection"    , 0    , kElId)) return false;
    if(!makeCut<float>( std::abs(_vc->get("LepGood_eta", elIdx)), eta_cut  , "<"  , "eta selection"   , 0    , kElId)) return false;
    //removed after RA7 sync round 2
    //if(!makeCut<float>( std::abs(_vc->get("LepGood_eta", elIdx)), eta_veto_low, "[!]", "eta selection veto"   , eta_veto_high, kElId)) return false;
    //removed after RA7 sync round 2
    //if(!makeCut<int>( _vc->get("LepGood_eleCutIdCSA14_50ns_v1", elIdx) , 3     , ">=" , "POG CB WP-M Id " , 0    , kElId)) return false;
    //mva based electron ID
    bool elTightMvaID = electronMvaCut(elIdx, 1);
    if(!makeCut( elTightMvaID, "electron tight mva wp", "=", kElId)) return false;
    //3 variable isolation criteria: miniIso < A and (pt ratio > B or pt rel > C)
    int wp = kMedium;
    isolated = multiIsolation(elIdx, _multiIsoWP[wp][0],  _multiIsoWP[wp][1], _multiIsoWP[wp][2]);
    if(!makeCut( isolated, "initial multiIso selection", "=", kElId)) return false;
    //replaced by multiIsolation
    //if(!makeCut<float>( _vc->get("LepGood_relIso03", elIdx) , isolation_cut   , "<"  , "isolation "      , 0    , kElId)) return false;
    if(!makeCut<float>( std::abs(_vc->get("LepGood_dz", elIdx)), vertex_dz_cut   , "<"  , "dz selection"    , 0    , kElId)) return false;
    if(!makeCut<float>( std::abs(_vc->get("LepGood_dxy", elIdx)), vertex_dxy_cut  , "<"  , "dxy selection"   , 0    , kElId)) return false;
    if(!makeCut<float>( std::abs(_vc->get("LepGood_sip3d", elIdx)), sip3d_cut  , "<"  , "sip3d selection"   , 0    , kElId)) return false;
    //removed after RA7 sync round 2
    //if(!makeCut<int>( _vc->get("LepGood_tightCharge", elIdx) , 1     , ">"  , "charge selection", 0    , kElId)) return false;
    //boolian variable if electron comes from gamma conversion or not (true if not from conversion)
    bool not_conv = (_vc->get("LepGood_convVeto", elIdx)>0 && _vc->get("LepGood_lostHits", elIdx)==0);
    if(!makeCut( not_conv, "conversion rejection", "=", kElId)) return false;
    
    //removed after RA7 sync round 2
    //reject electrons which are within a cone of delta R around a muon candidate (potentially final state radiation, bremsstrahlung)
    bool muMatch = false;
    for(int im=0; im<_nMus; ++im){
        float dr = KineUtils::dR( _mus[im]->eta(), _vc->get("LepGood_eta", elIdx), _mus[im]->phi(), _vc->get("LepGood_phi", elIdx));
        //_deltaR = dr;
        //fill("deltaR_elmu" , _deltaR        , _weight);
        if(dr<deltaR){
            muMatch = true;
            break;
        }
    }
    //enable to clean on tight objects
    //if(!makeCut( !muMatch, "dR selection (mu)", "=", kElId) ) return false;
    
       
    return true;
}


//____________________________________________________________________________
bool SUSY3L::muonSelection(int muIdx){
    /*
        selection of muons
        parameters: muIdx
        return: true (if the muon is accepted as a muon), false (else)
    */
    
    //count muon candidates
    counter("MuonDenominator", kMuId);

    //define cut values
    float pt_cut = 10.;
    float eta_cut = 2.4;
    float isolation_cut = 0.15;
    float vertex_dz_cut = 0.1;
    float vertex_dxy_cut = 0.05;
    float sip3d_cut = 4;
    bool isolated = false;
   
    //multiIso working points
    int kLoose = 0;
    int kMedium = 1;
    int kTight = 2;
    int kVeryTight = 3;
    int kHyperTight = 4;

    //apply the cuts
    if(!makeCut<float>( _vc->get("LepGood_pt", muIdx), pt_cut, ">", "pt selection"    , 0, kMuId)) return false;
    if(!makeCut<float>( std::abs( _vc->get("LepGood_eta", muIdx)), eta_cut, "<", "eta selection", 0, kMuId)) return false;
    //3 variable isolation criteria: miniIso < A and (pt ratio > B or pt rel > C)
    int wp = kLoose;
    isolated = multiIsolation(muIdx, _multiIsoWP[wp][0],  _multiIsoWP[wp][1], _multiIsoWP[wp][2]);
    if(!makeCut( isolated, "initial multiIso selection", "=", kMuId)) return false;
    //replaced by multiIsolation
    //if(!makeCut<float>( _vc->get("LepGood_relIso03", muIdx) , isolation_cut   , "<", "isolation "      , 0, kMuId)) return false;
    //removed after RA7 sync round 2
    //if(!makeCut<int>( _vc->get("LepGood_tightId", muIdx) , 1     , "=", "POG Tight Id "   , 0, kMuId)) return false;
    //mva based muon id, medium working point
    if(!makeCut<float>( _vc->get("LepGood_mediumMuonId", muIdx) , 1  , "=", "mva medium muon id", 0, kMuId)) return false;
    if(!makeCut<float>(std::abs(_vc->get("LepGood_dz", muIdx)), vertex_dz_cut   , "<", "dz selection"    , 0, kMuId)) return false;
    if(!makeCut<float>(std::abs(_vc->get("LepGood_dxy", muIdx)), vertex_dxy_cut , "<", "dxy selection"   , 0, kMuId)) return false;
    if(!makeCut<float>( std::abs(_vc->get("LepGood_sip3d", muIdx)), sip3d_cut  , "<"  , "sip3d selection"   , 0    , kMuId)) return false;
   
 
    return true;
}


//____________________________________________________________________________
bool SUSY3L::tauSelection(int tauIdx){
    /*
        selection of taus
        parameters: tauIdx
        return: true (if the lepton is identified as (hadronic) tau), false (else)
    */
   
    //count tau candidates
    counter("TauDenominator", kTauId);

    //define cuts for electrons
    float pt_cut = 20.;
    float eta_cut = 2.3;
    float deltaR = 0.3;
    
    //apply the cuts
    if(!makeCut<float>( _vc->get("TauGood_pt", tauIdx) , pt_cut, ">"  , "pt selection"    , 0    , kTauId)) return false;
    if(!makeCut<float>( std::abs(_vc->get("TauGood_eta", tauIdx)), eta_cut  , "<"  , "eta selection"   , 0    , kTauId)) return false;
    //removed after sync
    //if(!makeCut<int>( _vc->get("TauGood_idAntiMu", tauIdx) , 2     , "=" , "anti muon" , 0    , kTauId)) return false;
    //if(!makeCut<int>( _vc->get("TauGood_idAntiE", tauIdx) , 4     , ">=" , "anti electron" , 0    , kTauId)) return false;
    //if(!makeCut<int>( _vc->get("TauGood_idDecayMode", tauIdx) , 1     , "=" , "decay mode" , 0    , kTauId)) return false;
    //if(!makeCut<int>( _vc->get("TauGood_isoCI3hit", tauIdx) , 1     , ">=" , "ci3hit" , 0    , kTauId)) return false;
    
    //remove taus which are within a cone of deltaR around selected electrons or muons
    //loop over all electron candidates
    bool lepMatch = false;
    for(int ie=0; ie<_nEls; ++ie){
        //calculate delta R, input eta1, eta2, phi1, phi2
        float dr = KineUtils::dR( _els[ie]->eta(), _vc->get("TauGood_eta", tauIdx), _els[ie]->phi(), _vc->get("TauGood_phi", tauIdx));
        if(dr < deltaR){
            lepMatch = true; 
            break;
        }
    }
    //loop over all muon candidates
    for(int im=0; im<_nMus; ++im){
        //calculate delta R, input eta1, eta2, phi1, phi2
        float dr = KineUtils::dR( _mus[im]->eta(), _vc->get("TauGood_eta", tauIdx), _mus[im]->phi(), _vc->get("TauGood_phi", tauIdx));
        if(dr < deltaR) {
            lepMatch = true; 
            break;
        }
    }
    //enable to clean on tight objects
    //if(!makeCut(!lepMatch,  "lepton cleaning", "=", kTauId) ) return false;
    return true;
}


//____________________________________________________________________________
bool SUSY3L::goodJetSelection(int jetIdx){
    /*
        selection of jets
        parameters: jetIdx
        return: true (if the jet is good), false (else)
    */
    
    counter("JetDenominator", kJetId);

    //define cut values
    float pt_cut = 30.;
    float eta_cut = 2.4;
    float deltaR = 0.4;

    if(!makeCut<float>(_vc->get("Jet_pt", jetIdx)       , pt_cut, ">", "pt selection" , 0, kJetId) ) return false;
    if(!makeCut<float>(std::abs(_vc->get("Jet_eta", jetIdx)),  eta_cut, "<", "eta selection", 0, kJetId) ) return false;
    if(!makeCut<float>(_vc->get("Jet_id", jetIdx),  1, ">=", "jet id", 0, kJetId) ) return false;

    //exclude jets which are within a cone of deltaR around lepton candidates or taus
    //loop over all electron candidates
    bool lepMatch = false;
    for(int ie=0; ie<_nEls; ++ie){
        //calculate delta R, input eta1, eta2, phi1, phi2
        float dr = KineUtils::dR( _els[ie]->eta(), _vc->get("Jet_eta", jetIdx), _els[ie]->phi(), _vc->get("Jet_phi", jetIdx));
        if(dr < deltaR){
            lepMatch = true; 
            break;
        }
    }

    //loop over all muon candidates
    for(int im=0; im<_nMus; ++im){
        //calculate delta R, input eta1, eta2, phi1, phi2
        float dr = KineUtils::dR( _mus[im]->eta(), _vc->get("Jet_eta", jetIdx), _mus[im]->phi(), _vc->get("Jet_phi", jetIdx));
        if(dr < deltaR) {
            lepMatch = true; 
            break;
        }
    }
  
    //loop over all tau candidates
    for(int it=0; it<_nTaus; ++it){
        //calculate delta R, input eta1, eta2, phi1, phi2
        float dr = KineUtils::dR( _taus[it]->eta(), _vc->get("Jet_eta", jetIdx), _taus[it]->phi(), _vc->get("Jet_phi", jetIdx));
        if(dr < deltaR) {
            lepMatch = true; 
            break;
        }
    }
    //enable to clean on tight objects
    //if(!makeCut(!lepMatch,  "lepton cleaning", "=", kJetId) ) return false;
    
    return true;
}



//____________________________________________________________________________
bool SUSY3L::bJetSelection(int jetIdx){
    /*
        does the selection of  b-jets
        parameters: jetIdx
        return: true (if the jet is a b-jet), false (else)
    */
    
    counter("BJetDenominator", kBJetId);

    float btagCSV_cut = 0.814;

    //b-jet needs to fulfill criteria for jets
    if(!makeCut(goodJetSelection(jetIdx), "jet Id", "=", kBJetId) ) return false;
    //cut on b-tagger parameter
    if(!makeCut<float>(_vc->get("Jet_btagCSV", jetIdx), btagCSV_cut, ">", "csv btag selection", 0, kBJetId) ) return false;

    return true;

}



/*******************************************************************************
* ******************************************************************************
* ** KINEMATIC REGION DEFINITIONS                                             **
* ******************************************************************************
* *****************************************************************************/

//____________________________________________________________________________
void SUSY3L::setMultiIsoWP(){
    /*
        sets the cuts multiiso working point
        parameters: none
        return: none
    */
 
    //multiIso working points
    _multiIsoWP[0][0]=0.25;  _multiIsoWP[0][1]=0.75;  _multiIsoWP[0][2]=4.7; //loose
    _multiIsoWP[1][0]=0.21;  _multiIsoWP[1][1]=0.80;  _multiIsoWP[1][2]=6.9;//medium
    _multiIsoWP[2][0]=0.13;  _multiIsoWP[2][1]=0.81;  _multiIsoWP[2][2]=7.2; //tight
    _multiIsoWP[3][0]=0.088; _multiIsoWP[3][1]=0.84; _multiIsoWP[3][2]=7.2; //very tight
    _multiIsoWP[4][0]=0;     _multiIsoWP[4][1]=0; _multiIsoWP[4][2]=0; //hyper tight

}


//____________________________________________________________________________
void SUSY3L::setBaselineRegion(){
    /*
        sets the cuts of the baseline region (_BR)
        parameters: none
        return: none
    */

    if(_BR == "BR0"){
        setCut("LepMultiplicity"   ,    3, ">="  )  ;     //number of isolated leptons
        _pt_cut_hardest_legs          = 20          ;     //harsher pT requirement for at least _nHardestLeptons (below)
        _nHardestLeptons              = 1           ;     //number of leptons which need to fulfill harder pt cut
        _pt_cut_hard_legs              = 0          ;     //harsher pT requirement for at least _nHardestLeptons (below)
        _nHardLeptons                 = 0           ;     //number of leptons which need to fulfill harder pt cut
        _M_T_3rdLep_MET_cut           =  -1         ;     //minimum transverse mass of 3rd lepton and met in On-Z events
        setCut("NJets"              ,    1, ">=" )  ;     //number of jets in event
        setCut("NBJets"             ,    1, ">=" )  ;     //number of b-tagged jets in event
        _ZMassWindow                  = 15.         ;     //width around Z mass to define on- or off-Z events
        setCut("HT"                 ,   60, "<" )  ;     //sum of jet pT's
        setCut("MET"                ,   50, "<" )  ;     //missing transverse energy
        setCut("Mll"                ,   12, ">=" )  ;     //invariant mass of ossf lepton pair
        setCut("MT2"                ,   55, "<" )  ;     //MT2 cut value
    }

}


//____________________________________________________________________________
void SUSY3L::setSignalRegion() {
  
    /*
        sets the cuts of the signal region (_SR)
        parameters: none
        return: none
    */


    // 30 SR as in PAS 013-008

    if(_SR == "SR000") {
        setCut("NBJetsSR", 1, "=" );
        setCut("NJetsSR", 2, "[]", 3 );
        setCut("HTSR", 60, "[[", 200 );
        setCut("METSR", 50, "[[", 100 );
    }
 
    if(_SR == "SR001") {
        setCut("NBJetsSR", 1, "=" );
        setCut("NJetsSR", 2, "[]", 3 );
        setCut("HTSR", 60, "[[", 200 );
        setCut("METSR", 100, "[[", 200 );
    }   
 
    if(_SR == "SR002") {
        setCut("NBJetsSR", 1, "=" );
        setCut("NJetsSR", 2, "[]", 3 );
        setCut("HTSR", 60, "[[", 200 );
        setCut("METSR", 200, ">=" );
    } 

    if(_SR == "SR003") {
        setCut("NBJetsSR", 1, "=" );
        setCut("NJetsSR", 2, "[]", 3 );
        setCut("HTSR", 200, ">=" );
        setCut("METSR", 50, "[[", 100 );
    }
 
    if(_SR == "SR004") {
        setCut("NBJetsSR", 1, "=" );
        setCut("NJetsSR", 2, "[]", 3 );
        setCut("HTSR", 200, ">=" );
        setCut("METSR", 100, "[[", 200 );
    }   
 
    if(_SR == "SR005") {
        setCut("NBJetsSR", 1, "=" );
        setCut("NJetsSR", 2, "[]", 3 );
        setCut("HTSR", 200, ">=" );
        setCut("METSR", 200, ">=" );
    }

    if(_SR == "SR006") {
        setCut("NBJetsSR", 1, "=" );
        setCut("NJetsSR", 4, ">=" );
        setCut("HTSR", 60, "[[", 200 );
        setCut("METSR", 50, "[[", 100 );
    }
 
    if(_SR == "SR007") {
        setCut("NBJetsSR", 1, "=" );
        setCut("NJetsSR", 4, ">=" );
        setCut("HTSR", 60, "[[", 200 );
        setCut("METSR", 100, "[[", 200 );
    }   
 
    if(_SR == "SR008") {
        setCut("NBJetsSR", 1, "=" );
        setCut("NJetsSR", 4, ">=" );
        setCut("HTSR", 60, "[[", 200 );
        setCut("METSR", 200, ">=" );
    } 

    if(_SR == "SR009") {
        setCut("NBJetsSR", 1, "=" );
        setCut("NJetsSR", 4, ">=" );
        setCut("HTSR", 200, ">=" );
        setCut("METSR", 50, "[[", 100 );
    }
 
    if(_SR == "SR010") {
        setCut("NBJetsSR", 1, "=" );
        setCut("NJetsSR", 4, ">=" );
        setCut("HTSR", 200, ">=" );
        setCut("METSR", 100, "[[", 200 );
    }   
 
    if(_SR == "SR011") {
        setCut("NBJetsSR", 1, "=" );
        setCut("NJetsSR", 4, ">=" );
        setCut("HTSR", 200, ">=" );
        setCut("METSR", 200, ">=" );
    }

    if(_SR == "SR012") {
        setCut("NBJetsSR", 2, "=" );
        setCut("NJetsSR", 2, "[]", 3 );
        setCut("HTSR", 60, "[[", 200 );
        setCut("METSR", 50, "[[", 100 );
    }
 
    if(_SR == "SR013") {
        setCut("NBJetsSR", 2, "=" );
        setCut("NJetsSR", 2, "[]", 3 );
        setCut("HTSR", 60, "[[", 200 );
        setCut("METSR", 100, "[[", 200 );
    }   
 
    if(_SR == "SR014") {
        setCut("NBJetsSR", 2, "=" );
        setCut("NJetsSR", 2, "[]", 3 );
        setCut("HTSR", 60, "[[", 200 );
        setCut("METSR", 200, ">=" );
    } 

    if(_SR == "SR015") {
        setCut("NBJetsSR", 2, "=" );
        setCut("NJetsSR", 2, "[]", 3 );
        setCut("HTSR", 200, ">=" );
        setCut("METSR", 50, "[[", 100 );
    }
 
    if(_SR == "SR016") {
        setCut("NBJetsSR", 2, "=" );
        setCut("NJetsSR", 2, "[]", 3 );
        setCut("HTSR", 200, ">=" );
        setCut("METSR", 100, "[[", 200 );
    }   
 
    if(_SR == "SR017") {
        setCut("NBJetsSR", 2, "=" );
        setCut("NJetsSR", 2, "[]", 3 );
        setCut("HTSR", 200, ">=" );
        setCut("METSR", 200, ">=" );
    }

    if(_SR == "SR018") {
        setCut("NBJetsSR", 2, "=" );
        setCut("NJetsSR", 4, ">=" );
        setCut("HTSR", 60, "[[", 200 );
        setCut("METSR", 50, "[[", 100 );
    }
 
    if(_SR == "SR019") {
        setCut("NBJetsSR", 2, "=" );
        setCut("NJetsSR", 4, ">=" );
        setCut("HTSR", 60, "[[", 200 );
        setCut("METSR", 100, "[[", 200 );
    }   
 
    if(_SR == "SR020") {
        setCut("NBJetsSR", 2, "=" );
        setCut("NJetsSR", 4, ">=" );
        setCut("HTSR", 60, "[[", 200 );
        setCut("METSR", 200, ">=" );
    } 

    if(_SR == "SR021") {
        setCut("NBJetsSR", 2, "=" );
        setCut("NJetsSR", 4, ">=" );
        setCut("HTSR", 200, ">=" );
        setCut("METSR", 50, "[[", 100 );
    }
 
    if(_SR == "SR022") {
        setCut("NBJetsSR", 2, "=" );
        setCut("NJetsSR", 4, ">=" );
        setCut("HTSR", 200, ">=" );
        setCut("METSR", 100, "[[", 200 );
    }   
 
    if(_SR == "SR023") {
        setCut("NBJetsSR", 2, "=" );
        setCut("NJetsSR", 4, ">=" );
        setCut("HTSR", 200, ">=" );
        setCut("METSR", 200, ">=" );
    }

    if(_SR == "SR024") {
        setCut("NBJetsSR", 3, ">=" );
        setCut("NJetsSR", 2, ">=" );
        setCut("HTSR", 60, "[[", 200 );
        setCut("METSR", 50, "[[", 100 );
    }
 
    if(_SR == "SR025") {
        setCut("NBJetsSR", 3, ">=" );
        setCut("NJetsSR", 2, ">=" );
        setCut("HTSR", 60, "[[", 200 );
        setCut("METSR", 100, "[[", 200 );
    }   
 
    if(_SR == "SR026") {
        setCut("NBJetsSR", 3, ">=" );
        setCut("NJetsSR", 2, ">=" );
        setCut("HTSR", 60, "[[", 200 );
        setCut("METSR", 200, ">=" );
    } 

    if(_SR == "SR027") {
        setCut("NBJetsSR", 3, ">=" );
        setCut("NJetsSR", 2, ">=" );
        setCut("HTSR", 200, ">=" );
        setCut("METSR", 50, "[[", 100 );
    }
 
    if(_SR == "SR028") {
        setCut("NBJetsSR", 3, ">=" );
        setCut("NJetsSR", 2, ">=" );
        setCut("HTSR", 200, ">=" );
        setCut("METSR", 100, "[[", 200 );
    }   
 
    if(_SR == "SR029") {
        setCut("NBJetsSR", 3, ">=" );
        setCut("NJetsSR", 2, ">=" );
        setCut("HTSR", 200, ">=" );
        setCut("METSR", 200, ">=" );
    }

}


//____________________________________________________________________________
//void SUSY3L::setSignalRegion() {
/*
if(_SR == "SR000") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR001") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR002") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR003") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR004") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR005") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR006") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR007") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR008") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR009") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR010") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR011") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR012") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR013") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR014") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR015") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR016") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR017") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR018") {
   setCut("NBJetsSR", 1, "[[", 3 );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR019") {
   setCut("NBJetsSR", 1, "[[", 3 );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR020") {
   setCut("NBJetsSR", 1, "[[", 3 );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR021") {
   setCut("NBJetsSR", 1, "[[", 3 );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR022") {
   setCut("NBJetsSR", 1, "[[", 3 );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR023") {
   setCut("NBJetsSR", 1, "[[", 3 );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR024") {
   setCut("NBJetsSR", 1, "[[", 3 );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR025") {
   setCut("NBJetsSR", 1, "[[", 3 );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR026") {
   setCut("NBJetsSR", 1, "[[", 3 );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR027") {
   setCut("NBJetsSR", 1, "[[", 3 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR028") {
   setCut("NBJetsSR", 1, "[[", 3 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR029") {
   setCut("NBJetsSR", 1, "[[", 3 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR030") {
   setCut("NBJetsSR", 1, "[[", 3 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR031") {
   setCut("NBJetsSR", 1, "[[", 3 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR032") {
   setCut("NBJetsSR", 1, "[[", 3 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR033") {
   setCut("NBJetsSR", 1, "[[", 3 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR034") {
   setCut("NBJetsSR", 1, "[[", 3 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR035") {
   setCut("NBJetsSR", 1, "[[", 3 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR036") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR037") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR038") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR039") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR040") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR041") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR042") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR043") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR044") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 2, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR045") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR046") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR047") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR048") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR049") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR050") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR051") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR052") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR053") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 300, ">=" );
}


}
*/


//____________________________________________________________________________
//void SUSY3L::setSignalRegion() {
/*
if(_SR == "SR000") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR001") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR002") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR003") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR004") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR005") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR006") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR007") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR008") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR009") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR010") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR011") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR012") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR013") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR014") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR015") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR016") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR017") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR018") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR019") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR020") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR021") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR022") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR023") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR024") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR025") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR026") {
   setCut("NBJetsSR", 0, "[[", 1 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR027") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR028") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR029") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR030") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR031") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR032") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR033") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR034") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR035") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR036") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR037") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR038") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR039") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR040") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR041") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR042") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR043") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR044") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR045") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR046") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR047") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR048") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR049") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR050") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR051") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR052") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR053") {
   setCut("NBJetsSR", 1, "[[", 2 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR054") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR055") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR056") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR057") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR058") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR059") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR060") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR061") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR062") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR063") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR064") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR065") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR066") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR067") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR068") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR069") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR070") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR071") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR072") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR073") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR074") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR075") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR076") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR077") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR078") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR079") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR080") {
   setCut("NBJetsSR", 2, "[[", 3 );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR081") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR082") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR083") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR084") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR085") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR086") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR087") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR088") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR089") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 2, "[[", 4 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR090") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR091") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR092") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR093") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR094") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR095") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR096") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR097") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR098") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 4, "[[", 5 );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR099") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR100") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR101") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 60, "[[", 400 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR102") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR103") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR104") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 400, "[[", 600 );
   setCut("METSR", 300, ">=" );
}

if(_SR == "SR105") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 50, "[[", 150 );
}

if(_SR == "SR106") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 150, "[[", 300 );
}

if(_SR == "SR107") {
   setCut("NBJetsSR", 3, ">=" );
   setCut("NJetsSR", 5, ">=" );
   setCut("HTSR", 600, ">=" );
   setCut("METSR", 300, ">=" );
}




}
*/

//____________________________________________________________________________
void SUSY3L::setCut(std::string var, float valCut, std::string cType, float upValCut) {
    /*
        sets the parameters (valCut, cType, upValCut) for a specific cut on a variable (var)
        parameters: var, valCut (the cut value), cType (the cut type), upValCut (the upper value
        in case one cuts the variable in a range)
        return: none
    */

    //baseline region
    if(var == "LepMultiplicity") {
        _valCutLepMultiplicityBR   = valCut;
        _cTypeLepMultiplicityBR    = cType;
        _upValCutLepMultiplicityBR = upValCut;
    }
    else if(var == "NJets") {
        _valCutNJetsBR   = valCut;
        _cTypeNJetsBR    = cType;
        _upValCutNJetsBR = upValCut;
    }
    else if(var == "NBJets") {
        _valCutNBJetsBR   = valCut;
        _cTypeNBJetsBR    = cType;
        _upValCutNBJetsBR = upValCut;
    }
    else if(var == "HT") {
        _valCutHTBR   = valCut;
        _cTypeHTBR    = cType;
        _upValCutHTBR = upValCut;
    }
    else if(var == "MET") {
        _valCutMETBR   = valCut;
        _cTypeMETBR    = cType;
        _upValCutMETBR = upValCut;
    }
    else if(var == "Mll") {
        _valCutMllBR   = valCut;
        _cTypeMllBR    = cType;
        _upValCutMllBR = upValCut;
    }
    else if(var == "MT2") {
        _valCutMT2BR   = valCut;
        _cTypeMT2BR    = cType;
        _upValCutMT2BR = upValCut;
    }


    // signal region

    if(var == "HTSR") {
        _valCutHTSR   = valCut;
        _cTypeHTSR    = cType;
        _upValCutHTSR = upValCut;
    }

    else if(var == "METSR") {
        _valCutMETSR   = valCut;
        _cTypeMETSR    = cType;
        _upValCutMETSR = upValCut;
    }

    else if(var == "NJetsSR") {
        _valCutNJetsSR   = valCut;
        _cTypeNJetsSR    = cType;
        _upValCutNJetsSR = upValCut;
    }

    else if(var == "NBJetsSR") {
        _valCutNBJetsSR   = valCut;
        _cTypeNBJetsSR    = cType;
        _upValCutNBJetsSR = upValCut;
    }

}



/*******************************************************************************
* ******************************************************************************
* ** EVENT SELECTIONS                                                         **
* ******************************************************************************
* *****************************************************************************/

//____________________________________________________________________________
bool SUSY3L::baseSelection(){
    /*
        implements the basic selection that is fundamental for both the baseline 
        and the signal region selections
        parameters: none
        return: true (if event passes selection), false (else)
    */
   
    //select events with certain lepton multiplicity of all flavor combinations
    if(!makeCut<int>( _nMus + _nEls + _nTaus, _valCutLepMultiplicityBR, _cTypeLepMultiplicityBR, "lepton multiplicity", _upValCutLepMultiplicityBR ) ) return false;
    //if(!makeCut<int>( _nMus , 1, "=" , "muon multiplicity", 0 ) ) return false;
    //if(!makeCut<int>( _nTaus, 1, ">=" , "tau multiplicity", 0 ) ) return false;
    
    //apply additional pt cuts on leptons
    bool has_hard_legs = hardLegSelection();
    if(!makeCut( has_hard_legs , "hard leg selection", "=") ) return false;

    //require at least two of the leptons to be tighter in multiiso
    //bool has_two_tighter_leptons = checkMultiIso();
    //if(!makeCut( has_two_tighter_leptons , "multiIso tightening", "=") ) return false;

    //require minimum number of jets
    //if(!makeCut<int>( _nJets, _valCutNJetsBR, _cTypeNJetsBR, "jet multiplicity", _upValCutNJetsBR) ) return false;

    //require minimum number of b-tagged jets
    //if(!makeCut<int>( _nBJets, _valCutNBJetsBR, _cTypeNBJetsBR, "b-jet multiplicity", _upValCutNBJetsBR) ) return false;
    
    //require minimum hadronic activity (sum of jet pT's)
    if(!makeCut<float>( _HT, _valCutHTBR, _cTypeHTBR, "hadronic activity", _upValCutHTBR) ) return false;

    //require minimum missing transvers energy (actually missing momentum)
    //if(!makeCut<float>( _met->pt(), _valCutMETBR, _cTypeMETBR, "missing transverse energy", _upValCutMETBR) ) return false;

    //find smallest invariant mass of ossf pair and reject event if this is below a cut value
    _mll = lowestOssfMll();
    //if(!makeCut<int>( _mll, _valCutMllBR, _cTypeMllBR, "low invariant mass", _upValCutMllBR) ) return false;
    fill("lowMll" , _mll        , _weight);
 
    //select on or off-Z events according to specification in config file
    bool is_reconstructed_Z = ZEventSelectionLoop();
    if(_pairmass == "off"){
        if(!makeCut( !is_reconstructed_Z, "mll selection", "=") ) return false;
    }
    else if(_pairmass == "on"){
        if(!makeCut( is_reconstructed_Z, "mll selection", "=") ) return false;
    }
    
    //fill plots 
    if(is_reconstructed_Z){
        fill("Zmass" , _Z->mass()      , _weight);
        fill("Zpt"   , _Z->pt()        , _weight);
    }
    
    fill("el_multiplicity" , _nEls , _weight);
    fill("mu_multiplicity" , _nMus , _weight);
    fill("tau_multiplicity" , _nTaus , _weight);
    fill("lep_multiplicity" , _nEls + _nMus + _nTaus , _weight);

    //sort leptons by pt and fill pt plots
    sortSelectedLeps();
    fill("pt_1st_lepton" , _leps[0]->pt() , _weight);
    fill("pt_2nd_lepton" , _leps[1]->pt() , _weight);
    if(_nMus + _nEls + _nTaus > 2){
        fill("pt_3rd_lepton" , _leps[2]->pt() , _weight);
    }
    
    //calculate MT2 and fill plot
    if(_nMus + _nEls + _nTaus == 3){
        _MT2 = getMT2();
        //cut on MT2
        //if(!makeCut<float>( _MT2, _valCutMT2BR, _cTypeMT2BR, "mt2", _upValCutMT2BR) ) return false;
        fill("MT2" , _MT2        , _weight);
    }

    for(int mu=0;mu<_nMus;++mu){    
        fill("muon_SIP3d"   , std::abs(_vc->get("LepGood_sip3d" , _muIdx[mu]))                  , _weight);
        fill("muon_dxy"     , std::abs(_vc->get("LepGood_dxy"   , _muIdx[mu])*10000)            , _weight);
        fill("muon_dz"      , std::abs(_vc->get("LepGood_dz"    , _muIdx[mu])*10000)            , _weight);
        fill("muon_JetPtRatio" , std::abs(_vc->get("LepGood_jetPtRatio_LepAwareJECv2", _muIdx[mu]))        , _weight);
        fill("muon_JetPtRel" , std::abs(_vc->get("LepGood_jetPtRelv2" , _muIdx[mu]))            , _weight);
        fill("muon_miniRelIso" , std::abs(_vc->get("LepGood_miniRelIso" , _muIdx[mu]))          , _weight);
    }

    for(int el=0;el<_nEls;++el){    
        fill("el_SIP3d"   , std::abs(_vc->get("LepGood_sip3d" , _elIdx[el]))        , _weight);
        fill("el_dxy"     , std::abs(_vc->get("LepGood_dxy"   , _elIdx[el])*10000)        , _weight);
        fill("el_dz"      , std::abs(_vc->get("LepGood_dz"    , _elIdx[el])*10000)        , _weight);
        fill("el_JetPtRatio" , std::abs(_vc->get("LepGood_jetPtRatio_LepAwareJECv2" , _elIdx[el]))        , _weight);
        fill("el_JetPtRel" , std::abs(_vc->get("LepGood_jetPtRelv2" , _elIdx[el]))        , _weight);
        fill("el_miniRelIso" , std::abs(_vc->get("LepGood_miniRelIso" , _elIdx[el]))        , _weight);
    }

    return true;
}

//____________________________________________________________________________
void SUSY3L::wzCRSelection(){
    /*
        selects events for the WZ control region to estimate the WZ background from data
        parameters: none
        return: none
    */

    //change to WZCR workflow
    setWorkflow(kWZCR);
    if(!makeCut<float>( _HT, 60, ">", "hadronic activity", 0) ) return;
    fillEventPlots();
    setWorkflow(kGlobal);
}


//____________________________________________________________________________
bool SUSY3L::checkMultiIso(){
    /*
        Checks if at least two of the selected leptons (ultra-loose in multiIso) 
        are tigther in multiIso, where tighter can be different wp for muons and 
        electrons  
        return: true (if the event has 2 leptons which are tighter in multiIso)
        , false (else)
    */

    //number of leptons fulfilling the tightened multiIso wp
    int tighter_leptons = 0;

    //multiIso working points
    int kLoose = 0;
    int kMedium = 1;
    int kTight = 2;
    int kVeryTight = 3;
    int kHyperTight = 4;
    int wp = -1;
    
    //check electrons
    //multiIso working point
    wp = kLoose;
    //_elIdx is vector of electron positions in LepGood vector
    for(int ie=0; ie<_nEls; ++ie){
        if(multiIsolation(_elIdx[ie], _multiIsoWP[wp][0],  _multiIsoWP[wp][1], _multiIsoWP[wp][2])){
            tighter_leptons += 1;
        }
    }

    //check muons
    //multiIso working point
    wp = kLoose;
    //_muIdx is vector of electron positions in LepGood vector
    for(int im=0; im<_nMus; ++im){
        if(multiIsolation(_muIdx[im], _multiIsoWP[wp][0],  _multiIsoWP[wp][1], _multiIsoWP[wp][2])){
            tighter_leptons += 1;
        }
    }

    if(tighter_leptons>=2){
        return true;
    }

    return false;
}


//____________________________________________________________________________
bool SUSY3L::hardLegSelection(){
    /*
        Checks if the selected event has at least _nHardestLeptons leptons
        (muon or electron) fullfilling a harsher pT cut and _nHardLeptons leptons fulfilling another lower cut
        return: true (if the event has _nHardestLeptons and _nHardLeptons with higher pT), false (else)
    */
    
    int nHardestLepCount = 0;
    int nHardLepCount = 0;

    //check how many electrons fullfils hard pt cut
    for(int ie=0; ie<_nEls; ++ie){
        if(_els[ie]->pt()>_pt_cut_hard_legs){
            nHardLepCount += 1;
            if(_els[ie]->pt()>_pt_cut_hardest_legs){
                nHardestLepCount += 1;
            } 
        }
    }

    //check how many muons fullfils hard pt cut
    for(int im=0; im<_nMus; ++im){
        if(_mus[im]->pt()>_pt_cut_hard_legs){
            nHardLepCount += 1;
            if(_mus[im]->pt()>_pt_cut_hardest_legs){
                nHardestLepCount += 1;
            }
        }
    }

    //check how many taus fullfils hard pt cut
    for(int it=0; it<_nTaus; ++it){
        if(_taus[it]->pt()>_pt_cut_hard_legs){
            nHardLepCount += 1;
            if(_taus[it]->pt()>_pt_cut_hardest_legs){
                nHardestLepCount += 1;
            }
        }
    }

    //correct number of leptons of hardLeg requirement with required number of leptons with hardestLeg
    nHardLepCount -= _nHardLeptons;

    if(nHardestLepCount >= _nHardestLeptons && nHardLepCount >= _nHardLeptons) return true;

    return false;
}

//____________________________________________________________________________
float SUSY3L::lowestOssfMll(bool ossf){
    /*
        Checks if event has an ossf lepton pair and computes the lowest invariant mass of all ossf pairs
        parameters: ossf, true on default, if false all combinations of leptons are checked for the lowest invariant mass
        return: smallest mll of ossf lepton pair if a pair is found, 999 if no pair is found
    */

    bool pair_found = false;
    float mll = 99999;

   
    if(ossf == false){
        //mll of muon with highest pt tau
        float taupt = 0;
        for(int i=0; i < _nTaus; i++) {
            if(_taus[i]->pt()>taupt){
                mll = Candidate::create(_taus[i], _mus[0])->mass();
                taupt = _taus[i]->pt();
            }
        }
        pair_found = true;
    }

    if(ossf == true){
        //loop over all possible combination of two electrons
        for(int ie1=0; ie1 < _nEls; ie1++) {
            for(int ie2 = ie1; ie2 < _nEls; ie2++) {
                //continue if not an ossf pair
                if( _els[ie1]->pdgId() != - _els[ie2]->pdgId()) continue;
                //save mll if it is the smallest of all mll found so far
                float mll_tmp = Candidate::create(_els[ie1], _els[ie2])->mass();
                pair_found = true;
                if(mll_tmp < mll){
                    mll = mll_tmp;
                }
            }
        }   

        //loop over all possible combination of two muons
        for(int im1=0; im1 < _nMus; im1++) {
            for(int im2 = im1; im2 < _nMus; im2++) {
                //continue if not an ossf pair
                if( _mus[im1]->pdgId() != - _mus[im2]->pdgId()) continue;
                //save mll if it is the smallest of all mll found so far
                float mll_tmp = Candidate::create(_mus[im1], _mus[im2])->mass();
                pair_found = true;
                if(mll_tmp < mll){
                    mll = mll_tmp;
                }
            }
        }
 
        //loop over all possible combination of two taus
        for(int it1=0; it1 < _nTaus; it1++) {
            for(int it2 = it1; it2 < _nTaus; it2++) {
                //continue if not an ossf pair
                if( _taus[it1]->pdgId() != - _taus[it2]->pdgId()) continue;
                //save mll if it is the smallest of all mll found so far
                float mll_tmp = Candidate::create(_taus[it1], _taus[it2])->mass();
                pair_found = true;
                if(mll_tmp < mll){
                    mll = mll_tmp;
                }
            }
        }
    }
 
    if(pair_found){return mll;}
    else{return 999;}
}


//____________________________________________________________________________
bool SUSY3L::ZEventSelectionLoop(){
    /*
        Checks if there is a same-flavor opposite-charge lepton pair with an invariant 
        mass around the Z mass. The ossf pair with an invariant mass closest to the 
        Z mass is added as Z candidate. Additionally a requirement on the transverse mass
        of any of the other leptons and the met is checked
        return: true (if a Z can be reconstructed from 2 leptons and tranverse mass 
        requirement is fulfilled), false (else)
    */

    //count reconstructed Z bosons
    counter("denominator", conZEvents);

    //Z mass
    float Zmass = 91.1876;
    float diff = 1000000;
    bool Zevent = false;
    float pt_other = 0;
    float phi_other = 0;
    float mt = 0;
    int ie1_save = -1;
    int ie2_save = -1;
    int im1_save = -1;
    int im2_save = -1;
    int it1_save = -1;
    int it2_save = -1;


    bool el_Zcand = false;
    //loop over all possible combination of two electrons
    for(int ie1=0; ie1 < _nEls; ie1++){
        for(int ie2 = ie1; ie2 < _nEls; ie2++) {
            //continue if not an ossf pair
            if( _els[ie1]->pdgId() != - _els[ie2]->pdgId()) continue;
            //create new Z candidate
            Candidate* Ztmp = Candidate::create(_els[ie1], _els[ie2]);
            //keep Z candidate if smallest difference to Z mass
            if((std::abs(Ztmp->mass()-Zmass) < _ZMassWindow) && (std::abs(Ztmp->mass()-Zmass)<diff) ) {
                _Z = Ztmp;
                diff = std::abs(_Z->mass()-Zmass);
                el_Zcand = true;
                ie1_save = ie1;
                ie2_save = ie2;
            }
            else{
                continue;
            }
        }
    }

    bool mu_Zcand = false;
    //loop over all possible combination of two muons
    for(int im1=0; im1 < _nMus; im1++) {
        for(int im2 = im1; im2 < _nMus; im2++) {
            //continue if not an ossf pair
            if( _mus[im1]->pdgId() != - _mus[im2]->pdgId()) continue;
            //create new Z candidate
            Candidate* Ztmp = Candidate::create(_mus[im1], _mus[im2]);
            //keep Z candidate if smallest difference to Z mass
            if((std::abs(Ztmp->mass()-Zmass) < _ZMassWindow) && (std::abs(Ztmp->mass()-Zmass)<diff) ) {
                _Z = Ztmp;
                diff = std::abs(_Z->mass()-Zmass);
                //a better Z candidate formed by muons is found
                el_Zcand = false;
                mu_Zcand = true;
                im1_save = im1;
                im2_save = im2;
            }
            else{
                continue;
            }
        }
    }

    bool tau_Zcand = false;
    //loop over all possible combination of two taus
    for(int it1=0; it1 < _nTaus; it1++) {
        for(int it2 = it1; it2 < _nTaus; it2++) {
            //continue if not an ossf pair
            if( _taus[it1]->pdgId() != - _taus[it2]->pdgId()) continue;
            //create new Z candidate
            Candidate* Ztmp = Candidate::create(_taus[it1], _taus[it2]);
            //keep Z candidate if smallest difference to Z mass
            if((std::abs(Ztmp->mass()-Zmass) < _ZMassWindow) && (std::abs(Ztmp->mass()-Zmass)<diff) ) {
                _Z = Ztmp;
                diff = std::abs(_Z->mass()-Zmass);
                //a better Z candidate formed by taus is found
                el_Zcand = false;
                mu_Zcand = false;
                tau_Zcand = true;
                it1_save = it1;
                it2_save = it2;
            }
            else{
                continue;
            }
        }
    }

    //for 2 lepton selection do not check MT requirement with 3rd lepton
    if(_nMus + _nEls + _nTaus == 2){
        if(el_Zcand == true || mu_Zcand == true || tau_Zcand == true){return true;}
        else{return false;}
    }
    else{
        //check MT requirement if there is a Z candidate with electrons
        if(el_Zcand == true){
            //loop other all electrons which are not part of the ossf pair
            for(int ie=0; ie < _nEls; ie++){
                if(ie == ie1_save || ie == ie2_save){
                    continue;
                }
                pt_other = _els[ie]->pt();
                phi_other = _els[ie]->phi();
                fill("3rd_lepton_flavor", _els[ie]->pdgId(), _weight);
                //calculate transverse mass of other lepton and met
                mt = M_T(pt_other, _vc->get("met_pt"), phi_other, _vc->get("met_phi"));
                //accept event if Z candidate exists and mt critirion is fulfilled
                if(mt > _M_T_3rdLep_MET_cut){
                    return true;
                }
                mt = 0.;
                pt_other = 0.;
                phi_other = 0.;
            }
            //loop over all muons
            for(int im=0; im < _nMus; im++){
                pt_other = _mus[im]->pt();
                phi_other = _mus[im]->phi();
                fill("3rd_lepton_flavor", _mus[im]->pdgId(), _weight);
                //calculate transverse mass of other lepton and met
                mt = M_T(pt_other, _vc->get("met_pt"), phi_other, _vc->get("met_phi"));
                //accept event if Z candidate exists and mt critirion is fulfilled
                if(mt > _M_T_3rdLep_MET_cut){
                    fill("MT" , mt        , _weight);
                    return true;
                }
                mt = 0.;
                pt_other = 0.;
                phi_other = 0.;
            }
            //loop over all taus
            for(int it=0; it < _nTaus; it++){
                pt_other = _taus[it]->pt();
                phi_other = _taus[it]->phi();
                fill("3rd_lepton_flavor", _taus[it]->pdgId(), _weight);
                //calculate transverse mass of other lepton and met
                mt = M_T(pt_other, _vc->get("met_pt"), phi_other, _vc->get("met_phi"));
                //accept event if Z candidate exists and mt critirion is fulfilled
                if(mt > _M_T_3rdLep_MET_cut){
                    fill("MT" , mt        , _weight);
                    return true;
                }
                mt = 0.;
                pt_other = 0.;
                phi_other = 0.;
            }
        }
    

        //check MT requirement if there is a Z candidate with electrons
        if(mu_Zcand == true){
            //loop over all muons which are not part of the ossf pair
            for(int im=0; im < _nMus; im++){
                if(im == im1_save || im == im2_save){
                    continue;
                }
                pt_other = _mus[im]->pt();
                phi_other = _mus[im]->phi();
                //calculate transverse mass of other lepton and met
                mt = M_T(pt_other, _vc->get("met_pt"), phi_other, _vc->get("met_phi"));
                //accept event if Z candidate exists and mt critirion is fulfilled
                if(mt > _M_T_3rdLep_MET_cut){
                    fill("MT" , mt        , _weight);
                    return true;
                }
                mt = 0.;
                pt_other = 0.;
                phi_other = 0.;
            }
            //loop over all electrons to check MT requirement
            for(int ie=0; ie < _nEls; ie++){
                pt_other = _els[ie]->pt();
                phi_other = _els[ie]->phi();
                //calculate transverse mass of other lepton and met
                mt = M_T(pt_other, _vc->get("met_pt"), phi_other, _vc->get("met_phi"));
                //accept event if Z candidate exists and mt critirion is fulfilled
                if(mt > _M_T_3rdLep_MET_cut){
                    fill("MT" , mt        , _weight);
                    return true;
                }
                mt = 0.;
                pt_other = 0.;
                phi_other = 0.;
            }
            //loop over all taus
            for(int it=0; it < _nTaus; it++){
                pt_other = _taus[it]->pt();
                phi_other = _taus[it]->phi();
                //calculate transverse mass of other lepton and met
                mt = M_T(pt_other, _vc->get("met_pt"), phi_other, _vc->get("met_phi"));
                //accept event if Z candidate exists and mt critirion is fulfilled
                if(mt > _M_T_3rdLep_MET_cut){
                    fill("MT" , mt        , _weight);
                    return true;
                }
                mt = 0.;
                pt_other = 0.;
                phi_other = 0.;
            }
        }

        //check MT requirement if there is a Z candidate with taus
        if(tau_Zcand == true){
            //loop over all taus which are not part of the ossf pair
            for(int it=0; it < _nTaus; it++){
                if(it == it1_save || it == it2_save){
                    continue;
                }
                pt_other = _taus[it]->pt();
                phi_other = _taus[it]->phi();
                //calculate transverse mass of other lepton and met
                mt = M_T(pt_other, _vc->get("met_pt"), phi_other, _vc->get("met_phi"));
                //accept event if Z candidate exists and mt critirion is fulfilled
                if(mt > _M_T_3rdLep_MET_cut){
                    fill("MT" , mt        , _weight);
                    return true;
                }
                mt = 0.;
                pt_other = 0.;
                phi_other = 0.;
            }
            //loop over all electrons to check MT requirement
            for(int ie=0; ie < _nEls; ie++){
                pt_other = _els[ie]->pt();
                phi_other = _els[ie]->phi();
                //calculate transverse mass of other lepton and met
                mt = M_T(pt_other, _vc->get("met_pt"), phi_other, _vc->get("met_phi"));
                //accept event if Z candidate exists and mt critirion is fulfilled
                if(mt > _M_T_3rdLep_MET_cut){
                    fill("MT" , mt        , _weight);
                    return true;
                }
                mt = 0.;
                pt_other = 0.;
                phi_other = 0.;
            }
            //loop over all muons
            for(int im=0; im < _nMus; im++){
                pt_other = _mus[im]->pt();
                phi_other = _mus[im]->phi();
                //calculate transverse mass of other lepton and met
                mt = M_T(pt_other, _vc->get("met_pt"), phi_other, _vc->get("met_phi"));
                //accept event if Z candidate exists and mt critirion is fulfilled
                if(mt > _M_T_3rdLep_MET_cut){
                    fill("MT" , mt        , _weight);
                    return true;
                }
                mt = 0.;
                pt_other = 0.;
                phi_other = 0.;
            }
        }
    }

    return false;
}


//____________________________________________________________________________
bool SUSY3L::srSelection(){
    /*
        implements the signal region selection provided that the base selection
        already has been applied, i.e. here we just cut on the variables that 
        distinguish the different signal regions
        parameters: none
        return: true (if event passes selection), false (else)
    */

    // cut on the variables distriminating the signal regions
    if(!makeCut<float>( _nBJets     , _valCutNBJetsSR, _cTypeNBJetsSR, "SR bjet multiplicity", _upValCutNBJetsSR) ) return false;
    if(!makeCut<int>( _nJets       , _valCutNJetsSR , _cTypeNJetsSR , "SR jet multiplicity" , _upValCutNJetsSR ) ) return false;
    if(!makeCut<float>( _HT          , _valCutHTSR    , _cTypeHTSR    , "SR HT selection"     , _upValCutHTSR    ) ) return false;
    if(!makeCut<float>( _met->pt()   , _valCutMETSR   , _cTypeMETSR   , "SR MET selection"    , _upValCutMETSR   ) ) return false;

    return true;

}

//____________________________________________________________________________
float SUSY3L::getMT2(){
    /*
        selected the two leptons that should be used for the MT2 calculation
        parameters: none
        return: none
    */
    
    bool allSameSigned = false;
    float ptsum = 0; 
    float ptsum_tmp = 0;
    int il1_save = -1;
    int il2_save = -1;

    if(_nMus+_nEls != 3){
        return 0;
    }
   
    if(((signbit(_leps[0]->pdgId())) == (signbit(_leps[1]->pdgId()))) && ((signbit(_leps[0]->pdgId())) == (signbit(_leps[2]->pdgId())))){
         allSameSigned = true; 
    }
     
    if(allSameSigned){
        for(int il1=0;il1<_nleps;il1++){
            for(int il2=il1+1;il2<_nleps;il2++){
                //calculate sum of pt's
                ptsum_tmp = _leps[il1]->pt() + _leps[il2]->pt();
                //keep lepton pair candidate if it has the highest sum of pt's
                if(ptsum_tmp >= ptsum) {
                    ptsum = _leps[il1]->pt() + _leps[il2]->pt();
                    il1_save = il1;
                    il2_save = il2;
                }
            }   
        }
    }
    //in case not all leptons are of the same sign require os lepton pair 
    else{
        for(int il1=0;il1<_nleps;il1++){
            for(int il2=il1+1;il2<_nleps;il2++){
                //continue if not os
                if((signbit(_leps[il1]->pdgId())) == (signbit(_leps[il2]->pdgId()))){
                    continue;
                }
                //calculate sum of pt's
                ptsum_tmp = _leps[il1]->pt() + _leps[il2]->pt();
                //keep lepton pair candidate if it has the highest sum of pt's
                if(ptsum_tmp >= ptsum) {
                    ptsum = _leps[il1]->pt() + _leps[il2]->pt();
                    il1_save = il1;
                    il2_save = il2;
                }
            }   
        }
    }

    //take the two selected leptons and compute MT2 with them
    _lep1 = _leps[il1_save];
    _lep2 = _leps[il2_save];
              
    return MT2(_lep1, _lep2, _met, 0.0);
}

/*******************************************************************************
* ******************************************************************************
* ** EXECUTING TASKS                                                          **
* ******************************************************************************
* *****************************************************************************/

//____________________________________________________________________________
void SUSY3L::fillEventPlots(){
    /*
        fills the control plots for event quantities
        parameters: none
        return: none
    */

    fill("HT"        , _HT                    , _weight);
    fill("MET"       , _met->pt()             , _weight);
    fill("NBJets"    , _nBJets                , _weight);
    fill("NJets"     , _nJets                 , _weight);

}




//____________________________________________________________________________
float SUSY3L::DeltaPhi(float phi1, float phi2){
    /*
        computes delta phi for two giveb phis taking into account the phi range
        parameters: phi1, phi2
        return: delta phi
    */

        float result = phi1 - phi2;
        while( result >   TMath::Pi() ) result -= TMath::TwoPi();
        while( result <= -TMath::Pi() ) result += TMath::TwoPi();
        
        return TMath::Abs(result);
       
       
}

//____________________________________________________________________________
float SUSY3L::HT(){
    /*
        computes HT for a given list of selected jets
        parameters: jet_label
        return: HT
    */

        float ht = 0;
        for(int i = 0; i < _nJets; ++i){
            ht += _jets[i]->pt();
        }
        return ht;
}

//____________________________________________________________________________
float SUSY3L::M_T(float pt_lepton, float met, float phi_lepton, float phi_met){
    /*
        computes the transverse mass for a lepton and met
        parameters: pt_lepton, met, phi_lepton, phi_met
        return: transverse mass M_T
    */

        float deltaPhi = DeltaPhi(phi_lepton, phi_met);
        float m_t = 0;
        m_t = sqrt(2 * pt_lepton * met * (1 - cos(deltaPhi) ));
        return m_t;
}

//____________________________________________________________________________
bool SUSY3L::electronMvaCut(int idx, int wp){
    /*
        decides whether ot not an electron passes the loose or tight mva wp
        parameters: idx (electron identification number), wp (worling point 0 for loose, 1 for tight)
        return: true (if electron passes the wp), flase (else)
    */

        float _elMvaIdWP[3][2];
        int kLoose = 0;
        int kTight = 1;
        _elMvaIdWP[0][kLoose]=0.35;  _elMvaIdWP[0][kTight]=0.73;
        _elMvaIdWP[1][kLoose]=0.20;  _elMvaIdWP[1][kTight]=0.57;
        _elMvaIdWP[2][kLoose]=-0.52; _elMvaIdWP[2][kTight]=0.05;

        int etaBin=-1;
        if(std::abs(_vc->get("LepGood_eta", idx)) < 0.8){ etaBin=0 ;}
        else if(std::abs(_vc->get("LepGood_eta", idx)) < 1.479) {etaBin=1;}
        else if(std::abs(_vc->get("LepGood_eta", idx)) < 2.5) {etaBin=2;}
        if(_vc->get("LepGood_mvaIdPhys14", idx) <  _elMvaIdWP[etaBin][wp]  ) {return false;}

        return true;

}


//____________________________________________________________________________
bool SUSY3L::multiIsolation(int idx, float miniRelIso_cut, float ptRatio_cut, float ptRel_cut){
    /*
        decides whether or not a lepton is isolated according to the 3 varibale isolation requirement.
        lepton needs to pass miniRelIso cut and (ptratio or ptrel cut)
        parameters: idx (possition of lepton in LepGood vector), miniRelIso_cut, ptRatio_cut, ptRel_cut
        return: true (if lepton is isolated), flase (else)
    */

       if((_vc->get("LepGood_miniRelIso",idx) < miniRelIso_cut) && ((_vc->get("LepGood_jetPtRatio_LepAwareJECv2",idx) > ptRatio_cut) || (_vc->get("LepGood_jetPtRelv2",idx) > ptRel_cut))) return true;

       return false;

}


//____________________________________________________________________________
float SUSY3L::MT2(Candidate* lep1, Candidate* lep2, Candidate* met, double mass_invisible){
    /*
        calculates the MT2 variable based on the mt2_bisect class
        parameters: 2 leptons candidates, the met candidate, and the mass of the invisible particles
        return: value of MT2
    */

        double pa[3]     = { lep1->mass()   , lep1->px()    , lep1->py()    };
        double pb[3]     = { lep2->mass()   , lep2->px()    , lep2->py()    };
        double pmiss[3]  = { 0              , met->px()     , met->py()     };
        
        mt2 mt2_event;
        mt2_event.set_momenta( pa, pb, pmiss );
        mt2_event.set_mn( mass_invisible );
        double mt2_value = mt2_event.get_mt2();

        return mt2_value;

}

//____________________________________________________________________________
void SUSY3L::sortSelectedLeps(){
    /*
        joins all selected leptons into one candidate list ordered by pt
        parameters: none
        return: none
    */
        CandList leps_tmp;
        CandList leps_tmp2;
        
        for(int im=0;im<_nMus;im++){
            leps_tmp.push_back(_mus[im]);
        }
        for(int ie=0;ie<_nEls;ie++){
            leps_tmp.push_back(_els[ie]);
        }
        for(int it=0;it<_nTaus;it++){
            leps_tmp.push_back(_taus[it]);
        }

        while(leps_tmp.size()>0){
            float pt = -1;
            float pt_tmp = -1;
            int i_save = -1;
            for(int i=0; i < leps_tmp.size(); i++){
                pt_tmp = leps_tmp[i]->pt();
                if(pt_tmp > pt){
                    pt = pt_tmp;
                    i_save = i;
                }
            }
            for(int i=0; i < leps_tmp.size(); i++){
                if(i!=i_save){
                    leps_tmp2.push_back(leps_tmp[i]);
                }
            }
            _leps.push_back(leps_tmp[i_save]);
            leps_tmp.clear();
            leps_tmp = leps_tmp2;
            leps_tmp2.clear();
        }
        _nleps = _leps.size();
 
}


//____________________________________________________________________________
bool SUSY3L::passHLTLine(string line){
    /*
        checks if the event has been triggerd by a specific HLT trigger line
        parameters: trigger path
        return: true (if event has been triggered), false (else)
    */

    if(_vc->get(line)) return true;
    else return false;
}


//____________________________________________________________________________
bool SUSY3L::passMultiLine(bool doubleOnly){
    /*
        checks if the event has been triggerd by any of the HLT trigger lines
        parameters: doubleOnly if only dilepton paths should be checked
        return: true (if event has been triggered), false (else)
    */

    for(size_t ih=0;ih<7;ih++) {
        if(doubleOnly && ih>5) continue;
        if(passHLTLine(_hltLines[ih])) return true;
    }

    return false;
}





