/* This program calculates the Key for two persons 
using the Diffie-Hellman Key exchange algorithm */
#include<stdio.h> 
#include<math.h> 

// Power function to return value of a ^ b mod P 
long long int power(long long int a, long long int b, 
									long long int P) 
{ 
	if (b == 1) 
		return a; 

	else
		return (((long long int)pow(a, b)) % P); 
} 

//Driver program 
int main() 
{ 
	 long long int P, G, x, a, y, b,z,c, kaM,kbM,kbJ,kcJ,kaF,kcF,Sa,Sb,Sc; 
	

		// public keys G and P 
	P = 53; // A prime number P is taken 
	printf("The value of P : %lld\n", P); 

	G = 2; // A primitve root for P, G is taken 
	printf("The value of G : %lld\n\n", G); 


	a = 6; // a is the chosen private key 
	printf("The private key a for JuanMa : %lld\n", a); 
	x = power(G, a, P); // gets the generated key 
	

	b = 5; // b is the chosen private key 
	printf("The private key b for Felipe : %lld\n\n", b); 
	y = power(G, b, P); // gets the generated key 
	
	c= 7; // a is the chosen private key 
	printf("The private key a for Mayra : %lld\n", c); 
	z = power(G, c, P);
	printf("-------: %lld,%lld,%lld\n", x,y,z); 




	//MAYRA-------
	kaM = power(x, c, P); // jUANMA 	kaM,kbM,kbJ,kcJ,kaF,kcF
	kbM = power(y, c, P); //FELIPE
	printf("1 %lld^ %lld - %lld=%lld \n",x,c,P,kaM); 
	printf("1.1 %lld^ %lld - %lld=%lld \n", y,c,P,kbM);
	
	//JUANMA
	kbJ = power(y, a, P); //FELIPE
	kcJ = power(z, a, P); //MAYRa
	printf("2 %lld^ %lld - %lld=%lld \n",y,a,P,kbJ); 
	printf("2.1 %lld^ %lld - %lld=%lld \n", z,a,P,kcJ);
	
	//felipo
	kaF = power(x, b, P); //FELIPE
	kcF = power(z, b, P); //MAYRa
	printf("3 %lld^ %lld - %lld=%lld \n",x,b,P,kaF); 
	printf("3.1 %lld^ %lld - %lld=%lld \n", z,b,P,kcF);
	
	Sa = power(kbJ, c, P); //FELIPE
	Sb = power(kbM, a, P);
	Sc = power(kcJ, b, P);

	printf("\n\n %lld^ %lld - %lld=%lld \n",kbJ, c, P, Sa); 
	printf(" %lld^ %lld - %lld=%lld\n",kbM, a, P, Sb);
	printf(" %lld^ %lld - %lld=%lld\n", kcJ, b, P,Sc); 
	
	return 0; 
} 
