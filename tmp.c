#include<stdio.h>
#include<stdarg.h>

float average (int n_values, ...);

int main ()
{
    float res = average(5, 1,2,3,4,5);
    printf("%f\n", res);
    float res2 = average(6, 1,2,3,4,5,6);
    printf("%f\n", res2);
    return 0;
}

float average (int n_values, ... )
{
    va_list var_arg;
    int count;
    float sum = 0;

    /* 准备访问可变参数 */
    va_start(var_arg, n_values);

    for (count = 0; count < n_values; count++) {
        sum += va_arg(var_arg, int);
    }

    /* 完成处理可变参数 */
    va_end(var_arg);

    return sum / n_values;
}