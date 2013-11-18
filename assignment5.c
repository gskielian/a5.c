#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 39

/*** Implementation note: Use pointers to process arrays.
No [] operator or index-based access of array elements. ***/



/* Asks the user to enter a number and reads user input
into the provided array of characters, up to 'size' digits.
The array is terminated by a NULL (0) character.
Returns 0 if successful, 1 if user input is longer than 'size' characters.
*/

/*** Implementation note: Probably a good idea to read into a very large array
(for safety) and then refuse to deal with more than 'size' characters. ***/

int read_array(char* number, int size);

/* Converts ASCII digits (character codes '0' through '9', or 48 through 57)
in the provided array to their numerical values, 0 through 9.
Returns 0 if any non-digits are encountered.
Otherwise returns the count of digits in the array.
*/

int convert_ascii_to_decimal(char* number, int size);

/* Reverses the order of characters in the provided array. */

void reverse_array(char* number, int size);

/* Adds two numbers represented as arrays of characters,
each character containing a value between 0 and 9.
The arrays are 'reversed', that is, the least-significant digit
of each number is at the front of the corresponding array.

Places the result in the 'sum' array, and sets
overflow_digit to 0 or 1, depending on the result of the addition.
Returns 0 if invalid values are encountered in the inputs.
Otherwise returns the count of digits in the 'sum' array.
*/

int add_numbers(char* number1, int size1, char* number2, int size2, char* sum, int sum_size, int* overflow_digit);

/* Converts decimal values, 0 through 9, to ASCII digits (character codes '0' through '9')
in the provided array.
*/

void convert_decimal_to_ascii(char* number, int size);

/* Prints the provided array of characters. */

void print_array(char* number, int size);

/* If condition is false (0), prints the 'message' and exits the program with an error code. */

void ensure(int condition, char* message);



int main() {

	char number1[MAX_SIZE + 1], number2[MAX_SIZE + 1], sum[MAX_SIZE];
	int size1, size2, sum_size;
	int overflow_digit;
	int r;

	/*char n1[] = "1", n2[]= "99", s[]="xx";

	convert_ascii_to_decimal(n1, 1);
	convert_ascii_to_decimal(n2, 2);
	
	add_numbers(n1, 1, n2, 2, s, 2, &overflow_digit);
	convert_decimal_to_ascii(n1, 1);
	convert_decimal_to_ascii(n2, 2);
	convert_decimal_to_ascii(s, 2);
	printf("%s + %s = %s, overflow = %d\n", n1, n2, s, overflow_digit);

	return 0; */

	/* Read the two numbers.
 	Accept any strings of characters, as long as they fit into the arrays.
 	*/

	r = read_array(number1, MAX_SIZE);
	ensure(r == 0, "The number you entered is too long.\n");
	r = read_array(number2, MAX_SIZE);
	ensure(r == 0, "The number you entered is too long.\n");

	/* Convert to numeric values, and determine array sizes in the process. */
	size1 = convert_ascii_to_decimal(number1, MAX_SIZE);
	ensure(size1 != 0, "The number contains something other than digits.\n");
	size2 = convert_ascii_to_decimal(number2, MAX_SIZE);
	ensure(size1 != 0, "The number contains something other than digits.\n");

	/* At this point, we have number1 with size1 digits and number2 with size2 digits.
	Reverse the order of digits in each to allow for an easier addition to follow.
	*/
	reverse_array(number1, size1);
	reverse_array(number2, size2);

	/* Now add them. */
	sum_size = add_numbers(number1, size1, number2, size2, sum, MAX_SIZE,  &overflow_digit);
	if (overflow_digit == 1)
		printf("There has been an overflow.\n");

	/* Reverse the order of 'sum' back to readable form. */
	reverse_array(sum, sum_size);

	/* Convert the bytes of 'sum' to printable digits. */
	convert_decimal_to_ascii(sum, sum_size);

	/* Print the value of 'sum'. */
	printf("The sum is: ");
	print_array(sum, sum_size);
	printf("\n");

	return EXIT_SUCCESS;
}

int read_array(char* number, int size) {
  char reading[100], *p;
  printf("Enter the number: ");
  scanf("%s", reading);
  p = reading;
  int i;
  for(i = 0; i < size + 1; i++){
    //putchar(*(p+i));
    if(*(p + i) == '\0'){
      *(number + i) = *(p + i); //we should still add the stop bit -- it helps track size of number
      return 0;
    }
    else{
      *(number + i) = *(p + i);
      
    }
  }

  return 1;

}

int convert_ascii_to_decimal(char* number, int size) {
  char *p, decimal;
  p = number;
  int i;
  for (i = 0; i <size; i++){
  //before converting, make sure that the character is a digit
    if(*p > 47 && *p < 58){

    //convert to decimal
    decimal = *p - '0';
    //stores it to the array
    *p = decimal;
    p++;
    }
    else if(*p == '\0'){
      return i;
    }
    else{
 
      return 0;   
    }
   
  }
  return 999;

}

void reverse_array(char* number, int size) {
  char *p, temp;
  int  i;
  p = number;
    for (i = 0; i < size/2; i++){
      temp =  *(p+i);
      *(p+i) = *(p+size-1-i);
      *(p+size-1-i) = temp;
  }
}

int add_numbers(char* number1, int size1, char* number2, int size2, char* sum, int sum_size, int* overflow_digit) {
  int i, dig1, dig2, dig3, total, carry = 0;
  char *p, *q;
  p = number1;
  q = number2;

  for (i = 0; i < sum_size; i++){
  if((p-number1) >= size1){
    dig1 = 0;
    p++;
  }
  else{
    dig1 = *p++;
  }
  if((q-number2) >= size2){
    dig2 = 0;
    q++;
  }
  else{
    dig2 = *q++;
  }
    total = dig1 + dig2 + carry;
    printf("%d = %d + %d + %d\n", total, dig1, dig2, carry);
    carry = total/10;

    dig3 = total%10;

    *sum++ = dig3;
   }
   *overflow_digit = carry;

	return size1;

}
void convert_decimal_to_ascii(char* number, int size) {
  char *p;
  int i;
  p = number;
  for(i = 0; i< size; i++){
    if(*p >= 0 && *p <= 9){
    *number = *p + '0';
    number++;
    p++;
    }
  }
}

void print_array(char* number, int size) {
  int i;
  putchar('\n');
  for (i =0; i < size; i++){
    if(*(number+i) != '\0'){
    putchar(*(number + i));
    }
    else {
    break;
    }
  }
  putchar('\n'); 
}

void ensure(int condition, char* message) {
	if (!condition) {
		printf(message);
		exit(EXIT_FAILURE);
	}
}
