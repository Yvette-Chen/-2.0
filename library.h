#include <iostream>
#include <string>
#include <vector>

using namespace std; 

class book{
    public:
        friend class borrower;
        friend class manager;
        book() {}
        book(string name);
        string getBase();
        string getName();
        void setBase(string);
        void setSum(int);
        void setNow(int);
        void setBorrow(int);
		bool operator==(book &); 
        void getfile();
        void writefile();
    private:
        string name;   //  书名不允许重复且不允许有空格，本来有了base就不应该再多这个，但是因为book用书名存，为了方便文件读取加上
        string base;  //  这个字符串用于存储关于书名，作者，出版日期，ISBN的书籍信息
        int sum;      //  书籍总数
        int now;      //  现存数量
        int borrow;   //  借出数量
        vector<string> record;  //  四个string一个数据，借阅者，借阅日期，借阅期限（默认一个月），“0”借出，“1”归还 
};

class person{
    public:
        person(){}
        person(string, string);
        string getName();
        string getPassword();
    private:
        string name;  //  用户名 
        string password;   //  密码 
}; 

class borrower : public person{
    public: 
        friend class manager;
        borrower() {}
        borrower(string name, string);
        int getBlack();
        void setBlack(int);
        /*  借书的函数，借到书则返回0，书本全部借出返回1，书名错误返回2,
            参数分别为书籍数据，书名，日期，借阅期限 */ 
        int borrow(vector<book>&, string, string, string);
        //  还书成功返回0，书名错误返回1，参数分别为书籍数据，书名 
        int returnn(vector<book>&, string); 
        /* 查询一本书的记录 ，找到这本书返回这本书的下标，书名错误返回-1，
           参数列表为书籍数据，书名*/ 
        int query(vector<book>&, string);
        //  查询以往借阅记录 
        void querySelf();
        //  查找所有的书籍 
        void findAllbook(vector<book>&);
         /*  查看一本书的借阅记录的函数，找到这本书返回这本书的下标，书名错误返回-1
             参数列表为书籍数据，书名*/
        int findbookre(vector<book>&, string);
        bool operator==(borrower &); 
        //  将文件数据写入                        
        void getfile();
        //  将数据写入文件 
        void writefile();
    private: 
        int black;    //  是否被标记黑名单，0为不是黑名单，1为被标记黑名单 
        vector<string> borrow_record;  //  每三个string即为一个借阅数据，书名，借书日期 ,“0”表示未归还，“1”表示已归还 
};

class manager : public person {
    public:
       manager() {}
       manager (string name, string);
       /*  帮助读者借书的函数，借到书则返回0，书本全部借出返回1，书名错误返回2,借阅者名字错误返回3
           参数分别为借阅者的数据，书籍数据，借阅者的名字，书名，日期，借阅期限 */ 
       int helpBorrow(vector<borrower>&, vector<book>&, string, string, string, string);
       /*  帮助读者还书的函数，还书成功返回0，书名错误返回1，借阅者名字错误返回2 
           参数分别为借阅者数据，书籍数据，借阅者名字，书名 */ 
       int helpReturn(vector<borrower>&, vector<book>&, string, string);
       /*  上架书籍的函数，即为添加一本书，添加成功返回0，如果这本书已经存在返回1
           参数列表分别为书籍数据，书名，基本信息，总数*/ 
       int addBook(vector<book>&, string, string, int);
       /*  下架书籍的函数，即为删除一本书，删除成功返回0，如果这本书已经存在返回1
            参数列表分别为书籍数据，书名*/ 
       int deleteBook(vector<book>&, string);
       /*  修改书籍数量的函数，只能修改总数，不可以修改借出数量，剩余数量随之改动
           修改成功返回0，书名错误返回1 
           参数列表为书籍数据，书名，修改后的书籍总数*/ 
       int changeBook(vector<book>&, string, int);
       /*  查看一本书的借阅记录的函数，找到这本书返回这本书的下标，书名错误返回-1
           参数列表为书籍数据，书名*/
       int query(vector<book>&, string);
       /* 标记黑名单的函数，标记成功返回0，借阅者名字错误返回1
          参数列表为借阅者数据，借阅者名字*/
       int setBlack(vector<borrower>&, string);
       //  查看被标记了黑名单的借阅者名单 
       void black(vector<borrower>&);
       bool operator==(manager &);
};

//  新用户注册 
void SignIn(vector<borrower>&);


//  用户登录，登陆成功返回借阅者数据中的下标，用户名不存在返回-1，密码不正确返回-2 
int SignUp(vector<borrower>&);

// 管理员登陆，登陆成功返回下标，名字错误返回-1，密码不正确返回-2
int Sign(vector<manager>&); 
