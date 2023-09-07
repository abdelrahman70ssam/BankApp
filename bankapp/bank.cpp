#include "bank.h"

void BankApplication::run(){   
        
        cout << "Welcome to FCAI Banking Application" << endl ; 
        cout << "Create a New Account -> press button 1" << endl; 
        cout << "List Clients and Accounts -> press button 2 " << endl ;
        cout << "Withdraw Money -> press button 3 " << endl ;
        cout << "Deposit Money -> press button 4 " << endl ;
        cout << "press button \"0\" to exit application" << endl ;
        cout << endl ;
            while (true)
            {
                int choice ;
                cout << "enter your choice " << endl ;
                cin >> choice ; 

                if(choice == 1){
                  create_new_acc();
                }
                if(choice == 2){
                    list_clients_and_accounts(file) ;
                }
                if(choice == 3){
                    withdraw_app();
                }
                if(choice == 4){
                    deposit_app();
                }
                if (choice == 0)
                {
                    cout << "Thank you for using FCAI Banking Application . :) " << endl ;
                    break;
                }
            }
}


void BankApplication::create_new_acc()
{
    Client user ;
    string name , address , phone ;
    
    cout << "please enter your name :-  " << endl;
    //getline(cin,name) ;
    cin >> name ;
    user.setName(name) ; 
    
    cout << "please enter your address :-  " << endl ;
   // getline(cin,address) ;
    cin >> address ;
    user.setAddress(address) ; 
    
    cout << "please enter your phone number :-  " << endl;
    //getline(cin,phone) ;
    cin >> phone ;
    user.setPhoneNumber(phone) ; 

    int type ;
    cout << "What Type of Account Do You Like? (1) Basic (2) Saving ? Type 1 or 2 -->" ;
    cin >> type ;

    if(type == 1){
        BankAccount account ;
        int money ;
        cout << "Please Enter the Starting Balance =========> "  ;
        cin >> money ;
        if(account.setBalance(money)){
            account.setID();
            cout << "An account was created with ID FCAI-" << account.getID() ;
            cout << " and Starting Balance " << account.getBalance() << " L.E" << endl ;
            cout << "Account type is basic " << endl ; 
            cout << "_______________________" << endl ;

            link_add_basic(user, account) ;
        } 
    }
        
    else{
        BankAccount *pAccount = new SavingBankAccount ;
        int money ;
        cout << "Please Enter the Starting Balance =========>"  ;
        cin >> money ;
        if(pAccount->setBalance(money)){
            pAccount->setID();
            cout << "An account was created with ID FCAI-" << pAccount->getID() << ' ' ;
            cout << " and Starting Balance " << pAccount->getBalance() << " L.E" << endl ;
            cout << "Account type is saving" << endl ; 
            cout << "_______________________" << endl ;
            
            link_add_saving(user , pAccount ) ;
            delete pAccount ;
         }
        
    }

}


void BankApplication::link_add_basic (Client& user ,BankAccount& acc  )
{
    
    accounts_list.push_back(std::move(make_pair(user , acc )));
    
    fstream file("UsersInfo.txt") ;

    if(!file.is_open()){
        cout << "File not exist" << endl ;
        return ;
    }
        
            file << "ID " << acc.getID() << endl;
            file << "basic account " << endl;
            file << "Name -> " << user.getName() << endl ; 
            file << "address -> " << user.getAddress() << endl ; 
            file << "Phone Number -> " << user.getPhoneNumber() << endl ; 
            file << "balance -> " << acc.getBalance() << endl ; 
            file << "___________________________________________" << endl ;
            file.close() ;
    

   

}

void BankApplication::link_add_saving(Client& user , BankAccount* s_acc  )
{
    if(s_acc != NULL){
        accounts_list.push_back(std:: move(make_pair(user , *s_acc ))) ;
    }

    if(!file.is_open()){
        cout << "File not exist" << endl ;
        return ;
    }

    if(s_acc != NULL){
       
            file << "ID " << s_acc->getID() << endl;
            file << "saving account " << endl;
            file << "Name -> " << user.getName() << endl ; 
            file << "address -> " << user.getAddress() << endl ; 
            file << "Phone Number -> " << user.getPhoneNumber() << endl ; 
            file << "balance -> " << s_acc->getBalance() << endl ; 
            file << "___________________________________________" <<endl ;
            file.close() ;
        
    }
     

}


void  BankApplication:: list_clients_and_accounts(fstream& file)
    {
        string line ;
        while (getline(file,line))
        {
            cout << line << endl;
        }
        
    }

BankAccount BankApplication::find_account_basic(const vector<pair<Client , BankAccount >>& vbasic)
{
    int id_num ;
    cout << "enter your ID number :- " ;
    cin >> id_num ;  
    BankAccount temp ;
    for (auto &&i : vbasic)
    {
        if(i.second.index == id_num){
            cout << "Account found successfully . " << endl ;
            temp.index = id_num ;
            temp.balance = i.second.balance;
            
            break;
        }
    }
    return temp;
}


SavingBankAccount BankApplication::find_account_saving(const vector<pair<Client , BankAccount>>& vSaving)
{
    
    int id_num ;
    cout << "enter your ID number :- " ;
    cin >> id_num ;  
    SavingBankAccount temp ;
    for (auto &&i : vSaving)
    {
        if(i.second.index == id_num){
            cout << "Account found successfully . " << endl ;
            temp.index = id_num ;
            temp.balance = i.second.balance ;
            break;
        }
    }
    return temp ;
}


void BankApplication::withdraw_app(){
    int type ;
    cout << "enter type of your account ,(1) Basic (2) Saving ? Type 1 or 2 --> " ;
    cin >> type ;
    if(type == 1){
        BankAccount obj = find_account_basic(accounts_list);
        int money ;
        cout << "enter amaount of money you want to withdraw from your account -> " ;
        cin >> money ;
        obj.withdraw(money);
        } 
    else{
        SavingBankAccount obj = find_account_saving(accounts_list) ;
        int money ;
        cout << "enter amaount of money you want to withdraw from your account -> " ;
        cin >> money ;
        obj.withdraw(money);
    }
}

void BankApplication::deposit_app(){
    int type ;
    cout << "enter type of your account ,(1) Basic (2) Saving ? Type 1 or 2 --> " ;
    cin >> type ;
    if(type == 1){
        BankAccount obj = find_account_basic(accounts_list);
        int money ;
        cout << "enter amount of money you want to deposit in your account -> " ;
        cin >> money ;
        obj.deposit(money);
        } 
    else{
        SavingBankAccount obj = find_account_saving(accounts_list) ;
        int money ;
        cout << "enter amaount of money you want to deposit in your account -> " ;
        cin >> money ;
        obj.deposit(money);
    }
}




int BankAccount:: index = 0 ;
void BankAccount:: setID(){  index++ ;} 
bool BankAccount:: setBalance(int balance){ if(balance > 0){this->balance = balance ; return true;} return false;} 
int BankAccount:: getID() const {return index  ;} 
int BankAccount:: getBalance() const { return balance ;} 

void BankAccount:: withdraw(const int amount )
{
    // displayinfo() ; friend 
    if(amount > balance){
        cout << "Sorry. This is more than what you can withdraw " << endl ;
    }
    else{
        balance -= amount ;
        cout << "Successful Transaction " << endl ;
    }

    cout << "Your current Balance is : " << balance << endl ;
    cout << "_________________________" << endl;
}

void BankAccount:: deposit(const int amount)
{
    // displayinfo() ; friend 
    if(amount < 0){
        cout << "Sorry  Transacion failed  " << endl ;
    }
    else{
        balance += amount ;
        cout << "Successful Transaction " << endl ;
    }

    cout << "Your current Balance is : " << balance << endl ;
    cout << "_________________________" << endl;;
}

bool SavingBankAccount:: setBalance(int amount)
{   
    if(amount >= minimum_balance){
        balance =  amount ;
        cout << "Successful Transaction " << endl ;
        return true ;
    }
    cout << "Transaction failed :(" << endl;
    cout << "Balance should be 1000 or more " << endl;
    cout << "_________________________" << endl;
    
    return false ;

}

void SavingBankAccount::deposit (const int amount)
{   
    if(amount >= 100){
        balance += amount ;
        cout << "Successful Transaction " << endl ;
         cout << "Your current Balance is : " << balance << endl ;
        return ;
    }
    cout << "Transaction failed :(" << endl;
    cout << "Amount should be 100 or more " << endl;
    cout << "_________________________" << endl;

}

void SavingBankAccount::withdraw (const int amount)
{   
    if(balance - amount >= minimum_balance){
        balance -= amount ;
        cout << "Successful Transaction " << endl ;
         cout << "Your current Balance is : " << balance << endl ;
        return ;
    }
    cout << "Transaction failed :(" << endl;
    cout << "You can not withdraw money below minimum balance (1000) " << endl;
    cout << "_________________________" << endl;

}



void Client::setName(string name){this-> name = name ;}
void Client::setAddress(string address){this-> address = address ;}
void Client::setPhoneNumber(string phoneNumber){this-> phoneNumber = phoneNumber ;}
string Client::getName() const{return name ;}
string Client::getAddress() const{return address ;}
string Client::getPhoneNumber() const{return phoneNumber ;}  




