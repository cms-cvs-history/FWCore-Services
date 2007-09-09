#include "FWCore/Services/test/UnitTestClient.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include <iostream>
#include <string>

#include <cmath>
#include <float.h>

namespace edmtest
{
void
  UnitTestClient::analyze( edm::Event      const & e
                           , edm::EventSetup const & es )
{

   double x = 1.0;
   double y = DBL_MAX;
   edm::LogVerbatim("FPExceptions") << "\tx = " << x;
   edm::LogVerbatim("FPExceptions") << "\ty = " << y;

   // DivideByZero
   edm::LogVerbatim("FPExceptions") << "\tForce DivideByZero";
   double zero = 0.0;
   double a = x / zero;
   edm::LogVerbatim("FPExceptions") << "\ta = " << a;

   // Invalid
   edm::LogVerbatim("FPExceptions") << "\tForce Invalid";
   double b = std::log(-1.0);
   edm::LogVerbatim("FPExceptions") << "\tb = " << b;

   // Overflow (actually precision)
   edm::LogVerbatim("FPExceptions") << "\tForce Overflow";
   double c = y * y;
   edm::LogVerbatim("FPExceptions") << "\tc = " << c;

   // Underflow (actually precision)
   edm::LogVerbatim("FPExceptions") << "\tForce Underflow";
   double d = x / y;
   edm::LogVerbatim("FPExceptions") << "\td = " << d;
}  

}  // namespace edmtest


using edmtest::UnitTestClient;
DEFINE_FWK_MODULE(UnitTestClient);
