// -*- C++ -*-
//
// Package:    GenTutorial/GenLevelJpsiDplus13TeV
// Class:      GenLevelJpsiDplus13TeV
//
/**\class GenLevelJpsiDplus13TeV GenLevelJpsiDplus13TeV.cc GenTutorial/GenLevelJpsiDplus13TeV/plugins/GenLevelJpsiDplus13TeV.cc

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


class GenLevelJpsiDplus13TeV : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
	public:
		explicit GenLevelJpsiDplus13TeV(const edm::ParameterSet&);
		~GenLevelJpsiDplus13TeV();

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

		// Variables to store mass, pT, rapidity and phi - D+
		std::vector<float> gendplus_mass_;
		std::vector<float> gendplus_pt_;
		std::vector<float> gendplus_rap_;
		std::vector<float> gendplus_phi_;

		// Variables for associated J/psi and D+ particle properties
		/* float genJpsidplus_invariant_mass_;
		float genJpsidplus_delta_rapidity_;
		float genJpsidplus_delta_phi_; */

		std::vector<float> genJpsidplus_invariant_mass_;
		std::vector<float> genJpsidplus_delta_rapidity_;
		std::vector<float> genJpsidplus_delta_phi_;


		int runNumber=0; int eventNumber=0;              
};

////////////////////////////////////////////////////////////////////////////
GenLevelJpsiDplus13TeV::GenLevelJpsiDplus13TeV(const edm::ParameterSet& iConfig)
	:genParticlesToken_(consumes<GenParticleCollection>(edm::InputTag{"genParticles"}))
{
	
	//tree_ = fs->make<TTree>("tree", "tree");
	
}


GenLevelJpsiDplus13TeV::~GenLevelJpsiDplus13TeV()
{

	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)

}

/////////////////////
void GenLevelJpsiDplus13TeV::beginJob()
{
    // Open a ROOT file to store the output
    outFile_ = new TFile("control_plots_jpsidplus_13TeV.root", "RECREATE");
    
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
	// gen dplus
	tree_ ->Branch("gendplus_mass", &gendplus_mass_);
	tree_ ->Branch("gendplus_pt", &gendplus_pt_);
	tree_ ->Branch("gendplus_rap", &gendplus_rap_);
	tree_ ->Branch("gendplus_phi", &gendplus_phi_);
	// gen jpdidplus
	tree_ ->Branch("genJpsidplus_invariant_mass", &genJpsidplus_invariant_mass_);
	tree_ ->Branch("genJpsidplus_delta_rapidity", &genJpsidplus_delta_rapidity_);
	tree_ ->Branch("genJpsidplus_delta_phi", &genJpsidplus_delta_phi_);

}

void GenLevelJpsiDplus13TeV::initialize()
{
        runNumber=0; eventNumber=0;
        genParticle_pt_.clear();
        genParticle_eta_.clear();

		genJpsi_mass_.clear();
		genJpsi_pt_.clear();
		genJpsi_rap_.clear();
		genJpsi_phi_.clear();

		gendplus_mass_.clear();
		gendplus_pt_.clear();
		gendplus_rap_.clear();
		gendplus_phi_.clear();

		genJpsidplus_invariant_mass_.clear();
		genJpsidplus_delta_rapidity_.clear();
		genJpsidplus_delta_phi_.clear();



}

// ------------ method called for each event  ------------
void GenLevelJpsiDplus13TeV::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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

	// Store J/psi and D+ variables
	std::vector<TLorentzVector> jpsiParticles;
	// std::vector<HepMC::GenVertex*> jpsiVertices;

	std::vector<TLorentzVector> dplusParticles;
	// std::vector<HepMC::GenVertex*> dplusVertices;

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
		// Check if the particle is D+ (PDG ID = 411 or -411)
		if (genParticles.pdgId() == 411 && genParticles.numberOfDaughters()==3){
			TLorentzVector dplus;
			dplus.SetPxPyPzE(genParticles.px(), genParticles.py(), 
								genParticles.pz(), genParticles.energy());
			
			float mass = dplus.M();
			float pt = dplus.Pt();
			float rapidity = dplus.Rapidity();
			float phi = dplus.Phi();

				if ((pt >= 4.0 && pt <= 60.0) && (abs(rapidity) <= 2.1) ) {
				//cout << "dplus found" << endl;
				
				// Store all D+ particles
				gendplus_mass_.push_back(mass);
				gendplus_pt_.push_back(pt);
				gendplus_rap_.push_back(rapidity);
				gendplus_phi_.push_back(phi);
				dplusParticles.push_back(dplus);
				//dplusVertices.push_back(genParticles.production_vertex());
			    }
						
        }
	}
	// Calculate invariant mass, delta rapidity, and delta phi for Jpsidplus (combines each jpsi with each D+)
	for (size_t i=0; i < jpsiParticles.size(); ++i){
		
		for (size_t j=0; j < dplusParticles.size(); ++j){

			/* genJpsidplus_invariant_mass_ = (jpsiParticles[i] + dplusParticles[j]).M(); // Invariant mass
			genJpsidplus_delta_rapidity_ = abs(jpsiParticles[i].Rapidity() - dplusParticles[j].Rapidity()); // Delta rapidity
			genJpsidplus_delta_phi_ = abs(jpsiParticles[i].Phi() - dplusParticles[j].Phi()); // Delta phi */	
			
			genJpsidplus_invariant_mass_.push_back((jpsiParticles[i] + dplusParticles[j]).M());
			genJpsidplus_delta_rapidity_.push_back(abs(jpsiParticles[i].Rapidity() - dplusParticles[j].Rapidity()));
			Double_t dphi = abs(jpsiParticles[i].Phi() - dplusParticles[j].Phi());
			genJpsidplus_delta_phi_.push_back(TMath::Min(dphi, 2*TMath::Pi() - dphi ));


			//std::cout << "Associated object found, mass:" << genJpsidplus_invariant_mass_ << std::endl;
			
			// Fill the tree with the new variables for this combination
			
		}
	}		

tree_ ->Fill();
}// end analyze function


///////
//++++++++++++++++++
void GenLevelJpsiDplus13TeV::endJob(){

    cout <<"######################################################################"<<endl;
    cout << "Number of Events: " << eventNumber << " Run Number: " << runNumber << endl;
	// Write the tree to the file and close the file
    outFile_->cd();
    tree_->Write();
    outFile_->Close();
    
}

//////////////////////////////////////////
//define this as a plug-in
DEFINE_FWK_MODULE(GenLevelJpsiDplus13TeV);
