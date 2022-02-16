#include <string.h>
#include <string>
#include <iostream>
#include <string_view>
#include <algorithm>
#include <type_traits>
#include <span>
using namespace std;

struct String {
  String(const char *str = "") : size(strlen(str)), str(new char[size + 1]) {
      strcpy(this->str, str);
  }

  String(size_t n, char c) : size(n), str(new char[n + 1]) {
      memset(this->str, c, n);
      *(this->str + (int)n)  = '\0';
  }

  String(const String &other) : size(strlen(other.str)), str(new char[size + 1]) {
      strcpy(this->str, other.str);
  }

  ~String() {
        delete [] str;
    }

  String &operator=(const String &other) {
       if (this->str != other.str) {
           delete [] str;
           size = strlen(other.str);
           str = new char [size + 1];
           strcpy(this->str, other.str);
       }
       return *this;
   }

     String(String && other) : String() {
     	std::swap(size, other.size);
     	std::swap(str, other.str);
     }

     String &operator=(String && a){
        std::swap(size, a.size);
     	std::swap(str, a.str);
     	return *this;
     }

  void append(String &other) {
      this->size = strlen(other.str) + strlen(this->str);
      char *str1 = new char[size + 1];
      strcpy(str1, this->str);
      strcat(str1, other.str);
      delete [] str;
      this->str = str1;
    }

  char & at(size_t idx) {
      std::cout <<  "1"  << std::endl;
      return str[idx];
      }

  char at(size_t idx) const {
      std::cout <<  "2"  << std::endl;
      return str[idx];
  }

  size_t num() { return this->size; }

  explicit operator char const *() const { return this->str; };

  size_t size;
  char *str;
};

String operator+(const String& str1, const String& str2) {
    char* cp = new char[strlen(str1.str) + strlen(str2.str) + 1];
    strcpy(cp, str1.str);    
    strcat(cp, str2.str);
    return cp;
}

// внутри do_math объекты типа T
// - копируются
// - присваиваются
// - складываются оператором +
template<class T>
void do_math() noexcept(std::is_nothrow_copy_constructible<T>::value
		      && std::is_nothrow_copy_assignable<T>::value
			 && std::is_nothrow_move_assignable<T>::value
			&& std::is_nothrow_move_constructible<T>::value
	       && noexcept(std::declval<T>() + std::declval<T>())
          )
	{ }

int main(){
	bool b1 = noexcept(do_math<int>()); // true
	std::cout <<  b1  << std::endl;
	bool b2 = noexcept(do_math<std::string>()); // false
	std::cout <<  b2  << std::endl;
    String str1("Hello, ");
    String str2("world!");
    String res = str1 + str2;
    cout << res.str << " "  << res.size <<'\n';

//	  String l("left");
//	  String m("middle");
//	  String r("right");
//	  cout << "Default constructor: " << noexcept(String()) << endl;
//	  cout << "Copy constructor: " << noexcept(String(l)) << std::endl;
//	  cout << "Move constructor: " << noexcept(String(std::move(l))) << std::endl;
//
//	  std::cout << "Move constructor: " << std::is_nothrow_move_assignable
//			  <std::add_rvalue_reference<String>::type>::value << std::endl;
//
//	  std::cout << "Assign: " << std::is_nothrow_assignable
//			  <std::add_lvalue_reference<String>::type, std::add_rvalue_reference<String>::type>::value << endl;
//
//	  std::cout << "Move Assign: " << std::is_nothrow_move_assignable
//			  <std::add_rvalue_reference<String>::type>::value << std::endl;
//
//	  std::cout << "Move Assign: " << noexcept(l.operator =(std::move(r))) << std::endl;
//	  std::cout << "Destructor: " << std::is_nothrow_destructible<String>::value << std::endl;
//	  std::cout << "Size: " << noexcept(l.num()) << std::endl;
//	  std::cout << "Clear: " << noexcept(l.clear()) << std::endl;

//	char const * p1 = s;  // 3
//	char const * p2 = (char const*)s;   //4
//	char const * p4 = s.operator const char *();
//	(void)p4;
//	char const * p3 = static_cast<char const*>(s);  // 5
//	char const * s2 = s + 4;  // 6
}




