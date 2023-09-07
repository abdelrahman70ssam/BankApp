#ifndef BANK_H
#define BANK_H


#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<fstream>

using namespace std ;

fstream file("UsersInfo.txt" , ios::app) ;

class BankApplication ;
class BankAccount ;
class Client ;
class SavingBankAccount ;

class BankApplication
{   
    vector<pair<Client , BankAccount
      >> accounts_list ;
    public:
        void run();
        void create_new_acc() ;
        void link_add_basic(Client& , BankAccount& );
        void link_add_saving(Client& ,  BankAccount* );
        void list_clients_and_accounts(fstream& file) ;
        BankAccount find_account_basic(const vector<pair<Client , BankAccount >>& vbasic);
        SavingBankAccount find_account_saving(const vector<pair<Client , BankAccount>>& vSaving);
        void deposit_app();
        void withdraw_app();
};

class BankAccount 
{
    protected :
        int balance ;
        static int index ;
        

    public:
    // constructors 
        BankAccount():balance(0){};
        BankAccount(int balance){
            this->balance = balance ;
        }
    // setters and getters
        void setID();
        virtual bool setBalance(int);
        int getID() const;
        int getBalance() const;
    // methods
    virtual void withdraw(const int) ; 
    virtual void deposit(const int) ;
    void print_pretty(const BankAccount&) ;

    friend class BankApplication ;
};

class SavingBankAccount : public BankAccount 
{
    private:
       int minimum_balance  ;
    
    public:
        SavingBankAccount(){minimum_balance = 1000 ; balance = minimum_balance;}
        bool setBalance(int) ;
        void withdraw(const int) ; 
        void deposit(const int) ;

};

class Client {
    private :
        string name , address , phoneNumber ;
        //BankAccount *pAccount = nullptr ;
    
    public:
        Client(){};
        Client(string name , string address , string phoneNumber){
            this->name = name ;
            this->address = address ;
            this->phoneNumber = phoneNumber ;
        }
        void setName(string);
        void setAddress(string);
        void setPhoneNumber(string);
        string getName() const ;
        string getAddress() const ;
        string getPhoneNumber() const ;
        void print_pretty(const Client&) ;

        friend class BankApplication ;

};

#endif 