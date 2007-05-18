#include "FWCore/Services/test/UnitTestClient.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include <iostream>
#include <string>

namespace edmtest
{


void
  UnitTestClient::analyze( edm::Event      const & e
                           , edm::EventSetup const & es )
{
  
}  // MessageLoggerClient::analyze()


}  // namespace edmtest


using edmtest::UnitTestClient;
DEFINE_FWK_MODULE(UnitTestClient);
