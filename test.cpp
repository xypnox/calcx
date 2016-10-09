#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

// double ANSWER = 12.5;
//
// int checkBrackets(char a[]) {
//     int fbr = 0, bbr = 0, ck = 0;
//     for (size_t i = 0; i < strlen(a); i++) {
//         if (a[i] == '(') {
//             fbr++;
//             ck++;
//         } else if (a[i] == ')') {
//             bbr++;
//             ck--;
//             if (ck < 0) {
//                 bbr = 56;
//                 break;
//             }
//         }
//
//     }
//     if (fbr == bbr) {
//         return 1;
//     } else {
//         return 0;
//     }
// }

vector<double> history;

int main(int argc, char const *argv[]) {
    //for (size_t i = 0; i < 10; i++) {
    // char a [800] = "89+  + 78";
    for (size_t i = 0; i < 5; i++) {
        history.push_back(i);
    }

    for (size_t i = 0; i < 5; i++) {
        std::cout << history[i] << std::endl;
    }

    std::cout << history.size() << std::endl;
    // std::cout << checkBrackets(a) << std::endl;
    //    x++;
    //}

    return 0;
}
