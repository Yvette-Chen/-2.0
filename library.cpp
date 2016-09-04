#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "library.h"

using namespace std;


//  以下为书籍类的实现 
book::book(string name) {
    this->name = name;
    sum = now = borrow = 0;
}

string book::getBase() { return base; }

string book::getName() { return name; }

void book::setBase(string a) { base = a; }

void book::setSum(int a) { sum = a; }

void book::setNow(int a) { now  = a; }

void book::setBorrow(int a) { borrow = a; }

bool book::operator==(book & other) {
	if(name == other.name) return true;
	else return false;
}

void book::getfile() {
    ifstream file;
    string author, date, ISBN, boname, bodate, botime, borr;
    unsigned int count;
    
    file.open(name.c_str());
    
    file >> name >> author >> date >> ISBN >> sum >> now >> borrow;
    base = name +" " + author + " " + date + " " + ISBN;
    while(!file.eof()) {
        file >> boname >> bodate >> botime >> borr;
        record.push_back(boname);
        record.push_back(bodate);
        record.push_back(botime);
        record.push_back(borr);
    }
    file.close();
    
    count = record.size();
    if(count > 4) {
    	if(record[count - 4] == record[count - 8] && record[count - 3] == record[count - 7]) {
    		if(record[count - 1] == record[count - 5] && record[count - 2] == record[count - 6]) {
    			record.erase(record.end() - 1);
    	        record.erase(record.end() - 1);
    	        record.erase(record.end() - 1);
        	    record.erase(record.end() - 1);
			}	
		}
	}
}

void book::writefile() {
    ofstream out;
    out.open(name.c_str(), ios::trunc);
    out.close();
    fstream file;
    file.open(name.c_str());
    file << base << " " << sum << " " << now << " " << borrow << " ";
    for (int i = 0; i < record.size(); i++) {
        file << record[i++] <<" ";
        file << record[i++] << " ";
        file << record[i++] << " ";
        file << record[i] << " ";
    }
    file.close();
}

//   以下为person类的实现
person::person(string n, string p) {
    name = n;
    password = p;
}

string person::getName() { return name; }

string person::getPassword() { return password; }

//   以下为借阅者类的实现 
borrower::borrower(string name, string a) : person(name, a) {}

int borrower::getBlack() { return black; }

void borrower::setBlack(int a) {
    black = a;
}

int borrower::borrow(vector<book>& bookk, string bookname, string time, string limit) {
    unsigned int i, sum = bookk.size(), res;                    //  默认借书期限为一个月 
    bool flag = false; 
    limit = "一个月";
    for (i = 0; i < sum; i++) {
        if(bookk[i].getName() == bookname) {
            flag = true;
            res = i;
            break;
        }
    }
    if(!flag) return 2;
    if(flag && bookk[res].now == 0) return 1;
    if(flag && bookk[res].now > 0) {
        bookk[res].now--;
        bookk[res].borrow++;
        bookk[res].record.push_back(getName());
        bookk[res].record.push_back(time);
        bookk[res].record.push_back(limit);
        bookk[res].record.push_back("0");
        borrow_record.push_back(bookk[res].name);
        borrow_record.push_back(time);
        borrow_record.push_back("0");
        return 0;
    }
}

int borrower::returnn(vector<book>& bookk, string bookname) {
    unsigned int i, res;                  
    bool flag = false; 
    for (i = 0; i < bookk.size(); i++) {
        if(bookk[i].name == bookname) {
            flag = true;
            res = i;
            break;
        }
    }
    if(!flag) return 1;
    if(flag) {
        for(i = 0; i < bookk[res].record.size(); i += 4) {
            if(getName() == bookk[res].record[i] && bookk[res].record[i+3] == "0") {
                bookk[res].record[i+3] = "1";
                bookk[res].now++;
                bookk[res].borrow--;
                break;
            }
        }
        for(i = 0 ; i < borrow_record.size(); i += 3) {
            if(bookname == borrow_record[i] && borrow_record[i+2] == "0") {
                borrow_record[i+2] = "1";
                break;
            }
        }
        return 0;
    }
}

int borrower::query(vector<book>& bookk, string bookname) {
   int res = -1;
   bool flag = false;
   for(int i = 0; i < bookk.size(); i++) {
       if(bookk[i].name == bookname) {
            flag = true;
            res = i;
            break;
        }
   }
   if(!flag) return res;
   else {
       cout << "本书相关信息" << endl
            << bookk[res].base << endl << "书籍总数：" << bookk[res].sum << "  "
            << "剩余数：" << bookk[res].now << "  " << "借出数：" <<bookk[res].borrow << "  " << endl;
        return res;
   }
}

void borrower::querySelf() {
    cout << "本人借阅记录：" << endl;
    for(int i = 0; i < borrow_record.size(); i++) {
        cout << borrow_record[i++] << "  ";
        cout << "借书日期：" << borrow_record[i++] << "  ";
        if(borrow_record[i] == "0") cout << "未还" << endl;
        if(borrow_record[i] == "1") cout << "已还" << endl;
    }
}

void borrower::findAllbook(vector<book>& bookk) {
    cout << "所有的书籍：" << endl;
    for(int i = 0; i < bookk.size(); i++) cout << bookk[i].getName() << endl;
}
         
int borrower::findbookre(vector<book>& bookk, string bookname) {
   int res = -1;
   bool flag = false;
   for(int i = 0; i < bookk.size(); i++) {
       if(bookk[i].name == bookname) {
            flag = true;
            res = i;
            break;
        }
   }
   if(!flag) return res;
   else {
       cout << "本书相关信息" << endl
            << bookk[res].base << endl << "书籍总数：" << bookk[res].sum << "  "
            << "剩余数：" << bookk[res].now << "  " << "借出数：" <<bookk[res].borrow << "  " << endl;
       cout << "本书的借阅记录：" << endl;     
       for(int i = 0; i < bookk[res].record.size(); i++) {
           cout << "借阅者：" << bookk[res].record[i++];
           cout << "  借阅日期：" << bookk[res].record[i++];
           cout << "  借阅期限：" << bookk[res].record[i++];
           if(bookk[res].record[i] == "1") cout << "  已归还" << endl;
           else if(bookk[res].record[i] == "0") cout << "  未归还" << endl; 
       }
       return res;
   }
}

bool borrower::operator==(borrower & other) {
	if(getName() == other.getName()) return true;
	else return false;
}

void borrower::getfile() {
    string bookname, day, borr, name = getName();
    ifstream file;
    unsigned int count;
    
    file.open(name.c_str());
    file >> name >> black;
    while(!file.eof()) {
        file >> bookname >> day >> borr;
        borrow_record.push_back(bookname);
        borrow_record.push_back(day);
        borrow_record.push_back(borr);
    }
    
    count = borrow_record.size();
    if(count > 3) {
    	if(borrow_record[count - 1] == borrow_record[count - 4] && borrow_record[count - 2] == borrow_record[count - 5]) {
    		if(borrow_record[count - 3] == borrow_record[count - 6]) {
    			borrow_record.erase(borrow_record.end() - 1);
                borrow_record.erase(borrow_record.end() - 1);
                borrow_record.erase(borrow_record.end() - 1);
			}
		}
	}
    file.close();
}

void borrower::writefile() {
    string name = getName();
    ofstream out;
    out.open(getName().c_str(), ios::trunc);
    out.close();
    fstream file;
    file.open(getName().c_str());
    file << name << " " << black << " "; 
    for(int i = 0; i < borrow_record.size(); i++) {
        file << borrow_record[i++] << " ";
        file << borrow_record[i++] << " ";
        file << borrow_record[i] << " ";
    }
    file.close();
}

// 以下为管理者类的实现 
manager::manager (string name, string a) : person(name, a) {}

int manager::helpBorrow(vector<borrower>& borr, vector<book>& bookk, string namee, string bookn, string time, string limit) {
    unsigned int res1, res2;
    bool flag1 = false, flag2 = false; 
    limit = "一个月";
    for(int i = 0; i < borr.size(); i++) {
        if(namee == borr[i].getName()) {
            res1 = i;
            flag1 = true;
            break;
        }
    }
    if(!flag1) return 3;
    for(int i = 0; i < bookk.size(); i++) {
        if(bookn == bookk[i].name) {
            res2 = i;
            flag2 = true;
            break;
        }
    }
    if(!flag2) return 2;
    if(flag2 && bookk[res2].now == 0) return 1;
    if(flag2 && bookk[res2].now > 0) {
        if(borr[res1].getBlack() == 1) limit = "半个月"; 
        bookk[res2].now--;
        bookk[res2].borrow++;
        bookk[res2].record.push_back(namee);
        bookk[res2].record.push_back(time);
        bookk[res2].record.push_back(limit);
        bookk[res2].record.push_back("0");
        borr[res1].borrow_record.push_back(bookk[res2].name);
        borr[res1].borrow_record.push_back(time);
        borr[res1].borrow_record.push_back("0");
        return 0; 
    }
}
      
int manager::helpReturn(vector<borrower>& borr, vector<book>& bookk, string boname, string bookna) {
    unsigned int res1, res2;
    bool flag1 = false, flag2 = false; 
    for(int i = 0; i < borr.size(); i++) {
        if(boname == borr[i].getName()) {
            res1 = i;
            flag1 = true;
            break;
        }
    }
    if(!flag1) return 2;
    for(int i = 0; i < bookk.size(); i++) {
        if(bookna == bookk[i].name) {
            res2 = i;
            flag2 = true;
            break;
        }
    }
    if(!flag2) return 1;
    else {
        for(int i = 0; i < bookk[res2].record.size(); i += 4) {
            if(boname == bookk[res2].record[i] && bookk[res2].record[i+3] == "0") {
                bookk[res2].record[i+3] = "1";
                bookk[res2].now++;
                bookk[res2].borrow--;
                break;
            }
        }
        for(int i = 0 ; i < borr[res1].borrow_record.size(); i += 3) {
            if(bookna == borr[res1].borrow_record[i] && borr[res1].borrow_record[i+2] == "0") {
                borr[res1].borrow_record[i+2] = "1";
                break;
            }
        }
        return 0;
    } 
}

int manager::addBook(vector<book>& bookk, string namee, string base, int sum) {
    for(int i = 0; i < bookk.size(); i++) {
        if(bookk[i].name == namee) return 1;
    }
    book temp(namee);
    ofstream file;
    file.open(namee.c_str());
    temp.setBase(base);
    temp.setBorrow(0);
    temp.setNow(sum);
    temp.setSum(sum);
    bookk.push_back(temp);
    return 0;
}

int manager::deleteBook(vector<book>& bookk, string namee) {
    for(int i = 0; i < bookk.size(); i++) {
        if(bookk[i].name == namee) {
            vector<book>::iterator it = bookk.begin();
            bookk.erase(it + i);
            return 0;
        }
    }
    return 1;
}

int manager::changeBook(vector<book>& bookk, string namee, int sum) {
    for(int i = 0; i < bookk.size(); i++) {
        if(bookk[i].name == namee) {
            bookk[i].sum = sum;
            bookk[i].now = sum - bookk[i].borrow;
            return 0;
        }
    }
    return 1;
}

int manager::query(vector<book>& bookk, string bookname) {
   int res = -1;
   bool flag = false;
   for(int i = 0; i < bookk.size(); i++) {
       if(bookk[i].name == bookname) {
            flag = true;
            res = i;
            break;
        }
   }
   if(!flag) return res;
   else {
       cout << "本书相关信息" << endl
            << bookk[res].base << endl << "书籍总数：" << bookk[res].sum << "  "
            << "剩余数：" << bookk[res].now << "  " << "借出数：" <<bookk[res].borrow << "  " << endl;
       cout << "本书的借阅记录：" << endl;     
       for(int i = 0; i < bookk[res].record.size(); i++) {
           cout << "借阅者：" << bookk[res].record[i++];
           cout << "  借阅日期：" << bookk[res].record[i++];
           cout << "  借阅期限：" << bookk[res].record[i++];
           if(bookk[res].record[i] == "1") cout << "  已归还" << endl;
           else if(bookk[res].record[i] == "0") cout << "  未归还" << endl; 
       }
       return res;
   }
} 

int manager::setBlack(vector<borrower>& borro, string boname) {
    for(int i = 0; i < borro.size(); i++) {
        if(borro[i].getName() == boname) {
            borro[i].setBlack(1);
            return 0;
        }
    }
    return 1;
}

void manager::black(vector<borrower>& borro) {
    cout << "黑名单用户：" << endl;
    for (int i = 0; i < borro.size(); i++) {
        if(borro[i].black) cout << borro[i].getName() << endl;
    } 
}

bool manager::operator==(manager & other) {
	if(getName() == other.getName()) return true;
	else return false;
}

void SignIn(vector<borrower>& borr) {
    string name, password;
    bool flag = false, flag1 = false;
    ofstream file;
    
    cout << "请输入您想要注册的用户名：";
    cin >> name;
    while(!flag) {
        flag1 = false;
        for(int i = 0; i < borr.size(); i++) {
            if(name == borr[i].getName()) {
                flag1 = true;
                break;
            }
        }
        if(flag1) {
            cout << "该用户名已被使用，请重新输入：";
            cin >> name;
        }
        if(!flag1) break;
    }
    cout << "该用户名可使用" << endl;
    cout << "请输入您的密码：";
    cin >> password;
    file.open(name.c_str());
    borrower temp(name, password);
    temp.setBlack(0);
    borr.push_back(temp);
    cout << "注册成功，请返回登陆" << endl;
}

int SignUp(vector<borrower>& borr) {
    string name, password;
    bool flag = false;
    int res;
    
    cout << "请输入您的用户名：";
    cin >> name;
    for(int i = 0; i < borr.size(); i++) {
        if(name == borr[i].getName()) {
            flag = true;
            res = i;
            break;
        }
    }
    
    if(flag) {
        cout << "请输入您的密码：";
        cin >> password;
        if(borr[res].getPassword() == password) return res;
        else return -2;
    } else return -1;  
}
 
int Sign(vector<manager>& mana) {
    string name, password;
    bool flag = false;
    int res;
    
    cout << "请输入管理员的名字：";
    cin >> name;
    for(int i = 0; i < mana.size(); i++) {
        if(name == mana[i].getName()) {
            flag = true;
            res = i;
            break;
        }
    }
    
    if(flag) {
        cout << "请输入您的密码：";
        cin >> password;
        if(mana[res].getPassword() == password) return res;
        else return -2;
    } else return -1;
}
