#include <iostream>
#include <cstring>

#define as_string( s ) # s
using namespace std;

double ANSWER = 12.5;

void strip(char a[]) {
    int c = 0;
    size_t i;
    for (i = 0; a[i+c] != '\0'; i++) {
        if (a[i+c] == ' ') {
            c++;
        }
        a[i] = a[i+c];
        // std::cout << a << std::endl;
    }
    a[i++] = '\0';
}

void insertAnswer(char a[]) {
    int c = 0, p = 0, condn = 2;

    char b[80], ans[80] = as_string(ANSWER);
    for (size_t i = 0; i < strlen(a); i++) {
        if (a[i] == '_') {
            for (size_t j = i+1; j < strlen(a); j++) {
                b[c++] = a[j];
            }
            b[c++] = '\0';
            std::cout << "b = " << b << "a = " << a << std::endl;
            c = 0;
            cout << strlen(a)+strlen(ans) - 2 << " " << i+strlen(ans)-1 << endl;
            for (size_t qer = strlen(a)+strlen(ans) - 2; qer >= i+strlen(ans)-1; qer--) {
                a[qer] = b[c++];
            }
            a[strlen(a)+strlen(ans)-1] = '\0';
            std::cout << "a = " << a << std::endl;
            for (size_t qw = 0; qw < strlen(ans); qw++) {
                a[i+c++] = ans[qw];
            }
        }
    }

        std::cout << " Cool a = " << a << std::endl;

    std::cout << a << b << std::endl;
}

int main(int argc, char const *argv[]) {
    //for (size_t i = 0; i < 10; i++) {
        char a [800] = "89 + _ + 78";
        strip(a);
        insertAnswer(a);
        std::cout << a << std::endl;
    //    x++;
    //}

    return 0;
}
