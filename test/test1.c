int fib(int n)
{
  return (n == 1) ? 1 : (n == 0) ? 0 : fib(n-1) + fib(n-2);
}

void _start()
{
  main();
  __asm("ecall");
}

int main()
{
  int i, sum, sum1, sum2;
  int slt_test;
  int f;
  unsigned int op1 = 50, op2 = 101;

  f = fib(30);
  sum1 = 0;
  for(i = 1; i < 37; i++)
    sum1 += i;

  sum1 = sum >> 1;
  sum1 = sum1 | 333;
  op1  = op1 < (op2 >> 1);

  slt_test = (sum1 < 100);

  for(i = 36; i >=0; i--)
    sum2 += i;

  sum2 = sum2 >> 1;

  sum = sum1 + sum2 + slt_test;
  sum += f;
  return sum;
}
