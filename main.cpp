
#include <iostream>
#include <cstring>

#define as_string( s ) # s


using namespace std;

/*  This is a cool calculator program

    Some Definitions =>
        'E' -> Error

    Commented lines are nice for debugging

 */

double ANSWER=0.0;

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
    a[i++] = '\0';
}

int checkValid(char t) {
    if (t == '*' || t == '+' || t == '-' || t == '/' || t == '%') {
        return 1;
    } else {
        return 0;
    }
}

double operate(double a1, double a2, char op) {
    switch (op) {
        case '+': return a1+a2; break;
        case '-': return a1-a2; break;
        case '*': return a1*a2; break;
        case '/': return a1/a2; break;
        default: return -101;
    }

}


class element {
public:
    char op;
    double value;
    char type;
    element *next;
    element *prev;

    void display() {
        if (type == 'o') {
            std::cout << op << " ";
        } else {
            std::cout << value << " ";
        }
    }
};

class MultiStack {
    element *start;
    element *last;
    int length;
public:
    MultiStack() {
        start = NULL;
        length = 0;
    }
    void push(element k) {
        element *nn = new element;
        if (k.type == 'o') {
            nn -> op = k.op;
        } else {
            nn -> value = k.value;
        }
        nn -> type = k.type;
        nn -> next = NULL;
        nn -> prev = NULL;
        if (start == NULL) {
            start = last = nn;
        } else {
            start -> prev = nn;
            nn -> next = start;
            start = nn;
        }
        length++;
    }

    char popOp(char pos='f') {
        // returns the topmost operator after deleting it from stack
        char ret='E';
        if (length != 0) {

            if (start == last) {
                ret = start->op;
                start = last = NULL;
                length--;
            } else if (pos == 'f') {
                ret = start->op;
                element *t = start->next, *y = start;
                start = t;
                delete y;
                t->prev = NULL;
                length--;
            } else if (pos == 'l') {
                ret = last->op;
                element *x = last;
                x->prev->next = NULL;
                last = last->prev;
                delete x;
                length--;
            }
        }

        return ret;

    }

    double popNo(char pos='l') {
        // returns the topmost operator after deleting it from stack
        double ret = -101;
        if (start == last) {
            ret = start->value;
            start = last = NULL;
            length--;
        } else if (length != 0 && last->type=='n') {
            ret = last->value;
            element *x = last;
            x->prev->next = NULL;
            last = last->prev;
            delete x;
            length--;
        }
        return ret;
    }

    char topType() {
        if (start != NULL) {
            return start->type;
        } else {
            return 'E';
        }
    }

    char lastType() {
        if (last != NULL) {
            return last->type;
        } else {
            return 'E';
        }
    }

    char topOp() {
        if (start != NULL) {
            return start->op;
        } else {
            return 'E';
        }
    }

    double topNo() {
        if (start != NULL) {
            return start->value;
        } else {
            return -101;
        }
    }

    void display() {
        element *t = start;
        while(t != NULL) {
            t->display();
            t = t->next;
        }
        std::cout << std::endl;
    }

    int len() { return length; }
};

void parse(char a[], MultiStack &stack, MultiStack &pfx) {
    strip(a);
    char num[20];
    int k = 0;

    for (size_t i = 0; i < strlen(a); i++) {

        if ((a[i] < 58 && a[i] > 47) || a[i] == 46) {
            num[k++] = a[i];

            if ((i == strlen(a)-1) || checkValid(a[i+1])) {
                num[k] = '\0';
                k = 0;

                element tmp;
                tmp.type = 'n';
                tmp.value = convertDouble(num);

                pfx.push(tmp);
            }
        } else if (checkValid(a[i])) {
            element tmp, emp;
            tmp.type = emp.type = 'o';
            tmp.op = a[i];

            if ((tmp.op == '-' || tmp.op == '+') && (stack.topOp() == '*' || stack.topOp() == '/')) {
                emp.op = stack.popOp();
                while (emp.op != 'E' || stack.topOp() == '*' || stack.topOp() == '/' ) {
                    pfx.push(emp);
                    emp.op = stack.popOp();
                }
            }
            stack.push(tmp);
        }
    }
    element j;
    j.op = stack.popOp();
    j.type = 'o';
    while (j.op != 'E') {
        pfx.push(j);
        j.op = stack.popOp();
    }
}

double evaluate(MultiStack &pfx) {
    MultiStack calc;
    double ret=-101;
    while (pfx.len() != 0) {

        if (pfx.lastType() == 'n') {
            element tmp;
            tmp.value = pfx.popNo();
            tmp.type = 'n';
            calc.push(tmp);
        } else if (pfx.lastType() == 'o') {
            double a, b;
            char op = pfx.popOp('l');
            if (calc.lastType() == 'n') {
                a = calc.popNo();
                if (calc.lastType() == 'n') {
                    b = calc.popNo();
                } else {
                    std::cout << "ERROR : Syntax" << std::endl;
                    ret = -101;
                    break;
                }
            } else {
                std::cout << "ERROR : Syntax" << std::endl;
                ret = -101;
                break;
            }
            element tmp;
            tmp.value = operate(a, b, op);
            tmp.type = 'n';
            calc.push(tmp);
            ret = calc.topNo();
        }

    }

    return ret;
}


int main() {
    MultiStack stack, pfx;

    char x[80];
    while (1) {
        if (!strcmp(x, "quit")*strcmp(x, "exit")) {
            break;
        } else {
            std::cout << " >> ";
            cin.getline(x, 80);

            parse(x, stack, pfx);

            double k = evaluate(pfx);
            if (k != -101) {
                std::cout << k << std::endl;
            }
        }
    }



    // pfx.display();
    // stack.display();
    // char a[90] = "x + y + u 98 . 88";
    // std::cout << a << std::endl;
    // strip(a);
    // std::cout << a << std::endl;
    return 0;
}
