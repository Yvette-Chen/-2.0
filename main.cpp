#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "library.h"

using namespace std;

int main() {
	vector<book> bookk;
	vector<borrower> borr;
	vector<manager> mana;
	ifstream file;
	ofstream out;
    fstream f; 
	string bookname, boname, maname, password, temp, date, author, ISBN, base;
	int choice, res, choice1, choice2 = 0, borrowres, returnres, queryres, sum, addres, deres;
	unsigned int count;
	bool flag1, flag2;
		
	file.open("书名数据");
    while(!file.eof()) {
        file >> bookname;
        book temp(bookname);
        temp.getfile();
        bookk.push_back(temp);
    }
    bookk.erase(bookk.end() - 1);
    file.close();

    file.open("借阅者数据");
    while(!file.eof()) {
        file >> boname >> password;
        borrower temp(boname, password);
        temp.getfile();
        borr.push_back(temp);
    }
    file.close();
    
    file.open("管理者数据");
    while(!file.eof()) {
        file >> maname >> password;
        manager temp(maname, password);
        mana.push_back(temp);
    }
    file.close();
    
    count = bookk.size();
    if(count > 1) {
    	if(bookk[count - 1] == bookk[count - 2]) bookk.erase(bookk.end() - 1);
	}
    
	count = borr.size();
	if(count > 1) {
		if(borr[count - 1] == borr[count - 2]) borr.erase(borr.end() - 1);
	}
    
    count = mana.size();
    if(count > 1) {
    	if(mana[count - 1] == mana[count - 2]) mana.erase(mana.end() - 1);
	}
    
    cout <<"---------------------------------------------------------" << endl; 
    cout << "欢迎使用图书馆系统" << endl;
    cout << "1：新用户注册  2：旧用户登陆  3：管理员登陆  4：退出系统" << endl;
    cout << "请输入您的选择：";
    cin >> choice;
    
    while(choice > 4 || choice < 1) {
        cout << "您输入了错误的指令，请重新输入：";
        cin >> choice; 
    }
    
    while(choice != 4) {
        
        if(choice == 1) {
            SignIn(borr);
        }
        
        if(choice == 1 || choice == 2) {
            
            while(1) {
                res = SignUp(borr);
                if(!(res == -1 || res == -2)) {
                    cout << "登陆成功" << endl;
                    break;
                } else if(res == -1){
                    cout << "用户名不存在" << endl;
                    cout << "重新登陆请输入0，退出系统输入1：";
                    cin >> choice1;
                    while(!(choice1 == 0 || choice1 == 1)) {
                        cout << "您输入了错误的指令，请重新输入：";
                        cin >> choice1; 
                    }
                    if(choice1 == 1) break;
                } else if(res == -2) {
                    cout << "密码不正确" << endl;
                    cout << "重新登陆请输入0，退出系统输入1：";
                    cin >> choice1;
                    while(!(choice1 == 0 && choice1 == 1)) {
                        cout << "您输入了错误的指令，请重新输入：";
                        cin >> choice1; 
                    }
                    if(choice1 == 1) break; 
                }
            }
            
            if(choice1 == 1) {
                choice = 4;
                break;
            }
            
            while(choice2 != 7) {
                cout <<"---------------------------------------------------------" << endl;
                cout << "1：借书  2：还书  3：查询书本  4：查询本人借阅记录  5：查找所有书籍" << endl
                     << "6：查询一本书的借阅记录  7：退出" <<endl; 
                cout << "请输入您的指令：";
                cin >> choice2;
                while(choice2 > 7 || choice2 < 1) {
                    cout << "您输入了错误的指令，请重新输入：";
                    cin >> choice2;
                }
                
                if(choice2 == 1) {
                    cout << "请输入您要借的书的书名：";
                    cin >> bookname;
                    cout << "输入借书的日期" << endl;
                    cout << "年："; cin >> temp;
                    date = date + temp + "年";
                    cout << "月："; cin >> temp;
                    date = date + temp + "月";
                    cout << "日："; cin >> temp;
                    date = date + temp + "日";
                    if(borr[res].getBlack() == 0) {
                        borrowres = borr[res].borrow(bookk, "书名：" + bookname, date, "一个月");
                    } else {
                        borrowres = borr[res].borrow(bookk, "书名：" + bookname, date, "半个月");
                    }
                    if(borrowres == 0) cout << "借书成功" << endl;
                    if(borrowres == 1) cout << "该本书已经被全部借出" << endl;
                    if(borrowres == 2) cout << "您输入的书名错误" << endl; 
                }
                
                if(choice2 == 2) {
                    cout << "请输入您还书的书名：";
                    cin >> bookname;
                    returnres = borr[res].returnn(bookk, "书名：" + bookname);
                    if(returnres == 0) {
                        cout << "还书成功" << endl;
                    } else if(returnres == 1) {
                        cout << "您输入的书名错误" << endl;
                    }
                }
                
                if(choice2 == 3) {
                    cout << "请输入您需要查询的书名：";
                    cin >> bookname;
                    queryres = borr[res].query(bookk, "书名：" + bookname);
                    if(queryres == -1) cout << "您输入的书名错误" << endl; 
                } 
                
                if(choice2 == 4) {
                    borr[res].querySelf();
                }
                
                if(choice2 == 5) {
                    borr[res].findAllbook(bookk);
                }
                
                if(choice2 == 6) {
                    cout << "输入需要查询的书名：";
                    cin >> bookname;
                    addres = mana[res].query(bookk, "书名：" + bookname);
                    if(addres == -1) cout << "书名错误" << endl;
                }
                
                if(choice2 == 7) {
                    choice = 4;
                    break;
                }
            }
        }
        
        if(choice == 3) {
            while(1) {
                res = Sign(mana);
                if(!(res == -1 || res == -2)) {
                    cout << "登陆成功" << endl;
                    break;
                } else if(res == -1){
                    cout << "用户名不存在" << endl;
                    cout << "重新登陆请输入0，退出系统输入1：";
                    cin >> choice1;
                    while(!(choice1 == 0 || choice1 == 1)) {
                        cout << "您输入了错误的指令，请重新输入：";
                        cin >> choice1; 
                    }
                    if(choice1 == 1) break;
                } else if(res == -2) {
                    cout << "密码不正确" << endl;
                    cout << "重新登陆请输入0，退出系统输入1：";
                    cin >> choice1;
                    while(!(choice1 == 0 || choice1 == 1)) {
                        cout << "您输入了错误的指令，请重新输入：";
                        cin >> choice1; 
                    }
                    if(choice1 == 1) break; 
                }
            }
            
            if(choice1 == 1) {
                choice = 4;
                break;
            }
            
            while(choice2 != 9) {
                cout <<"---------------------------------------------------------" << endl;
                cout << "1：帮助借阅  2：帮助归还  3：上架书籍  4：下架书籍" << endl
                     << "5：修改书的数量  6：标记黑名单  7：查询一本书的借阅记录" << endl
                     << "8：查询被标记了黑名单的借阅者  9：退出系统" << endl; 
                cout << "请输入您的指令：";
                cin >> choice2;
                while(choice2 > 9 || choice2 < 1) {
                    cout << "您输入了错误的指令，请重新输入：";
                    cin >> choice2;
                }
                
                if(choice2 == 1) {
                    cout << "请输入借阅者的名字：";
                    cin >> boname;
                    cout << "请输入书籍的名字：";
                    cin >> bookname;
                    cout << "输入借书的日期" << endl;
                    cout << "年："; cin >> temp;
                    date = date + temp + "年";
                    cout << "月："; cin >> temp;
                    date = date + temp + "月";
                    cout << "日："; cin >> temp;
                    date = date + temp + "日";
                    borrowres = mana[res].helpBorrow(borr, bookk, boname, "书名：" + bookname, date, "一个月");
                    if(borrowres == 0) cout << "借书成功" << endl;
                    if(borrowres == 1) cout << "该本书已被全部借出" << endl;
                    if(borrowres == 2) cout << "书名错误" << endl;
                    if(borrowres == 3) cout << "借阅者用户名字错误" << endl; 
                }
                
                if(choice2 == 2) {
                    cout << "请输入借阅者的名字：";
                    cin >> boname;
                    cout << "请输入书籍的名字：";
                    cin >> bookname;
                    returnres = mana[res].helpReturn(borr, bookk, boname, "书名：" + bookname);
                    if(returnres == 0) cout << "还书成功" << endl;
                    if(returnres == 1) cout << "您输入的书名错误" << endl;
                    if(returnres == 2) cout << "您输入的借阅者名字错误" << endl;
                }
                
                if(choice2 == 3) {
                    cout << "请输入您上架的书籍名：";
                    cin >> bookname;
                    bookname = "书名：" + bookname;
                    cout << "请输入作者名字：";
                    cin >> author;
                    author = "作者：" + author;
                    cout << "请输入出版日期" << endl;
                    cout << "年："; cin >> temp;
                    date = date + temp + "年";
                    cout << "月："; cin >> temp;
                    date = date + temp + "月";
                    cout << "日："; cin >> temp;
                    date = "出版日期" + date + temp + "日";
                    cout << "请输入ISBN编号：";
                    cin >> ISBN;
                    ISBN = "ISBN：" + ISBN;
                    base = bookname + " " + author + " " + date + " " + ISBN;
                    cout << "请输入该书的总数：";
                    cin >> sum;
                    addres = mana[res].addBook(bookk, bookname, base, sum);
                    if(addres == 0) cout << "上架成功" << endl;
                    if(addres == 1) cout << "本书已存在" << endl;
                }
                
                if(choice2 == 4) {
                    cout << "请输入需要删除的书籍名：";
                    cin >> bookname;
                    deres = mana[res].deleteBook(bookk, "书名：" + bookname);
                    if(deres == 0) cout << "下架成功" << endl;
                    if(deres == 1) cout << "书名错误" << endl; 
                }
                
                if(choice2 == 5) {
                    cout << "请输入需要修改的书籍名：";
                    cin >> bookname;
                    cout << "请输入修改后的书籍总数";
                    cin >> sum;
                    addres = mana[res].changeBook(bookk, "书名：" + bookname, sum);
                    if(addres == 0) cout << "修改成功" << endl;
                    if(addres == 1) cout << "书名错误" << endl; 
                }
                
                if(choice2 == 6) {
                    cout << "请输入被标记黑名单的借阅者名字：";
                    cin >> boname;
                    addres = mana[res].setBlack(borr, boname);
                    if(addres == 0) cout << "标记成功" << endl;
                    if(addres == 1) cout << "借阅者名字错误" << endl;
                }
                
                if(choice2 == 7) {
                    cout << "输入需要查询的书名：";
                    cin >> bookname;
                    addres = mana[res].query(bookk, "书名：" + bookname);
                    if(addres == -1) cout << "书名错误" << endl;
                }
                
                if(choice2 == 8) {
                    mana[res].black(borr);
                }
                
                if(choice2 == 9) {
                    choice = 4;
                    break;
                }
            }
        }
        
        if(choice == 4) {
            cout << "欢迎下次使用" << endl;
            break;
        }
    }
    
    out.open("书名数据", ios::trunc);
    out.close();
    f.open("书名数据");
    for(int i = 0; i < bookk.size(); i++) {
        f << bookk[i].getName() << " ";
        bookk[i].writefile();
    }
    f.close();
    
    out.open("借阅者数据", ios::trunc);
    out.close();
    f.open("借阅者数据");
    for(int i = 0; i < borr.size(); i++) {
        f << borr[i].getName() << " " <<borr[i].getPassword() << " ";
        borr[i].writefile();
    }
    f.close();
    
    out.open("管理者数据", ios::trunc);
    out.close();
    f.open("管理者数据");
    for(int i = 0; i < mana.size(); i++) {
    	f << mana[i].getName() << " " << mana[i].getPassword() << " ";
	}
	f.close();
	
    return 0;
}
