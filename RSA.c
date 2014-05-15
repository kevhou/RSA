#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int len = 0;
int text[100000];

// Main Menu
int menu(){
    // Initial Selection
    int selection = 0;

    // Menu Selection
    printf("\nMENU\n");
    printf("1. Create encryption & decryption keys\n");
    printf("2. RSA Encryption (Key needed)\n");
    printf("3. RSA Decryption (Key needed)\n");
    printf("4. Help\n");
    printf("5. Exit\n");

    // Receive Selection
    printf("\nSelect: ");
    scanf("%d", &selection);

    return selection;
}

// Find the Greatest Common Divisor between two numbers
int gcd(int num1, int num2){
    int temp;

    while(num2 > 0){
      temp = num1 % num2;
      num1 = num2;
      num2 = temp;
    }
     
    return num1;
}

// d = (1/e) mod n
int mod_inverse(int u, int v)
{
    int inv, u1, u3, v1, v3, t1, t3, q;
    int iter;
    /* Step X1. Initialise */
    u1 = 1;
    u3 = u;
    v1 = 0;
    v3 = v;
    /* Remember odd/even iterations */
    iter = 1;
    /* Step X2. Loop while v3 != 0 */
    while (v3 != 0)
    {
        /* Step X3. Divide and "Subtract" */
        q = u3 / v3;
        t3 = u3 % v3;
        t1 = u1 + q * v1;
        /* Swap */
        u1 = v1; v1 = t1; u3 = v3; v3 = t3;
        iter = -iter;
    }
    /* Make sure u3 = gcd(u,v) == 1 */
    if (u3 != 1)
        return 0;   /* Error: No inverse exists */
    /* Ensure a positive result */
    if (iter < 0)
        inv = v - u1;
    else
        inv = u1;
    return inv;
}



// Check if the input number is a prime number or not
bool check_prime(num){

    if(num == 0 || num == 1){
        return false;
    }

    // Return true if the number can only divide 1 and itself
    for(int i = 2; i < num; i++){
        if (num % i == 0 && i != num){
            return false;
        }
    }
    
    return true;
}

// Check if input e is valid
bool check_e(e, phi){

    // e and phi must have gcd of 1, 1 < e < phi
    if(gcd(e,phi) == 1 && e > 1 && e < phi){
        return true;
    } else{
        return false;
    }
}

// The Modular Exponentiation Algorithm
int MEA(int p, int e, int n){
 
  int r2 = 1;
  int r1 = 0;
  int Q = 0;
  int R = 0;
 
  while( e != 0 ){
     R = (e % 2);
     Q = ((e - R) / 2);
 
     r1 = ((p * p) % n);
 
       if(R == 1){
          r2 = ((r2 * p) % n);
       }
     p = r1;
     e = Q;
  }
return r2;
}

// Received input from user
void encode(e,n){
  int i = 0;

  int c = getchar();
  do{
    c = getchar();
    text[i] = MEA(c, e, n);
    len++;
    i++;
  }while(c != '\n');

  i = 0;  
  len -= 1;
  printf("\n*************************************\n");
  for(int i = 0; i < len; i++){ /* print until we've hit \0 */
    printf("  Ciphered text C%d: %d\n", i+1, text[i]);
  }
}

void decode(d,n){
  printf("\n");

  for(int i = 0; i < len; i++){
    printf("Ciphered text C%d: ", i+1);
    scanf("%d", &text[i]);
    text[i] = MEA(text[i], d, n);
  }

  printf("\n*************************************");
  printf("\n   Deciphered text: ");
  for(int i = 0; i < len; i++){
    printf("%c", text[i]);
  }
}

void clear_input(){
  // Clears the text array
  memset(text,0,sizeof(text));
  len = 0;
}

int main(){

    // Header style
    printf("\n");
    printf("***************************************************\n");
    printf("*                                                 *\n");
    printf("*       RSA (Encryption/ Decryption) Program      *\n");
    printf("*              Created by: Kevin Hou              *\n");
    printf("*                                                 *\n");
    printf("***************************************************\n");

    int selection = 0;
    int p = 0; // Prime 1
    int q = 0; // Prime 2
    int n = 0; // n = p * q;
    int e = 0; // Public exponent
    int d = 0; // d = (1/e) mod (phi)
    int phi = 0; // (p - 1) * (q - 1)

    bool valid_input = true;

    // Menu Choices
    while(selection != 5){

        int selection = menu();

        // Creat public key
        if(selection == 1){

            do{
              printf("\nEnter the first prime number: ");
              scanf("%d", &p);

              if(check_prime(p) == false){
                valid_input = false;

                printf("The number entered is not a prime number. Try again.\n");
              } else {
                valid_input = true;
              }

            }while(valid_input == false);

            do{
              printf("\nEnter the second prime number: ");
              scanf("%d", &q);

              if(check_prime(q) == false){
                valid_input = false;
                printf("The number entered is not a prime number. Try again.\n");
              } else {
                valid_input = true;
              }

            }while(valid_input == false);
            
            n = p * q;
            phi = (p-1)*(q-1);
            

            // For testing (Shows value of n & phi)
            // printf("\nn is equal to: %d\n", n);
            // printf("\nphi is equal to: %d\n", phi);

            do{
              printf("\nEnter a value for public exponent 'e': ");
              scanf("%d", &e);

              if(check_e(e,phi) == false){
                valid_input = false;
                printf("The 'e' value is not compatible. Try again.\n");
              } else {
                valid_input = true;
              }

            }while(valid_input == false);

            d = mod_inverse(e, phi);

            //printf("\nd is equal to: %d\n", d);
            printf("\n*************************************\n");
            printf("  Public encryption key: \n");
            printf("    e = %d\n", e);
            printf("    n = %d\n", n);

            printf("\n");

            printf("  Private decryption key: \n");
            printf("    d = %d\n", d);
            printf("    n = %d", n);
            printf("\n*************************************\n");
        } else if(selection == 2){
            printf("\nEnter the public encryption key: \n");
            printf("Enter 'e' value: ");
            scanf("%d", &e);
            printf("Enter 'n' value: ");
            scanf("%d", &n);

            printf("\nEnter text to be encrypted: ");

            encode(e,n);
            
            printf("\n  Total number of characters: %d", len);
            clear_input();
            printf("\n*************************************\n");
        } else if(selection == 3){
            printf("\nEnter the private decryption key: \n");
            printf("Enter 'd' value: ");
            scanf("%d", &d);
            printf("Enter 'n' value: ");
            scanf("%d", &n);

            printf("\nEnter the number of characters in the encrypted text: ");
            scanf("%d", &len);

            decode(d,n);
            clear_input();
            printf("\n*************************************\n");
        }else if(selection == 4){
            printf("***************************************************\n");
            printf("Instructions:\n\n");

            printf("   Create encryption & decryption keys:\n");
            printf("   1. Enter two distinctive (greater than 10)\n");
            printf("      primes p and q\n");
            printf("   2. Enter an integer e so that gcd(e,phi(n)) = 1\n");
            printf("   3. Use the Public encryption key to encrypt\n");
            printf("      messages.\n");
            printf("   4. Use the Private decryption key to decrypt\n");
            printf("      messages.\n\n");

            printf("   RSA Encryption:\n");
            printf("   1. Enter e and n values in the Public encryption\n");
            printf("      key\n");
            printf("   2. Enter message to be encrypted (< 100000 chars)\n");
            printf("   3. Record the ciphered text info\n");
            printf("   4. Record the number of characters in the text\n\n");

            printf("   RSA Decryption:\n");
            printf("   1. Enter d and n values in the Private decryption\n");
            printf("      key\n");
            printf("   2. Enter the number of chars in the encrypted text\n");
            printf("   3. Enter the each chars in the encrypted text\n\n");
            printf("***************************************************\n");
        } else if(selection == 5){
            break;
        }
    }
}


