// -*- C++ -*-
//
// Package:    GenTutorial/GenLevelJpsiDzero13TeV
// Class:      GenLevelJpsiDzero13TeV
//
/**\class GenLevelJpsiDzero13TeV GenLevelJpsiDzero13TeV.cc GenTutorial/GenLevelJpsiDzero13TeV/plugins/GenLevelJpsiDzero13TeV.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Sandro Fonseca De Souza
//         Created:  Wed, 05 Feb 2020 09:25:53 GMT
//
//


// system include files
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TH1.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.

using reco::GenParticleCollection;
using namespace std;
using namespace reco;
using namespace edm;


class GenLevelJpsiDzero13TeV : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
	public:
		explicit GenLevelJpsiDzero13TeV(const edm::ParameterSet&);
		~GenLevelJpsiDzero13TeV();

	private:
		virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
                virtual void beginJob() override ;
                virtual void endJob() override ;
                void initialize();
		// ----------member data ---------------------------
		
		// Token for gen particles (Run 2)
		edm::EDGetTokenT<GenParticleCollection> genParticlesToken_; 
		
		// Output file and ttree
		TFile* outFile_;
		TTree *tree_;

		// Variables to store pT and eta (all gen particles)
		std::vector<float> genParticle_pt_;
		std::vector<float> genParticle_eta_;

		// Variables to store mass, pT, rapidity and phi - J/psi
		std::vector<float> genJpsi_mass_;
		std::vector<float> genJpsi_pt_;
		std::vector<float> genJpsi_rap_;
		std::vector<float> genJpsi_phi_;

		// Variables to store mass, pT, rapidity and phi - D0
		std::vector<float> gendzero_mass_;
		std::vector<float> gendzero_pt_;
		std::vector<float> gendzero_rap_;
		std::vector<float> gendzero_phi_;

		// Variables for associated J/psi and D0 particle properties
		/* float genJpsidzero_invariant_mass_;
		float genJpsidzero_delta_rapidity_;
		float genJpsidzero_delta_phi_; */

		std::vector<float> genJpsidzero_invariant_mass_;
		std::vector<float> genJpsidzero_delta_rapidity_;
		std::vector<float> genJpsidzero_delta_phi_;


		int runNumber=0; int eventNumber=0;              
};

////////////////////////////////////////////////////////////////////////////
GenLevelJpsiDzero13TeV::GenLevelJpsiDzero13TeV(const edm::ParameterSet& iConfig)
	:genParticlesToken_(consumes<GenParticleCollection>(edm::InputTag{"genParticles"}))
{
	
	//tree_ = fs->make<TTree>("tree", "tree");
	
}


GenLevelJpsiDzero13TeV::~GenLevelJpsiDzero13TeV()
{

	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)

}

/////////////////////
void GenLevelJpsiDzero13TeV::beginJob()
{
    // Open a ROOT file to store the output
    outFile_ = new TFile("control_plots_jpsidzero_13TeV.root", "RECREATE");
    
    // Create a tree and set up branches for pT and eta
    tree_ = new TTree("GenTree", "Tree containing distributions");
    // all gen particles
	tree_->Branch("pt", &genParticle_pt_);
    tree_->Branch("eta", &genParticle_eta_);
	// gen jpsi
	tree_ ->Branch("genJpsi_mass", &genJpsi_mass_);
	tree_ ->Branch("genJpsi_pt", &genJpsi_pt_);
	tree_ ->Branch("genJpsi_rap", &genJpsi_rap_);
	tree_ ->Branch("genJpsi_phi", &genJpsi_phi_);
	// gen dzero
	tree_ ->Branch("gendzero_mass", &gendzero_mass_);
	tree_ ->Branch("gendzero_pt", &gendzero_pt_);
	tree_ ->Branch("gendzero_rap", &gendzero_rap_);
	tree_ ->Branch("gendzero_phi", &gendzero_phi_);
	// gen jpdidzero
	tree_ ->Branch("genJpsidzero_invariant_mass", &genJpsidzero_invariant_mass_);
	tree_ ->Branch("genJpsidzero_delta_rapidity", &genJpsidzero_delta_rapidity_);
	tree_ ->Branch("genJpsidzero_delta_phi", &genJpsidzero_delta_phi_);

}

void GenLevelJpsiDzero13TeV::initialize()
{
        runNumber=0; eventNumber=0;
        genParticle_pt_.clear();
        genParticle_eta_.clear();

		genJpsi_mass_.clear();
		genJpsi_pt_.clear();
		genJpsi_rap_.clear();
		genJpsi_phi_.clear();

		gendzero_mass_.clear();
		gendzero_pt_.clear();
		gendzero_rap_.clear();
		gendzero_phi_.clear();

		genJpsidzero_invariant_mass_.clear();
		genJpsidzero_delta_rapidity_.clear();
		genJpsidzero_delta_phi_.clear();



}

// ------------ method called for each event  ------------
void GenLevelJpsiDzero13TeV::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	using namespace edm;
	using namespace std;
    
	//to clear vectors
    initialize();
    //run, event, lumi section
	runNumber= iEvent.id().run();
	eventNumber= iEvent.id().event();

	// Handle for GenParticleCollection
	Handle<GenParticleCollection> genParticles;
	iEvent.getByToken(genParticlesToken_, genParticles);
	//cout << "Running " << endl;  

	// Store J/psi and D0 variables
	std::vector<TLorentzVector> jpsiParticles;
	// std::vector<HepMC::GenVertex*> jpsiVertices;

	std::vector<TLorentzVector> dzeroParticles;
	// std::vector<HepMC::GenVertex*> dzeroVertices;

	for(const auto& genParticles : iEvent.get(genParticlesToken_) ){

		// Save the pT and eta of all gen particles
        genParticle_pt_.push_back(genParticles.pt());
		genParticle_eta_.push_back(genParticles.eta());

		//Loop for Jpsi
		if (genParticles.pdgId() == 443 && genParticles.numberOfDaughters()==2){
			
			TLorentzVector jpsi;
			jpsi.SetPxPyPzE(genParticles.px(), genParticles.py(), 
			                genParticles.pz(), genParticles.energy());

			float mass = jpsi.M();
			float pt = jpsi.Pt();
			float rapidity = jpsi.Rapidity();
			float phi = jpsi.Phi();

			// Store only if pT is between 25 and 100 GeV/c
                if ((pt >= 25.0 && pt <= 100.0) && (abs(rapidity) <= 1.2 ) ) {

                    genJpsi_mass_.push_back(mass);
					genJpsi_pt_.push_back(pt);
                    genJpsi_rap_.push_back(rapidity);
                    genJpsi_phi_.push_back(phi);
					jpsiParticles.push_back(jpsi);
					//jpsiVertices.push_back(genParticles.production_vertex());
                }
		}
		// Check if the particle is D0 (PDG ID = 421 or -421)
		if (genParticles.pdgId() == 421 && genParticles.numberOfDaughters()==2){
			TLorentzVector dzero;
			dzero.SetPxPyPzE(genParticles.px(), genParticles.py(), 
								genParticles.pz(), genParticles.energy());
			
			float mass = dzero.M();
			float pt = dzero.Pt();
			float rapidity = dzero.Rapidity();
			float phi = dzero.Phi();

				if ((pt >= 4.0 && pt <= 60.0) && (abs(rapidity) <= 2.1) ) {
					//cout << "dzero found" << endl;
					
					// Store all D0 particles
					gendzero_mass_.push_back(mass);
					gendzero_pt_.push_back(pt);
					gendzero_rap_.push_back(rapidity);
					gendzero_phi_.push_back(phi);
					dzeroParticles.push_back(dzero);
					//dzeroVertices.push_back(genParticles.production_vertex());
			    }
						
        }
	}
	// Calculate invariant mass, delta rapidity, and delta phi for Jpsidzero (combines each jpsi with each D0)
	for (size_t i=0; i < jpsiParticles.size(); ++i){
		
		for (size_t j=0; j < dzeroParticles.size(); ++j){

			/* genJpsidzero_invariant_mass_ = (jpsiParticles[i] + dzeroParticles[j]).M(); // Invariant mass
			genJpsidzero_delta_rapidity_ = abs(jpsiParticles[i].Rapidity() - dzeroParticles[j].Rapidity()); // Delta rapidity
			genJpsidzero_delta_phi_ = abs(jpsiParticles[i].Phi() - dzeroParticles[j].Phi()); // Delta phi */	
			
			genJpsidzero_invariant_mass_.push_back((jpsiParticles[i] + dzeroParticles[j]).M());
			genJpsidzero_delta_rapidity_.push_back(abs(jpsiParticles[i].Rapidity() - dzeroParticles[j].Rapidity()));
			float dphi = abs(jpsiParticles[i].Phi() - dzeroParticles[j].Phi());
			genJpsidzero_delta_phi_.push_back(TMath::Min(dphi, 2*TMath::Pi() - dphi ));


			//std::cout << "Associated object found, mass:" << genJpsidzero_invariant_mass_ << std::endl;
			
			// Fill the tree with the new variables for this combination
			
		}
	}		

tree_ ->Fill();
}// end analyze function


///////
//++++++++++++++++++
void GenLevelJpsiDzero13TeV::endJob(){

    cout <<"######################################################################"<<endl;
    cout << "Number of Events: " << eventNumber << " Run Number: " << runNumber << endl;
	// Write the tree to the file and close the file
    outFile_->cd();
    tree_->Write();
    outFile_->Close();
    
}

//////////////////////////////////////////
//define this as a plug-in
DEFINE_FWK_MODULE(GenLevelJpsiDzero13TeV);
