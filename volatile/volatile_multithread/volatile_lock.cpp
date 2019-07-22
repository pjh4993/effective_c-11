#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

template <typename T>
class LockingPtr{
    public:
        LockingPtr(volatile T& obj, mutex& mtx)
            :pObj_(const_cast<T*>(&obj)),
            pMtx_(&mtx){
            mtx.lock();    
        }
        ~LockingPtr(){
            pMtx_->unlock();
        }
        T& operator*(){
            return *pObj_;
        }
        T* operator->(){
            return pObj_;
        }

    private:
        T* pObj_;
        mutex* pMtx_;
        LockingPtr(const LockingPtr&);
        LockingPtr& operator=(const LockingPtr&);
};

#ifdef SYNCBUF

class SyncBuf{
    public:
        void th1();
        void th2();
        size_t Size();
        void Size(unsigned int);
        SyncBuf(){};
    private:
        typedef vector<char> BufT;
        volatile BufT buffer_;
        mutex mtx_;
};

void SyncBuf::th1(){
    LockingPtr<BufT> lpBuf(buffer_,mtx_);
    cout<< "first thread start" << endl;
    BufT::iterator i = lpBuf->begin();
    for(;i!=lpBuf->end();++i){
        *i = 't';
        cout << *i ;
    }
    cout << endl;
}

void SyncBuf::th2(){
    LockingPtr<BufT> lpBuf(buffer_,mtx_);
    cout << "second thread start" << endl;
    BufT::iterator i = lpBuf->begin();
    for(;i!=lpBuf->end();++i){
        *i = 's';
        cout << *i;
    }
    cout << endl;
}

size_t SyncBuf::Size(){
    return LockingPtr<BufT>(buffer_, mtx_)->size();
}

void SyncBuf::Size(unsigned int size_){
    LockingPtr<BufT>(buffer_, mtx_)->resize(size_);
    cout << "set size of buf" << endl;
}

#endif
class NaiveCounter{
    public:
        void increment(){
            ctr_++;
        }
        void decrement(){
            ctr_--;
        }
        void set(int t){
            ctr_ = t;
        }
        int get(){
            return ctr_;
        }
    private:
        volatile int ctr_;
};

class Counter{
    public:
        void increment(){
            ++*LockingPtr<int>(ctr_,mtx_);
        }
        void decrement(){
            --*LockingPtr<int>(ctr_,mtx_);
        }
        void set(int t){
            *LockingPtr<int>(ctr_,mtx_) = t;
        }
        int get(){
            return *LockingPtr<int>(ctr_,mtx_);
        }
    private:
        volatile int ctr_;
        mutex mtx_;
};
#ifdef CNT

#endif

int main(void){
#ifdef SYNCBUF
    SyncBuf bf;
    void (SyncBuf::*memfunc)(unsigned int) = &SyncBuf::Size;
    thread hp1(&SyncBuf::th1,&bf);
    thread hp2(&SyncBuf::th2,&bf);
    thread hp3(memfunc,&bf,3);
    hp3.join();
    hp1.join();
    hp2.join();
#endif
#ifdef CNT
    NaiveCounter nc;
    Counter cnt;
    thread ncSet(&NaiveCounter::set,&nc, 5),
           ncInc(&NaiveCoutner::increment,&nc),
           ncDec(&NaiveCounter::decrement,&nc),
           ncGet(&NaiveCoutner::get,&nc);
    thread cSet(&Counter::set,&cnt, 5),
           cInc(&Coutner::increment,&cnt),
           cDec(&Counter::decrement,&cnt),
           cGet(&Coutner::get,&cnt);

    ncSet.join();
    ncInc.join();
    ncInc.join();
    ncDec.join();
    cout << "Naive counter result "<< ncGet.join() << endl;

    cSet.join();
    cInc.join();
    cInc.join();
    cDec.join();
    cout << "counter result " << cGet.join() << endl;

#endif
    cout << "done" << endl;
    return 0;
}
