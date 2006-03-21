#include <iostream>
#include <sstream>
#include <string>
#include <vector>


#include "DataFormats/Common/interface/EventID.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/Services/interface/JobReport.h"

using edm::service::Token;

void work()
{
  // Make the service.
  edm::ParameterSet ps;
  edm::ActivityRegistry areg;

  edm::service::JobReport jrs(ps, areg);
  std::vector<Token> inputTokens;
  std::vector<Token> outputTokens;

  // Make input files
  std::vector<std::string> branchnames;
  branchnames.push_back("branch_1_");
  branchnames.push_back("branch_2_");

  for (int i = 0; i < 10; ++i)
    {
      std::ostringstream oss;
      oss << i;
      std::string seq_tag = oss.str();
      std::vector<std::string> localBranchNames(branchnames);
      localBranchNames[0] += seq_tag;
      localBranchNames[1] += seq_tag;
      Token t = jrs.inputFileOpened("phys" + seq_tag,
				    "log" + seq_tag,
				    "cat" + seq_tag,
				    "class" + seq_tag,
				    "label" + seq_tag,
				    localBranchNames);
      inputTokens.push_back(t);
    }

  try
    {
      jrs.eventReadFromFile(24, edm::EventID());
      assert( "Failed to throw required exception" == 0);
    }
  catch ( edm::Exception & x )
    {
      assert( x.categoryCode() == edm::errors::LogicError );
    }
  catch ( ... )
    {
      assert( "Threw unexpected exception type" == 0 );
    }
  

  // Fake the end-of-job
  areg.postEndJobSignal_();
}

void fail()
{
  // Make the service.
  edm::ParameterSet ps;
  edm::ActivityRegistry areg;

  edm::service::JobReport jrs(ps, areg);
  std::vector<Token> inputTokens;
  std::vector<Token> outputTokens;

  areg.jobFailureSignal_();
}

int main()
{
  int rc = -1;
  try
    {
      work();
      fail();
      rc = 0;
    }

  catch ( edm::Exception & x )
    {
      std::cerr << x << '\n';
      rc = 1;
    }
  catch ( ... )
    {
      std::cerr << "Unknown exception caught\n";
      rc = 2;
    }
  return rc;
}