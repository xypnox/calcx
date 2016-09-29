#include <iostream>
#include <cstring>

using namespace std;

/*  This is a cool calculator program

    Some Definitions =>
        'E' -> Error

    Commented lines are nice for debugging

 */

double convertDouble(char a[]) {
    // This Fxn Converts a char to double
    // It neglects all alphabets
    // It can also handle decimals
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
    // std::cout << c << std::endl;
    a[i++] = '\0';
}

int checkValid(char t) {
    if (t == '*' || t == '+' || t == '-' || t == '/' || t == '%') {
        return 1;
    } else {
        return 0;
    }
}


struct element {
    char op;
    double value;
    char type;
    element *next;
};

class MultiStack {
    element *start;
public:
    MultiStack() {
        start = NULL;
    }
    void push(element k) {
        element *nn = new element;
        nn -> op = k.op;
        nn -> value = k.value;
        nn -> type = k.type;
        nn -> next = NULL;
        if (start == NULL) {
            start = nn;
        } else {
            nn -> next = start;
            start = nn;
        }
    }

    element pop() {
        // reurns the topmos operator after deleting it from stack
        if (start != NULL) {
            element x = *start;
            start = start -> next;
            return x;
        }
    }

    element top() {
        if (start != NULL) {
            element n = *start;
            return n;
        }
    }

    void display() {
        element *t = start;
        while(t != NULL) {
            if (t->type == 'o') {
                std::cout << t->op << " ";
            } else if (t->type == 'n') {
                std::cout << t->value << " ";
            }
            t = t->next;
        }
        std::cout << std::endl;
    }
};

void parse(char a[], MultiStack &stack, MultiStack &pfx) {
    strip(a);
    char num[20];
    int k = 0;

    for (size_t i = 0; i < strlen(a); i++) {

        if ((a[i] < 58 && a[i] > 47) || a[i] == 46) {
            std::cout << "found number" << std::endl;
            num[k++] = a[i];

            if ((i == strlen(a)-1) || checkValid(a[i+1])) {
                num[k] = '\0';
                k = 0;

                element tmp;
                tmp.type = 'n';
                tmp.value = convertDouble(num);

                pfx.push(tmp);
                // pfx.display();
            }
        } else if (checkValid(a[i])) {
            // std::cout << "Hi" << std::endl;
            element tmp;
            tmp.type = 'o';
            tmp.op = a[i];

            stack.push(tmp);
            // stack.display();
        }
    }
}

int main() {
    MultiStack stack, pfx;

    char x[80];
    std::cout << " >> ";
    cin.getline(x, 80);

    parse(x, stack, pfx);

    pfx.display();
    stack.display();


    // char a[90] = "x + y + u 98 . 88";
    // std::cout << a << std::endl;
    // strip(a);
    // std::cout << a << std::endl;
    return 0;
}
