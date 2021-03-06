/*****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Multi-Purpose Analysis Framework                                     **
**                                                                          **
** Constantin Heidegger, CERN, Summer 2014                                  **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/

#ifndef phys14limits_HH
#define phys14limits_HH

#include "analysis/core/MPAF.hh"

class phys14limits: public MPAF {

public:


  // Member Functions

  phys14limits(std::string);
  virtual ~phys14limits();


private:

  void initialize();

  void run();
  void defineOutput();
  void modifyWeight();
  void writeOutput();

  void modifySkimming();

  bool bJetSelection(int);
  void collectKinematicObjects();
  bool electronSelection(int);
  bool goodJetSelection(int);
  bool muonSelection(int);
  bool tightVetoElectronSelection(int);
  bool tightVetoMuonSelection(int);
  bool vetoElectronSelection(int);
  bool vetoMuonSelection(int);

  void setCut(std::string, float, std::string, float = 0); 
  void setSignalRegion();

  bool cernSelection();
  bool baseSelection();
  bool mllVetoSelection();
  bool mllLMGVeto(Candidate * cand, Candidate * veto);
  bool mllZVeto(Candidate * cand, Candidate * veto);
  bool skimSelection();
  bool srSelection();
  bool ssEventSelection();
  bool vetoEventSelection();

  void fillTestPlots();
  void fillEventPlots(std::string);
  void fillLeptonPlots(std::string);
  void fillJetPlots(std::string);

  int genMatchCateg(const Candidate*);

  float HT();
  int eventCharge();

  bool dilepIsolated();

private: 

  //counter categories, 0 is ALWAYS global (even if not specified later)
  enum {kGlobal=0, kElId, kTVElId, kVElId, kMuId, kTVMuId, kVMuId, kJetId, kBJetId, kVetoLepSel, kLMGVetoLepSel, kZVetoLepSel};

  enum {kNoGenMatch=0, kMisMatchPdgId,
	kMisChargePdgId, kGenMatched};

  float _valCutHTSR;
  float _valCutMETSR;
  float _valCutHTCondSR;
  float _valCutMETHighSR;
  float _valCutMETLowSR;
  float _valCutNJetsSR;
  float _valCutNBJetsSR;

  std::string _cTypeHTSR;
  std::string _cTypeMETSR;
  std::string _cTypeHTCondSR;
  std::string _cTypeMETHighSR;
  std::string _cTypeMETLowSR;
  std::string _cTypeNJetsSR;
  std::string _cTypeNBJetsSR;

  float _upValCutHTSR;
  float _upValCutMETSR;
  float _upValCutHTCondSR;
  float _upValCutMETHighSR;
  float _upValCutMETLowSR;
  float _upValCutNJetsSR;
  float _upValCutNBJetsSR;
	
  std::vector<int> _elIdx;
  std::vector<int> _tVElIdx;
  std::vector<int> _vElIdx;
  std::vector<int> _lepIdx;
  std::vector<int> _tVLepIdx;
  std::vector<int> _vLepIdx;
  std::vector<int> _muIdx;
  std::vector<int> _tVMuIdx;
  std::vector<int> _vMuIdx;

  int _nEls;
  int _nTVEls;
  int _nVEls;
  int _nLeps;
  int _nTVLeps;
  int _nVLeps;
  int _nMus;
  int _nTVMus;
  int _nVMus;
  int _nJets;
  int _nBJets;

  CandList _leps;
  CandList _tVLeps;
  CandList _vLeps;
  CandList _els;
  CandList _tVEls;
  CandList _vEls;
  CandList _mus;
  CandList _tVMus;
  CandList _vMus;
  CandList _jets;
  CandList _bJets;
  Candidate * _met;
  Candidate * _first;
  Candidate * _second;
  
  float _HT;


  bool _mvaId;
  string _bvar;
  string _lepflav;
  
  string _mva;
  string _btag;
  string _PT;
  string _BR;
  string _SR;

};


#endif
