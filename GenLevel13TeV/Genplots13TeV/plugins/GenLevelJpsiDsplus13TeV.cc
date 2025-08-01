// -*- C++ -*-
//
// Package:    GenTutorial/GenLevelJpsiDsplus13TeV
// Class:      GenLevelJpsiDsplus13TeV
//
/**\class GenLevelJpsiDsplus13TeV GenLevelJpsiDsplus13TeV.cc GenTutorial/GenLevelJpsiDsplus13TeV/plugins/GenLevelJpsiDsplus13TeV.cc

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


class GenLevelJpsiDsplus13TeV : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
	public:
		explicit GenLevelJpsiDsplus13TeV(const edm::ParameterSet&);
		~GenLevelJpsiDsplus13TeV();

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

		// Variables to store mass, pT, rapidity and phi - Ds+
		std::vector<float> gendsplus_mass_;
		std::vector<float> gendsplus_pt_;
		std::vector<float> gendsplus_rap_;
		std::vector<float> gendsplus_phi_;

		// Variables for associated J/psi and Ds+ particle properties
		/* float genJpsidsplus_invariant_mass_;
		float genJpsidsplus_delta_rapidity_;
		float genJpsidsplus_delta_phi_; */

		std::vector<float> genJpsidsplus_invariant_mass_;
		std::vector<float> genJpsidsplus_delta_rapidity_;
		std::vector<float> genJpsidsplus_delta_phi_;


		int runNumber=0; int eventNumber=0;              
};

////////////////////////////////////////////////////////////////////////////
GenLevelJpsiDsplus13TeV::GenLevelJpsiDsplus13TeV(const edm::ParameterSet& iConfig)
	:genParticlesToken_(consumes<GenParticleCollection>(edm::InputTag{"genParticles"}))
{
	
	//tree_ = fs->make<TTree>("tree", "tree");
	
}


GenLevelJpsiDsplus13TeV::~GenLevelJpsiDsplus13TeV()
{

	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)

}

/////////////////////
void GenLevelJpsiDsplus13TeV::beginJob()
{
    // Open a ROOT file to store the output
    outFile_ = new TFile("control_plots_Jpsidsplus_13TeV.root", "RECREATE");
    
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
	// gen dsplus
	tree_ ->Branch("gendsplus_mass", &gendsplus_mass_);
	tree_ ->Branch("gendsplus_pt", &gendsplus_pt_);
	tree_ ->Branch("gendsplus_rap", &gendsplus_rap_);
	tree_ ->Branch("gendsplus_phi", &gendsplus_phi_);
	// gen jpdidsplus
	tree_ ->Branch("genJpsidsplus_invariant_mass", &genJpsidsplus_invariant_mass_);
	tree_ ->Branch("genJpsidsplus_delta_rapidity", &genJpsidsplus_delta_rapidity_);
	tree_ ->Branch("genJpsidsplus_delta_phi", &genJpsidsplus_delta_phi_);

}

void GenLevelJpsiDsplus13TeV::initialize()
{
        runNumber=0; eventNumber=0;
        genParticle_pt_.clear();
        genParticle_eta_.clear();

		genJpsi_mass_.clear();
		genJpsi_pt_.clear();
		genJpsi_rap_.clear();
		genJpsi_phi_.clear();

		gendsplus_mass_.clear();
		gendsplus_pt_.clear();
		gendsplus_rap_.clear();
		gendsplus_phi_.clear();

		genJpsidsplus_invariant_mass_.clear();
		genJpsidsplus_delta_rapidity_.clear();
		genJpsidsplus_delta_phi_.clear();



}

// ------------ method called for each event  ------------
void GenLevelJpsiDsplus13TeV::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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

	// Store J/psi and Ds+ variables
	std::vector<TLorentzVector> jpsiParticles;
	// std::vector<HepMC::GenVertex*> jpsiVertices;

	std::vector<TLorentzVector> dsplusParticles;
	// std::vector<HepMC::GenVertex*> dsplusVertices;

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
		// Check if the particle is Ds+ (PDG ID = 431 or -431)
		if (genParticles.pdgId() == 431 && genParticles.numberOfDaughters()==3){
			TLorentzVector dsplus;
			dsplus.SetPxPyPzE(genParticles.px(), genParticles.py(), 
								genParticles.pz(), genParticles.energy());
			
			float mass = dsplus.M();
			float pt = dsplus.Pt();
			float rapidity = dsplus.Rapidity();
			float phi = dsplus.Phi();

				if ((pt >= 4.0 && pt <= 60.0) && (abs(rapidity) <= 2.1) ) {
				//cout << "dsplus found" << endl;
				
				// Store all Ds+ particles
				gendsplus_mass_.push_back(mass);
				gendsplus_pt_.push_back(pt);
				gendsplus_rap_.push_back(rapidity);
				gendsplus_phi_.push_back(phi);
				dsplusParticles.push_back(dsplus);
				//dsplusVertices.push_back(genParticles.production_vertex());
			    }
						
        }
	}
	// Calculate invariant mass, delta rapidity, and delta phi for Jpsidsplus (combines each jpsi with each Ds+)
	for (size_t i=0; i < jpsiParticles.size(); ++i){
		
		for (size_t j=0; j < dsplusParticles.size(); ++j){

			/* genJpsidsplus_invariant_mass_ = (jpsiParticles[i] + dsplusParticles[j]).M(); // Invariant mass
			genJpsidsplus_delta_rapidity_ = abs(jpsiParticles[i].Rapidity() - dsplusParticles[j].Rapidity()); // Delta rapidity
			genJpsidsplus_delta_phi_ = abs(jpsiParticles[i].Phi() - dsplusParticles[j].Phi()); // Delta phi */	
			
			genJpsidsplus_invariant_mass_.push_back((jpsiParticles[i] + dsplusParticles[j]).M());
			genJpsidsplus_delta_rapidity_.push_back(abs(jpsiParticles[i].Rapidity() - dsplusParticles[j].Rapidity()));
			genJpsidsplus_delta_phi_.push_back(abs(jpsiParticles[i].Phi() - dsplusParticles[j].Phi()));


			//std::cout << "Associated object found, mass:" << genJpsidsplus_invariant_mass_ << std::endl;
			
			// Fill the tree with the new variables for this combination
			
		}
	}		

tree_ ->Fill();
}// end analyze function


///////
//++++++++++++++++++
void GenLevelJpsiDsplus13TeV::endJob(){

    cout <<"######################################################################"<<endl;
    cout << "Number of Events: " << eventNumber << " Run Number: " << runNumber << endl;
	// Write the tree to the file and close the file
    outFile_->cd();
    tree_->Write();
    outFile_->Close();
    
}

//////////////////////////////////////////
//define this as a plug-in
DEFINE_FWK_MODULE(GenLevelJpsiDsplus13TeV);
