#include <iostream>
#include "stack.h"
#include <string>

using namespace std;


struct Result{
    double result;
    bool error;
};


int precedence(char c)
{
    return (c == '+' || c == '-') ? 1 :
           (c == '*' || c == '/') ? 2 :0;
}

bool isOperator(char c)
{
    return precedence(c) != 0;
}



Result evaluate(string input) {
// 1- descomponer el input y validar
    Result per; // salida
    StackArray<char> validar = StackArray<char>(input.length());

    for (char c: input) {
        if (c == '(') {

            validar.push(c);

        }
        else if (c == ')') {

            char pop = validar.pop();
        }
    }


    if (validar.is_empty()) {

        per.error=false;
        // 2- convertir de Infijo a Postfijo

         string postfijo;
         StackArray<char> stack = StackArray<char>(input.length());


         char operador;

        if (isOperator(input[input.length()-1])){
            per.error=true;
            return per;}

        for (char c: input) {

            try {
                if (isOperator(c)) {

                    while (stack.is_empty() &&
                           (operador = stack.top()) != '(' &&
                           precedence(c) <= precedence(operador)) {
                        postfijo += operador;
                        stack.pop();
                    }
                    stack.push(c);
                } else if (c == '(') {

                    stack.push(c);
                } else if (c == ')') {

                    while ((operador = stack.top()) != '(') {
                        postfijo += operador;
                        stack.pop();
                    }
                    stack.pop();

                } else {

                    postfijo += c;
                }
            }
            catch (...) {
                cout << "formato inadecuado del infijo" << endl;

            }
        }

        while (!stack.is_empty()) {
            postfijo += stack.top();
            stack.pop();
        }


        // 3- resolver la expresion
        int n;
        StackArray<float> resultado = StackArray<float>(input.length());

        for (char c: postfijo) {

           if (c =='+'){
               float a = resultado.top();    resultado.pop();
               float b=  resultado.top();    resultado.pop();

               resultado.push(a+b);
           }
           else if (c =='-'){

               float a = resultado.top();    resultado.pop();
               float b=  resultado.top();    resultado.pop();

               resultado.push(b-a);

           }
           else if (c =='*'){

               float a = resultado.top();    resultado.pop();
               float b=  resultado.top();    resultado.pop();

               resultado.push(a*b);

           }
           else if (c =='/'){

               float a = resultado.top();  resultado.pop();
               float b=  resultado.top();  resultado.pop();

               resultado.push(b/a);

           }
           else if (c== ' '){
               // espacio vacio
               }
           else{
               n=c - '0';
                 resultado.push(n);


           }

        }



        per.result=resultado.top();
        return per;
    }

        //* Si no cumple la validacion retornar Result.error = true;

  else
  {

      per.error=true;
      return per;
  }

    return Result();
}
