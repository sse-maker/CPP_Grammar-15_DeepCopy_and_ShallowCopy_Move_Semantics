//
//  main.cpp
//  15_DeepCopy_and_ShallowCopy_Move_Semantics
//
//  Created by 세광 on 2021/07/02.
//

// 이동 시멘틱 -> 이동 생성자, 이동 대입 연산자

#include <iostream>

using namespace std;

class String {
public:
    String() {
        cout << "String(): " << this << endl;
        strData = NULL;
        len = 0;
    }
    
    String(const char *str) {
        cout << "String(const char*): " << this << endl;
        len = strlen(str);
        alloc(len);
        strcpy(strData, str);
    }
    
    // 복사 생성자
    String(const String &rhs) {
        cout << "String(const String&): " << this << endl;
        len = rhs.len;
        alloc(len);
        strcpy(strData, rhs.strData);
    }
    
    String(String &&rhs) {
        cout << "String(String&&): " << this << endl;
        len = rhs.len;
        strData = rhs.strData; // 얕은 복사
        rhs.strData = NULL;
    }
    
    ~String() {
        cout << "~String(): " << this << endl;
        release();
        strData = NULL;
    }
    
    // 복사 대입 연산자
    String &operator=(const String &rhs) {
        cout << "String &operator=(const String&): " << this << endl;
        if(this != &rhs) {
            release();
            len = rhs.len;
            alloc(len);
            strcpy(strData, rhs.strData);
        }
        return *this;
    }
    
    String &operator=(String &&rhs) {
        cout << "String &operator=(String&&): " << this << endl;
        len = rhs.len;
        strData = rhs.strData; // 얕은 복사
        rhs.strData = NULL;
        return *this;
    }
    
    char *GetStrData() const {
        return strData;
    }
    
    int GetLen() const {
        return len;
    }
    
    void SetStrData(const char *str) {
        cout << "void SetStrData(const char*): " << this << ", " << str << endl;
        len = strlen(str);
        alloc(len);
        strcpy(strData, str);
    }
    
private:
    void alloc(int len) {
        strData = new char[len + 1];
        cout << "strData allocated: " << (void*)strData << endl;
    }
    
    void release() {
        delete [] strData;
        if (strData) cout << "strData released: " << (void*)strData << endl;
    }
    
    char *strData;
    int len;
};

String getName() {
    cout << "===== 2 =====" << endl;
    String res("Doodle");
    cout << "===== 3 =====" << endl;
    return res;
}

int main() {
    String a;
    cout << "===== 1 =====" << endl;
    a = getName();
    cout << "===== 4 =====" << endl;
    
    // Rvalue: 우변에만 올 수 있는 값
    // Lvalue: 좌변과 우변에 모두 올 수 있는 값
    // String &&r = getName(); -> &&r: Rvalue 참조자, Rvalue 참조자가 getName()을 참조하고 있음
    // 임시 객체: Rvalue
}
