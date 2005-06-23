/*----------------------------------------------------------------------
$Id: EmptyInputService.h,v 1.1 2005/05/29 02:29:54 wmtan Exp $
----------------------------------------------------------------------*/

#include <memory>

#include "FWCore/CoreFramework/interface/CoreFrameworkfwd.h"
#include "FWCore/CoreFramework/interface/Retriever.h"
#include "FWCore/CoreFramework/interface/InputService.h"
#include "FWCore/EDProduct/interface/CollisionID.h"

namespace edm {
  class ParameterSet;

  class EmptyInputService : public InputService {
  public:
    explicit EmptyInputService(ParameterSet const&, const InputServiceDescription&);
    ~EmptyInputService();
  private:
    std::auto_ptr<EventPrincipal> read();
    
    CollisionID nextID_;
    int remainingEvents_;
    Retriever* retriever_;
  };


  struct FakeRetriever : public Retriever {
    virtual ~FakeRetriever();
    virtual std::auto_ptr<EDProduct> get(BranchKey const& k);
  };
}