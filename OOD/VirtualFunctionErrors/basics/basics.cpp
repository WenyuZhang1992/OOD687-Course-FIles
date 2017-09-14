///////////////////////////////////////////////////////////////
// basics.cpp - Illustrate problems caused by:               //
//              - failure to provide virtual destructor      //
//              - overriding non-virtual functions           //
//                                                           //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2008 //
///////////////////////////////////////////////////////////////

#include <iostream>

void trace(const std::string& msg = "")
{
  std::cout << "\n  " << msg.c_str();
}

class DB  // defective base class - no virtual dtor
{
public:
  DB() { trace("DB::DB called"); }
  virtual void vmf() { trace("DB::vmf called"); }
  void nvmf() { trace("DB::nvmf called"); }
  ~DB() { trace("DB::~DB called"); }
};

class DD : public DB  // defective derived class - redef of non-virtual member
{
public:
  DD() { trace("DD::DD called"); }
  virtual void vmf() { trace("DD::vmf called"); }
  void nvmf() { trace("DD::nvmf called"); }
  ~DD() { trace("DD::~DD called"); }
};

class DDA : public DD  // defective derived class - more of same
{
public:
  DDA() { trace("DDA::DDA called"); }
  virtual void vmf() { trace("DDA::vmf called"); }
  void nvmf() { trace("DDA::nvmf called"); }
  ~DDA() { trace("DDA::~DDA called"); }
};

void main()
{
  std::cout << "\n  Demonstrate virtual function defects ";
  std::cout << "\n ======================================\n";

  std::cout << "\n  -- stack based instantiations --\n";

  // defining anonymous local scopes to trigger destruction - no problems here

  {  DB db; db.vmf(); db.nvmf(); } trace();
  {  DD dd; dd.vmf(); dd.nvmf(); } trace();
  
  std::cout << "\n  -- heap based instantiations --\n";
  
  // two problems with operation of derived class:
  // - redefined non-virtual function called on wrong object
  // - derived dtor not called
  //   - a problem even if there are no virtual functions in DB and DD

  DB* pDB = new DB;
  pDB->vmf();
  pDB->nvmf();
  delete pDB;
  trace();

  DB* pDBD = new DD;
  pDBD->vmf();
  pDBD->nvmf();       // DB::nvmf() called on DD object!
  delete pDBD;        // won't call DD::~DD()!
  trace();

  DB* pDBDA = new DDA;
  pDBDA->vmf();
  pDBDA->nvmf();       // DB::nvmf() called on DDA object!
  delete pDBDA;        // won't call either DDA::~DDA() or DD::~DD()!
  trace();

  // If you simply declare the DB dtor virtual, all heap-based instances
  // are correctly destroyed.  Note that this implies that declaring
  // virtual DB dtor is essential, but declaring DD dtor virtual is optional

  // The call of the redefined non-virtual functions on base object persists
  // even if you declare base dtor virtual.
}
