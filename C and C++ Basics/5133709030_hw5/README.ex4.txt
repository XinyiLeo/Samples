1.Details of the Karatsuba algorithm:
    When claculating the product of two large numbers ,the Karatsuba 
    algorithm separate the two numbers into two parts respectively.
    Then procceed three calclations. In this algorithm, the number are peeled
    layer by layer(recursion). Then apply the formula: a*b=2^(N_n)*2^n+2^x*(z2*y0+x0)+x0*y0

3.Efficiency  
    3.1 Use N-n and n instead of N and n to decrease the procedure of multiplication.
    3.2 Calculation baed on 2 can increase the efficiency.

4. Advanced function
    if (tR <= 32) 
     {
     AsmMulLL(pL, pR, pA, b, a);
     return;
      }

     unsigned long t = b / a;
     if (t >= 2) 
      {
     unsigned long * pT = new unsigned long[2 * b];

     for (unsigned long i = 0; i < t; i ++)
     {
     AsmMemZero(pT, 2 * b);
     AsmAddLL(pT, pA + i * b, pA + i * b, 2 * b); } 