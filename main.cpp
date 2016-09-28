#include <iostream>
#include <cstring>

using namespace std;

double convertDouble(char a[]) {
    double x = 0.0;
    double m = 10, n = 1; // to change when '.' is found
    for (size_t i = 0; i < strlen(a); i++) {
        char k = a[i];
        if (k < 58 && k > 47) {
            x = x*m + k%48*n;
            if (n < 1.0) {
                n*= 0.1;
            }
        } else if (k == 46) {
            m = 1;
            n = 0.1;
        }
    }
    return x;
}

struct nums {
    double value;
    nums *next;
};

class StackOperands {
    nums *start;
public:
    StackOperands() {
        start = NULL;
    }
    void push(int n) {
        nums *nn = new nums;
        nn -> value = n;
        nn -> next = NULL;
        if (start == NULL) {
            start = nn;
        } else {
            nn -> next = start;
            start = nn;
        }
    }
    double pop() {
        if (start != NULL) {
            double k = start -> value;
            nums *x = start;
            start = start -> next;
            delete x;

            return k;
        } else {
            return 'E';
        }
    }
    void display() {
        nums *t = start;
        while(t != NULL) {
            std::cout << t -> value << " ";
            t = t->next;
        }
        std::cout << std::endl;
    }
};

int checkValid(char t) {
    if (t == '*' || t == '+' || t == '-' || t == '/' || t == '%') {
        return 1;
    } else {
        return 0;
    }
}

struct operators {
    char ops;
    operators *next;
};

class StackOperators {
    operators *start;
public:
    StackOperators() {
        start = NULL;
    }
    void push(char op) {
        if (checkValid(op)) {
            operators *nn = new operators;
            nn -> ops = op;
            nn -> next = NULL;
            if (start == NULL) {
                start = nn;
            } else {
                nn -> next = start;
                start = nn;
            }
        } else {
            std::cout << "Operator Invalid" << std::endl;
        }
    }
    char pop() {
        if (start != NULL) {
            char k = start -> ops;
            operators *x = start;
            start = start -> next;
            delete x;

            return k;
        } else {
            return 'E';
        }
    }
    void display() {
        operators *t = start;
        while(t != NULL) {
            std::cout << t -> ops << " ";
            t = t->next;
        }
        std::cout << std::endl;
    }
};


void parse(){
    // to be done
}

int main() {
    char a[] = "0.001";
    std::cout << convertDouble(a)*2 << std::endl;
    return 0;
}
