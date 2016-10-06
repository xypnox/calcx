#include <iostream>
#include <cstring>

#define as_string( s ) # s
using namespace std;

double ANSWER = 12.5;

int checkBrackets(char a[]) {
    int fbr = 0, bbr = 0, ck = 0;
    for (size_t i = 0; i < strlen(a); i++) {
        if (a[i] == '(') {
            fbr++;
            ck++;
        } else if (a[i] == ')') {
            bbr++;
            ck--;
            if (ck != 0) {
                bbr = 56;
                break;
            }
        }

    }
    if (fbr == bbr) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char const *argv[]) {
    //for (size_t i = 0; i < 10; i++) {
    char a [800] = "89+  + 78";

    std::cout << checkBrackets(a) << std::endl;
    //    x++;
    //}

    return 0;
}
