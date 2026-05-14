#include <iostream>
#include <string>
#include <ctime>    
#include <iomanip> 
#include <windows.h>
using namespace std;

const int MAX_ADMINS = 2;
const int MAX_BOOKS = 100;
const int MAX_USERS = 100;
const int MAX_BORROWED = 3;

int bookCount = 0;
int adminCount = 0;
int userCount = 0;

const int SECONDS_PER_DAY_SIMULATION = 5; 
const int MAX_DAYS_ALLOWED = 2; 
const int FINE_PER_DAY = 50;   

void printHeader() {
 cout<<"                                       ==========================================";
 cout<<"\n                                        _      _  _";                          
 cout<<"\n                                       | |    (_)| |   ";                      
 cout<<"\n                                       | |     _ | |__   _ __   __ _  _ _  _   _ ";
 cout<<"\n                                       | |    | || '_ ) |  __| / __ ||  _|| | | |";
 cout<<"\n                                       | |___ | || |_) )| |   | (_| || |  | |_| |";
 cout<<"\n                                       |_____||_||_.__/ |_|   |_ ___||_|  |___, |";
 cout<<"\n                                                                            __/ |";
 cout<<"\n                                                                           |___/ ";
 cout<<"\n                                       =========================================="<<endl;
}


void loadingBar() {
    cout<< "Processing: ";
    for (int i = 0; i < 20; i++){
        cout << char(219);
        Sleep(30);
    }
    cout << endl;
}

void printMenuItem(int number, string text) {
    cout<< "||"<< " " << number << ". " << left << setw(30) << text<< " ||"<< endl;
}

int getIntegerInput() {
    int input;
    while (true) {
        cout <<">> ";
        cin >> input;
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            cout <<"     Invalid input! Enter a number given in choices."<< endl;
        } else {
            cin.ignore(1000, '\n'); 
            return input;
        }
    }
}

class Book {
private:
    string title;
    string author;
    string ISBN;

public:
    Book() {}
    Book(string t, string a, string isbn) : title(t), author(a), ISBN(isbn) {}

    string getTitle() const {
	 return title; 
	 }
    string getAuthor() const { 
	return author; 
	}
    string getISBN() const {
	 return ISBN;
	  }
};

Book books[MAX_BOOKS];

void sortTheBooks(){
    for (int i = 0; i <bookCount - 1; ++i) {
        for (int j = 0; j< bookCount - 1 - i; ++j) {
            if (books[j].getISBN() > books[j + 1].getISBN()) {
                Book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}

class Person {
protected:
    string name;     
    string password; 

    void displayBooksAvailable() {
        sortTheBooks();
        cout << "\n"<< "--- AVAILABLE LIBRARY INVENTORY ---"<< endl;
        cout<<"+-"<<string(10, '-')<<"-+-"<<string(25, '-')<<"-+-"<<string(20, '-')<<"-+"<<endl;
        cout<<"| " << left << setw(10) << "ISBN" 
             << " | " << setw(25) << "Title" 
             << " | " << setw(20) << "Author" << " |"<< endl;
        cout<< "+-" << string(10, '-') << "-+-" << string(25, '-') << "-+-" << string(20, '-') << "-+" <<endl;

        for (int i = 0; i < bookCount; i++) {
            cout << "| " << left << setw(10) << books[i].getISBN() 
                 << " | " << setw(25) << books[i].getTitle().substr(0, 24)
                 << " | " << setw(20) << books[i].getAuthor().substr(0, 19) << " |" << endl;
        }
        cout<< "+-" << string(10, '-') << "-+-" << string(25, '-') << "-+-" << string(20, '-') << "-+"<< endl;
    }
        
public:
    Person() {} 
    virtual void showDashboard() = 0; 
    string getName() const {
	 return name;
	  }
    string getPassword() const {
	 return password; 
	 }
};

class Admin : public Person {
public:
    Admin() {}
    Admin(string n, string p) {
	 name = n; 
	 password = p;
	  } 

    void showDashboard() override {
        while (true) {
            cout << endl << "Logged in as: " << name << endl;
            cout << "+---------- ADMIN DASHBOARD ---------+" << endl;
            printMenuItem(1, "Add Book");
            printMenuItem(2, "Remove Book");
            printMenuItem(3, "View All Books");
            printMenuItem(4, "View User Borrow History");
            printMenuItem(5, "Logout");
            cout << "+------------------------------------+" << endl;
            cout << "Select Option ";

            int adminChoice = getIntegerInput();
            if (adminChoice == 1){
            addBook();	
			}
            else if (adminChoice == 2){
            	 removeBook();
			}
			
            else if (adminChoice == 3) {
            		displayBooks();
			}
		
            else if (adminChoice == 4){
            	 viewAllUserHistory();
			}
			
            else if (adminChoice == 5){
            		break;
			} 
		
        }
    }

    void viewAllUserHistory(); 

    void addBook() {
        string title, author, isbn;
        cout << "\n"<< "--- ADD NEW BOOK ---"<< endl;
        cout << "Enter Title : "; 
		getline(cin, title);
        cout << "Enter Author: ";
		 getline(cin, author);
        cout << "Enter ISBN  : ";
		 getline(cin, isbn);

        loadingBar();
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getISBN() == isbn) {
                cout <<" ! Error: ISBN collision."<< endl;
                return;
            }
        }
        if (bookCount >= MAX_BOOKS) {
            cout<< " ! Error: Library Full."<< endl;
            return;
        }
        books[bookCount++] = Book(title, author, isbn);
        sortTheBooks();
        cout<< " OK Book added successfully!"<< endl;
    }

    void removeBook() {
        cout<< "--- REMOVE BOOK ---" <<endl;
        cout << "Enter ISBN to remove: ";
        string isbn; 
		getline(cin, isbn);
        loadingBar();
        int index = -1;
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getISBN() == isbn) { 
			index = i;
			 break;
			  }
        }
        if (index == -1) {
            cout<< " ! Book not found."<<endl;
            return;
        }
        for (int i = index; i < bookCount - 1; ++i){
		
		 books[i] = books[i + 1];
        --bookCount;
    }
        sortTheBooks();
        cout<< " OK Book removed!"<< endl;
    }

    void displayBooks() {
	 Person::displayBooksAvailable();
	  }
};

class User : public Person {
private:
    string id;
    string borrowedISBNs[MAX_BORROWED];
    time_t issueDates[MAX_BORROWED]; 
    int borrowCount;

public:
    User() : borrowCount(0) {}
    User(string uid, string uname, string pwd) : id(uid), borrowCount(0) { 
	name = uname;
	 password = pwd; 
	 }

    string getID() const {
	 return id; 
	 }
    int getBorrowCount() const { 
	return borrowCount;
	 }
    string getBorrowedISBN(int idx) const { 
	return borrowedISBNs[idx];
	 }

    void showDashboard() override {
        while (true){
            cout << endl << "Welcome, " << name << endl;
            cout << "+----------- USER DASHBOARD ---------+" << endl;
            printMenuItem(1, "View Library Inventory");
            printMenuItem(2, "Search Book (ISBN)");
            printMenuItem(3, "Issue Book");
            printMenuItem(4, "Return Book");
            printMenuItem(5, "My Borrowed Books");
            printMenuItem(6, "Logout");
            cout << "+------------------------------------+" << endl;
            cout << "Select Option ";

            int userChoice = getIntegerInput();
            if (userChoice == 1) {
            	displayBooks();
			}
            else if (userChoice == 2){
                cout << "Search ISBN: "; 
				string isbn;
				 getline(cin, isbn);
                if (!searchBook(isbn)){
				 cout << "Not Found." << endl;
			}
            }
            else if (userChoice == 3) {
                cout << "Issue ISBN: ";
				 string isbn; 
				 getline(cin, isbn);
                issueBook(isbn);
            }
            else if (userChoice == 4) {
                cout << "Return ISBN: ";
				 string isbn;
				  getline(cin, isbn);
                returnBook(isbn);
            }
            else if (userChoice == 5){
			viewBorrowedBooks();
		}
            else if (userChoice == 6){
			break;
		}
        }
    }

    bool hasBorrowed(const string &isbn) const {
        for (int i = 0; i < borrowCount; ++i){
		 if (borrowedISBNs[i] == isbn)
		  return true;
        return false;
    }
    }

    void issueBook(const string &isbn) {
        loadingBar();
        if (borrowCount >= MAX_BORROWED) {
		 cout<< " Limit reached (Max 3)."<< endl;
		  return; 
		  }
        int idx = -1;
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getISBN() == isbn) {
			 idx = i;
			  break; 
			  }
        }
        if (idx < 0 || hasBorrowed(isbn)) {
		 cout <<"  Not available or already borrowed."<< endl;
		  return;
		   }

        borrowedISBNs[borrowCount] = isbn;
        issueDates[borrowCount] = time(0); 
        borrowCount++;

        for (int i = idx; i < bookCount - 1; ++i)
		 books[i] = books[i + 1];
        --bookCount;
        sortTheBooks();
        cout <<" OK Issued successfully." << endl;
    }

    void returnBook(const string &isbn) {
        loadingBar();
        int idx = -1;
        for (int i = 0; i < borrowCount; ++i) {
		 if (borrowedISBNs[i] == isbn) { 
		 idx = i;
		  break;
		   } }
        if (idx < 0) {
		 cout<< " You don't have this book."<< endl;
		  return; 
		  }

        time_t now = time(0);
        int daysPassed = (int)difftime(now, issueDates[idx]) / SECONDS_PER_DAY_SIMULATION; 
        
        if (daysPassed > MAX_DAYS_ALLOWED) {
            cout<< "  OVERDUE! Fine: " << (daysPassed - MAX_DAYS_ALLOWED) * FINE_PER_DAY << " PKR"<< endl;
        }

        books[bookCount++] = Book("Returned Book", "Library System", isbn);
        sortTheBooks();
        borrowedISBNs[idx] = borrowedISBNs[borrowCount - 1];
        issueDates[idx] = issueDates[borrowCount - 1];
        borrowCount--;
        cout<< " OK Book Returned." <<endl;
    }

    void viewBorrowedBooks() const {
        cout<< "\n--- MY BORROWED BOOKS & LIVE FINES ---"<< endl;
        time_t now = time(0);
        for (int i = 0; i < borrowCount; ++i) {
            int daysPassed = (int)difftime(now, issueDates[i]) / SECONDS_PER_DAY_SIMULATION;
            cout << " [" << i+1 << "] ISBN: " << borrowedISBNs[i];
            if (daysPassed > MAX_DAYS_ALLOWED) 
                cout << " (OVERDUE - Fine: " << (daysPassed - MAX_DAYS_ALLOWED) * FINE_PER_DAY << " PKR)";
            else cout << " (Status: On Time)";
            cout << endl;
        }
        if (borrowCount == 0) 
		cout << "No books borrowed" << endl;
    }

    bool searchBook(const string &isbn) {
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getISBN() == isbn) {
                cout<< " FOUND: " << books[i].getTitle() << " by " << books[i].getAuthor()<< endl;
                return true;
            }
        }
        return false;
    }
    void displayBooks() { 
	Person::displayBooksAvailable();
	 }
};

void Admin::viewAllUserHistory() {
    extern User users[];
    for (int i = 0; i < userCount; ++i) {
        cout << "User: " << users[i].getName() << " | ID: " << users[i].getID() << endl;
        if (users[i].getBorrowCount() == 0) 
		cout << "  (No books)" << endl;
        else
		 for (int j = 0; j < users[i].getBorrowCount(); ++j)
            cout << "  - " << users[i].getBorrowedISBN(j) << endl;
    }
}

User users[MAX_USERS];
Admin admins[MAX_ADMINS];

int main() {
   admins[adminCount++] = Admin("admin", "admin123");
    users[userCount++] = User("0677", "azan", "azan123");
    users[userCount++] = User("0711", "aftab", "aftab123");
    books[bookCount++] = Book("C++ Programming", "Bjarne Stroustrup", "ISBN001");
    books[bookCount++] = Book("Effective Java", "Joshua Bloch", "ISBN002");
    books[bookCount++] = Book("Clean Code", "Robert C. Martin", "ISBN003");
    sortTheBooks();
    while (true) {
        printHeader(); 
        cout<< "+=====================================+"<< endl;
        cout<< "               MAIN MENU"<< endl;
        cout<< "+=====================================+"<< endl;
        printMenuItem(1, "Admin Login");
        printMenuItem(2, "User Portal");
        printMenuItem(3, "Exit");
        cout<< "+=====================================+"<< endl;
        
        int choice = getIntegerInput(); 
        Person* currentUser = NULL;

        if (choice == 1) {
            string username, password;
            cout << "Admin Name : ";
			 getline(cin, username);
            cout << "Password: ";
			 cin >> password;
			 cin.ignore();
            for (int i = 0; i < adminCount; ++i) {
                if (admins[i].getName() == username && admins[i].getPassword() == password)
				 currentUser = &admins[i];
            }
        }
        else if (choice == 2) {
            cout << "Have an account? (y/n): ";
			 char has;
			  cin >> has;
			   cin.ignore();
            if (tolower(has) == 'n') {
                if (userCount >= MAX_USERS) 
				cout << "Full." << endl;
                else {
                    string uid, uname, pwd;
                    cout << "New 4-digit ID: "; 
					getline(cin, uid);
                    cout << "Name: "; 
					getline(cin, uname);
                    cout << "Password: "; 
					cin >> pwd;
					 cin.ignore();
                    users[userCount++] = User(uid, uname, pwd);
                    currentUser = &users[userCount - 1];
                    cout << " Registered!" << endl;
                }
            } else {
                string uid, pwd;
                cout << "User ID : ";
				 getline(cin, uid);
                cout << "Password: ";
				 cin >> pwd; 
				 cin.ignore();
                for (int i = 0; i < userCount; ++i) {
                    if (users[i].getID() == uid && users[i].getPassword() == pwd) 
					currentUser = &users[i];
                }
            }
        }
        else if (choice == 3)
		 break;
		 
        if (currentUser) 
		currentUser->showDashboard(); 
        else if (choice != 3)
		 cout << " Login Failed." << endl;
    }
    return 0;
}
