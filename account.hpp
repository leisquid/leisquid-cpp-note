#ifndef _account_hpp
#define _account_hpp

class Account {
public:
    Account();
    explicit Account(const char *, double = 0.0);
    Account(const Account &);
    ~Account();
    // ... 
private:
    char *_name;
    unsigned int _acct_nmbr;
    double _balance;
};
inline Account::~Account() {
    delete[] _name;
    // return_acct_nmbr(_acct_nmbr);
}

#endif
