#include <stdio.h>

int main() {
    int num1=0;
    int num2=0;
    char operator;
    double result=0.0;
    printf("Welcome to the Basic Arithmetic Calculator!\n");
    printf("Enter an operation in the format: number1 operator number2\n");
    printf("Supported operators: + (add), - (subtract), * (multiply), / (divide)\n");
    printf("Enter your calculation:");
    scanf("%d %c %d",&num1,&operator,&num2);
    switch (operator) {
        case '+':
            result = (double)num1 + num2;
            printf("Result: %.2f",result);
            break;
        case '-':
            result =(double) num1 - num2;
            printf("Result:  %.2f",result);
            break;
        case '*':
            result =(double) num1 * num2;
            printf("Result:  %.2f",result);
            break;
        case '/':
            if(num2!=0){
                result = (double)num1 / num2;
                printf("Result:  %.2f",result);
            }else{
                printf("Error: Division by zero is not allowed.");
            }
            break;
        default: printf("Error:Unsupported operator %c .Please use +,-,*,or /.", operator);
    }
//   using if condition
//    if(operator=='+'){
//        result=(double)num1+num2;
//        printf("Result: %.2f",result);
//    }else if(operator=='-'){
//        result=(double)num1-num2;
//        printf("Result:  %.2f",result);
//    }else if(operator=='*') {
//        result = (double)num1 * num2;
//        printf("Result:  %.2f", result);
//    }else if(operator=='/') {
//        if(num2!=0){
//            result = (double)num1 / num2;
//            printf("Result:  %.2f", result);
//        }else{
//            printf("Error: Division by zero is not allowed.");
//        }
//
//    }else{
//        printf("Error:Unsupported operator %c .Please use +,-,*,or /.", operator);
//    }
        return 0;
}
