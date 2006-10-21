// -*- C++ -*-
//
// Package:    TestRandomNumberServiceAnalyzer
// Class:      TestRandomNumberServiceAnalyzer
// 
/**\class TestRandomNumberServiceAnalyzer TestRandomNumberServiceAnalyzer.cc FWCore/TestRandomNumberServiceAnalyzer/src/TestRandomNumberServiceAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Chris Jones
//         Created:  Tue Mar  7 11:57:09 EST 2006
// $Id: TestRandomNumberServiceAnalyzer.cc,v 1.1 2006/03/07 19:46:43 chrjones Exp $
//
//


// system include files
#include <memory>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"

//
// class decleration
//

class TestRandomNumberServiceAnalyzer : public edm::EDAnalyzer {
   public:
      explicit TestRandomNumberServiceAnalyzer(const edm::ParameterSet&);
      ~TestRandomNumberServiceAnalyzer();


      virtual void analyze(const edm::Event&, const edm::EventSetup&);
   private:
      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TestRandomNumberServiceAnalyzer::TestRandomNumberServiceAnalyzer(const edm::ParameterSet& iConfig)
{
   using namespace edm;
   //see if random number generator is accessible
   Service<RandomNumberGenerator> rng;
   std::cout << rng->mySeed() <<std::endl;
}


TestRandomNumberServiceAnalyzer::~TestRandomNumberServiceAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
TestRandomNumberServiceAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   Service<RandomNumberGenerator> rng;
   std::cout << rng->mySeed() <<std::endl;
}

//define this as a plug-in
DEFINE_FWK_MODULE(TestRandomNumberServiceAnalyzer);
