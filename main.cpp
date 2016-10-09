
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

/*  This is a cool calculator program by @AdiUltra

    Some Definitions =>
        'E' -> Error
        '-101' -> Error

        pfx -> prefix expression
        prcd -> precedence of the operator

        ANSWER -> previous answer of expression. It can be used as '_' in expressions


    Commented code with //# lines are nice for debugging

    It is essentially quite elegant and extendable.

 */
double ANSWER=0.0;
double E=2.71828182846;
double PI=3.14159265359;

std::vector<double> history;

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
    if (a[0] == '_') {
        return ANSWER;
    } else if (a[0] == 'P') {
        return PI;
    } else if (a[0] == 'e') {
        return E;
    } else {
        return x;
    }
}

void strip(char a[]) {
    int c = 0;
    size_t i;
    for (i = 0; a[i+c] != '\0'; i++) {
        if (a[i+c] == ' ') {
            c++;
        }
        a[i] = a[i+c];
        //# std::cout << a << std::endl;
    }
    a[i++] = '\0';
}

int checkBrackets(char a[]) {
    int fbr = 0, bbr = 0, ck = 0;
    for (size_t i = 0; i < strlen(a); i++) {
        if (a[i] == '(') {
            fbr++;
            ck++;
        } else if (a[i] == ')') {
            bbr++;
            ck--;
            if (ck < 0) {
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

int checkValid(char t) {
    if (t == '*' ||
        t == '+' ||
        t == '-' ||
        t == '/' ||
        t == '%' ||
        t == '^' ||
        t == '(' ||
        t == ')') {

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
        case '%': return int(a1)%int(a2); break;
        case '^': return pow(a1,a2); break;
        default: return -101;
    }
}

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 0;
    } else if (op == '*' || op == '/' || op == '%') {
        return 1;
    } else if (op == '^') {
        return 2;
    } else if (op == '(' || op == ')') {
        return -1;
    } else {
        return 4;
    }
}


class element {
public:
    char type;  // to store wether operator -> 'o' or number -> 'n'

    char op;    // to store operators
    int prcd;   // to store precedence of the operator, greater value for higher precedence

    double value;   // to store value of number


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
        start = last = NULL;
        length = 0;
    }

    void push(element k) {
        element *nn = new element;
        if (k.type == 'o') {
            nn -> op = k.op;
            nn -> prcd = precedence(k.op);
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
        } else if (length != 0 && last->type=='n' && pos == 'l') {
            ret = last->value;
            element *x = last;
            x->prev->next = NULL;
            last = last->prev;
            delete x;
            length--;
        } else if (length != 0 && start->type=='n' && pos == 'f') {
            ret = start->value;
            element *x = start;
            x->next->prev = NULL;
            start = start->next;
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

    int lastPrecedence() {
        if (start != NULL) {
            return last->prcd;
        } else {
            return -101;
        }
    }

    char topOp() {
        if (start != NULL) {
            return start->op;
        } else {
            return 'E';
        }
    }

    int topPrecedence() {
        if (start != NULL) {
            return start->prcd;
        } else {
            return -101;
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

    void empty() {
        element *t = start, *x;
        while (t != NULL) {
            x = t;
            t = t->next;
            delete x;
        }
        start = last = NULL;
        length = 0;
    }

    int len() { return length; }
};

void parse(char a[], MultiStack &pfx) {
    strip(a);
    MultiStack stack;
    char num[20];
    int k = 0;

    for (size_t i = 0; i < strlen(a); i++) {

        if ((a[i] < 58 && a[i] > 47) ||
            a[i] == '.' ||
            a[i] == '_' ||
            a[i] == 'P' ||
            a[i] == 'e') {
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

            element tmp;
            tmp.type = 'o';
            tmp.op = a[i];
            tmp.prcd = precedence(tmp.op);

            if (tmp.op == ')') {
                element k;
                k.op = stack.popOp();
                k.prcd = precedence(k.op);
                k.type = 'o';
                while (k.op != '(' && k.op != 'E') {
                    pfx.push(k);
                    k.op = stack.popOp();
                    k.prcd = precedence(k.op);
                    k.type = 'o';
                }
            } else if (tmp.op == '(') {
                // Do nothing, Just Push
            } else if (tmp.prcd <= stack.topPrecedence()) {
                while (!(tmp.prcd > stack.topPrecedence())) {
                    element k;
                    k.op = stack.popOp();
                    k.prcd = precedence(k.op);
                    k.type = 'o';

                    pfx.push(k);
                }
            }
            if (tmp.op != ')') {
                stack.push(tmp);
            }
        }
        //# std::cout << "PFX: ";
        //# pfx.display();
        //# std::cout << "STACK: ";
        //# stack.display();
    }

    // Transfer all operators left in stack to pfx
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

            if (calc.topType() == 'n') {
                a = calc.popNo('f');

                if (calc.topType() == 'n') {
                    b = calc.popNo('f');
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
            tmp.value = operate(b, a, op);
            tmp.type = 'n';
            calc.push(tmp);
            ret = calc.topNo();
        }

        //# std::cout << "\nPFX: ";
        //# pfx.display();
        //# std::cout << "\nCALC: ";
        //# calc.display();

    }

    if (ret!=-101) {
        ANSWER = ret;
        history.push_back(ANSWER);
    }
    return ret;
}

int commander(char x[]) {
    MultiStack pfx;

    if (!(strcmp(x, "quit")*strcmp(x, "exit")*strcmp(x, "q"))) {
            return 0;

    } else if (!(strcmp(x, "history")*strcmp(x, "hst"))) {

        for (size_t i = 0; i < history.size(); i++) {
            std::cout << i+1 << "\t: " << history[i] << std::endl;
        }
        std::cout << std::endl;

        return 1;

    } else if (!(strcmp(x, "latest")*strcmp(x, "lst"))) {

        if (history.size() > 10) {
            for (size_t i = 0; i < 10; i++) {
                std::cout << i+1 << "\t: " << history[history.size()-10+i] << std::endl;
            }
        } else {
            for (size_t i = 0; i < history.size(); i++) {
                std::cout << i+1 << "\t: " << history[i] << std::endl;
            }
        }
        std::cout << std::endl;

        return 1;
    } else if (!(strcmp(x, "help"))) {
        std::cout << "\n    * You can enter basic math expressions to be evaluated like this :" << std::endl;
        std::cout << " >> 12 + (2 + 1)^3" << std::endl;
        std::cout << "\n      Which will output :" << std::endl;
        std::cout << ":= 39" << std::endl;
        std::cout << "\n    * The previous answer is stored as \'_\' you can use it as :" << std::endl;
        std::cout << " >> _ + _/3" << std::endl;
        std::cout << "\n      Which will evaluate as 39 + 39/3 and output :" << std::endl;
        std::cout << ":= 52" << std::endl;
        std::cout << "\n    * You can also view history of answers by typing \'history\' or \'hst\' :" << std::endl;
        std::cout << " >> hst" << std::endl;
        std::cout << "1        : 39" << std::endl;
        std::cout << "2        : 52" << std::endl;
        std::cout << "    * Or just view the previous 10 answers by typing \'latest\' or \'lst\'" << std::endl;
        std::cout << "\n ## Happy Computing ;p PS when done type \'q\' or \'quit\' to exit" << std::endl;
        return 1;
    } else {
        if (checkBrackets(x)) {
            parse(x, pfx);
        } else {
            std::cout << "Brackets are crazy ;)" << std::endl;
        }

        //# pfx.display();

        double k = evaluate(pfx);
        if (k != -101) {
            std::cout << ":= " <<  k << std::endl << std::endl;
        }
        return 1;
    }
    pfx.empty();

    //# pfx.display();
    //# stack.display();
    //# char a[90] = "x + y + u 98 . 88";
    //# std::cout << a << std::endl;
    //# strip(a);
    //# std::cout << a << std::endl;
}

int main() {

    char x[80];

    std::cout << "\nWelcome to CalcX - a smart calculator" << std::endl;
    std::cout << "Type \'help\' hor help\n" << std::endl;

    while (1) {
        std::cout << " >> ";
        cin.getline(x, 80);
        if (!commander(x)) {
            break;
        }
    }

    return 0;
}
