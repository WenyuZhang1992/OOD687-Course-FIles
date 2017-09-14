////////////////////////////////////////////
// layout.cpp -- INCOMPLETE DEMO !!!!

#include <iostream>

void trace(const std::string& msg = "")
{
  std::cout << "\n  " << msg.c_str();
}

class DB  // defective base class
{
public:
  DB() { trace("DB::DB called"); }
  virtual void vmf1()
  { 
    int x;
    std::cout << "\n  address of local in vmf: " << &x;
    trace("DB::vmf1 called"); 
  }
  virtual void vmf2() { trace("DB::vmf2 called"); }
  void nvmf() { trace("DB::nvmf called"); }
  virtual ~DB() { trace("DB::~DB called"); }
};

class DD : public DB  // defective derived class
{
public:
  DD() { trace("DD::DD called"); }
  virtual void vmf() { trace("DD::vmf called"); }
  void nvmf() { trace("DD::nvmf called"); }
  ~DD() { trace("DD::~DD called"); }
};

void main()
{
  std::cout << "\n  Demonstrate virtual function defects ";
  std::cout << "\n ======================================\n";

  std::cout << "\n  Testing Layout ";
  std::cout << "\n ----------------\n";
  DB obj;
  typedef void(DB::*pFunc)();
  pFunc vmf1 = &DB::vmf1;
  pFunc vmf2 = &DB::vmf2;
  pFunc nvmf = &DB::nvmf;
//  &DB::~DB;

//  typedef (DB::*qFunc)();
//  qFunc ctor = &DB::DB;
//  qFunc dtor = &DB::~DB;
  
  DB* pObj = &obj;
  std::cout << "\n  obj address: " << pObj;
  std::cout << "\n  vmf1 address: " << vmf1;
  std::cout << "\n  vmf2 address: " << vmf2;
  std::cout << "\n  nvmf address: " << nvmf;

//  std::cout << "\n  dtor address: " << dtor;
  (pObj->*vmf1)();
  (pObj->*vmf2)();
  (pObj->*nvmf)();

//  pFunc* pVtbl = reinterpret_cast<pFunc*>(&obj);
  std::cout << "\n  address of vtbl: " << (int*)*(int*)(&obj);
//  pFunc* pfun = reinterpret_cast<pFunc*>((int*)*(int*)(&obj)); // calls vmf
  pFunc* pVtbl = reinterpret_cast<pFunc*>((int*)*(int*)(&obj));
  (pObj->*(*pVtbl))();
//  std::cout << "\n  address of vmf1: " << (pObj->*(*pVtbl));
  pFunc* pVtbl2 = reinterpret_cast<pFunc*>((int*)*(int*)(&obj)+1);
  (pObj->*(*pVtbl2))();
//  pFunc* pVtbl3 = reinterpret_cast<pFunc*>((int*)*(int*)(&obj)+2);
//  (pObj->*(*pVtbl3))();
//  (pObj->*(*(pVtbl+sizeof(int*))))();
  trace();

  std::cout << "\n  revised";
  typedef int* RawPtr;
  RawPtr pVtable = reinterpret_cast<RawPtr>(&obj);
  RawPtr Vtable = reinterpret_cast<RawPtr>(*pVtable);
  typedef void(*FuncPtr)();
  FuncPtr fp = reinterpret_cast<FuncPtr>(Vtable[0]);
  fp();
  fp = reinterpret_cast<FuncPtr>(Vtable[1]);
  fp();
  pFunc* nfp = reinterpret_cast<pFunc*>(Vtable[0]);
  (pObj->*(*nfp))();
}
