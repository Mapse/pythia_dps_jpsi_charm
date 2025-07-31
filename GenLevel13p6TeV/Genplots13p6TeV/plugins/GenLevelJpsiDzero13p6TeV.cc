// -*- C++ -*-
//
// Package:    GenTutorial/GenLevelJpsiDzero13p6TeV
// Class:      GenLevelJpsiDzero13p6TeV
//
/**\class GenLevelJpsiDzero13p6TeV GenLevelJpsiDzero13p6TeV.cc GenTutorial/GenLevelJpsiDzero13p6TeV/plugins/GenLevelJpsiDzero13p6TeV.cc

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
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "TFile.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "HepMC/GenVertex.h"

// For gen particles
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

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


class GenLevelJpsiDzero13p6TeV : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
	public:
		explicit GenLevelJpsiDzero13p6TeV(const edm::ParameterSet&);
		~GenLevelJpsiDzero13p6TeV();

	private:
		virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
                virtual void beginJob() override ;
                virtual void endJob() override ;
                void initialize();
		
		// ----------member data ---------------------------
		
		// Token for gen particles (Run 3)
		edm::EDGetTokenT<reco::GenParticleCollection> genParticlesToken_;

		//edm::EDGetTokenT<edm::HepMCProduct> hepMCToken_;   

		// Output file and ttree
		TFile* outFile_;
		TTree *tree_;

		// Variables to store pT and eta
		std::vector<float> genParticle_pt_;
		std::vector<float> genParticle_eta_;

		// Variables to store mass, pT, rapidity and phi - J/psi
		std::vector<float> genJpsi_mass_;
		std::vector<float> genJpsi_pt_;
		std::vector<float> genJpsi_rap_;
		std::vector<float> genJpsi_phi_;

		// Variables to store mass, pT, rapidity and phi / D0
		std::vector<float> gendzero_mass_;
		std::vector<float> gendzero_pt_;
		std::vector<float> gendzero_rap_;
		std::vector<float> gendzero_phi_;

		// Variables for associated J/psi and D0 particle properties
		std::vector<float> genJpsidzero_invariant_mass_;
		std::vector<float> genJpsidzero_delta_rapidity_;
		std::vector<float> genJpsidzero_delta_phi_;

		int runNumber=0; int eventNumber=0; 
	         
};

////////////////////////////////////////////////////////////////////////////
GenLevelJpsiDzero13p6TeV::GenLevelJpsiDzero13p6TeV(const edm::ParameterSet& iConfig)
	//:genParticlesToken_(consumes<GenParticleCollection>(edm::InputTag{"genParticles"}))
{
	
	// In the constructor, change the token to consume HepMCProduct
	genParticlesToken_ = consumes<reco::GenParticleCollection>(edm::InputTag("genParticles"));

}


GenLevelJpsiDzero13p6TeV::~GenLevelJpsiDzero13p6TeV()
{

	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)

}

/////////////////////
void GenLevelJpsiDzero13p6TeV::beginJob()
{
    // Open a ROOT file to store the output
    outFile_ = new TFile("control_plots_jpsidzero_13p6TeV.root", "RECREATE");
    
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

void GenLevelJpsiDzero13p6TeV::initialize()
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
void GenLevelJpsiDzero13p6TeV::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	using namespace edm;
	using namespace std;

    // Clear the vectors before filling
    initialize();
    //run, event, lumi section
	runNumber= iEvent.id().run();
	eventNumber= iEvent.id().event();

	// Store J/psi and D0 variables
	std::vector<TLorentzVector> jpsiParticles;
	//std::vector<HepMC::GenVertex*> jpsiVertices;

	std::vector<TLorentzVector> dzeroParticles;
	//std::vector<HepMC::GenVertex*> dzeroVertices;

	edm::Handle<reco::GenParticleCollection> genParticles;
	iEvent.getByToken(genParticlesToken_, genParticles);

	if (genParticles.isValid()) {

        // Loop over all particles in the HepMC event
		for (const auto& genParticle : *genParticles) {

			genParticle_pt_.push_back(genParticle.pt());
        	genParticle_eta_.push_back(genParticle.eta());

			//Loop for Jpsi
			//if (genParticle->pdg_id() == 443){
			if (genParticle.pdgId() == 443) {
				
				TLorentzVector jpsi;
				
				jpsi.SetPtEtaPhiM(genParticle.pt(), genParticle.eta(), genParticle.phi(), genParticle.mass());
				
				float mass = jpsi.M();
				float pt = jpsi.Pt();
                float rapidity = jpsi.Rapidity();
                float phi = jpsi.Phi();

				// Store only if pT is between 25 and 100 GeV/c
                if ((pt >= 25.0 && pt <= 100.0) && (abs(rapidity) <= 1.2 ) ) {
					
					//cout << "Jpsi found" << endl;
					genJpsi_mass_.push_back(mass);
                    genJpsi_pt_.push_back(pt);
                    genJpsi_rap_.push_back(rapidity);
                    genJpsi_phi_.push_back(phi);
					jpsiParticles.push_back(jpsi);
					//jpsiVertices.push_back(genParticle->production_vertex());
                }

			}

			// Check if the particle is D0 (PDG ID = 421 or -421)
            //if (std::abs(genParticle->pdg_id()) == 421) {
			if (abs(genParticle.pdgId()) == 421) {
				
				TLorentzVector dzero;
                
				dzero.SetPtEtaPhiM(genParticle.pt(), genParticle.eta(), genParticle.phi(), genParticle.mass());

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
						//dzeroVertices.push_back(genParticle->production_vertex());
                }
                
                
            }

			
        }
		// Calculate invariant mass, delta rapidity, and delta phi for Jpsidzero (combines each jpsi with each D0)
		for (size_t i=0; i < jpsiParticles.size(); ++i){
			
			for (size_t j=0; j < dzeroParticles.size(); ++j){

				genJpsidzero_invariant_mass_.push_back((jpsiParticles[i] + dzeroParticles[j]).M());
				genJpsidzero_delta_rapidity_.push_back(abs(jpsiParticles[i].Rapidity() - dzeroParticles[j].Rapidity()));
				genJpsidzero_delta_phi_.push_back(abs(jpsiParticles[i].Phi() - dzeroParticles[j].Phi()));
				
			}
		}
		
    } else {
        //edm::LogWarning("HepMCProduct") << "HepMCProduct not found!";
		edm::LogWarning("GenParticles") << "GenParticleCollection not found!";
    }
			
// Fill the tree with the new variables for this combination
tree_ ->Fill();
}// end analyze function

///////
//++++++++++++++++++
void GenLevelJpsiDzero13p6TeV::endJob(){

    cout <<"######################################################################"<<endl;
    cout << "Number of Events: " << eventNumber << " Run Number: " << runNumber << endl;

	// Write the tree to the file and close the file
    outFile_->cd();
    tree_->Write();
    outFile_->Close();
    
}

//////////////////////////////////////////
//define this as a plug-in
DEFINE_FWK_MODULE(GenLevelJpsiDzero13p6TeV);
