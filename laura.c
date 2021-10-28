PHASE 1

void phase_1(char* string)
{
  int result;
  
  result = strings_not_equal(string,"Public speaking is very easy.");
  if (result != 0) {
    explode_bomb();
  }
  return;
}

Answer = Public speaking is very easy.


PHASE 2

void phase_2(char* string)
{
  int index;
  int numberArray[7];
  
  read_six_numbers(string, numberArray + 1);
  if (numberArray[1] != 1) {                                            -> first number must be 1
    explode_bomb();
  }
  index = 1;
  do {
    if (numberArray[index + 1] != (index + 1) * numberArray[index]) {   -> start to compare from the second number (index + 1)
      explode_bomb();                                                  
    }
    index = index + 1;
  } while (index < 6);
  return;
}

Base on the code the first number must be 1, the subsequence number will be base on the formula "numberArray[index + 1] != (index + 1) * numberArray[index]"
numberArray[1] = 1
numberArray[1 + 1] = (1 + 1) * 1 -> numberArray[2] = 2
numberArray[2 + 1] = (2 + 1) * 2 -> numberArray[3] = 6
numberArray[3 + 1] = (3 + 1) * 6 -> numberArray[4] = 24
numberArray[4 + 1] = (4 + 1) * 24 -> numberArray[5] = 120
numberArray[5 + 1] = (5 + 1) * 120 -> numberArray[2] = 720

Answer = 1 2 6 24 120 720


PHASE 3

void phase_3(char* string)
{
  int inputCount;
  char c;
  uint number1;
  char char1;
  int number2;
  
  inputCount = sscanf(string,"%d %c %d",&number1,&char1,&number2);    -> get 1 number, 1 char, 1 number from command line input
  if (inputCount < 3) {
    explode_bomb();
  }
  switch(number1) {
    case 0:
      c = 'q';
      if (number2 != 0x309) {
        explode_bomb();
      }
      break;
    case 1:
      c = 'b';
      if (number2 != 0xd6) {                                          -> 0xd6 = 214
        explode_bomb();
      }
      break;
    case 2:
      c = 'b';
      if (number2 != 0x2f3) {                                         -> 0x2f3 = 755
        explode_bomb();
      }
      break;
    case 3:
      c = 'k';
      if (number2 != 0xfb) {
        explode_bomb();
      }
      break;
    case 4:
      c = 'o';
      if (number2 != 0xa0) {
        explode_bomb();
      }
      break;
    case 5:
      c = 't';
      if (number2 != 0x1ca) {
        explode_bomb();
      }
      break;
    case 6:
      c = 'v';
      if (number2 != 0x30c) {
        explode_bomb();
      }
      break;
    case 7:
      c = 'b';
      if (number2 != 0x20c) {                                         -> 0x20c = 524
        explode_bomb();
      }
      break;
    default:
      c = 'x';
      explode_bomb();
  }
  if (c != char1) {
    explode_bomb();
  }
  return;
}

Base on the README hint, the 3 password should contain 'b' as the second character, so possible answer should be:
1 b 214
2 b 755
7 b 524


PHASE 4

void phase_4(char* string)
{
  int inputCount;
  int inputNumber;
  
  inputCount = sscanf(string,"%d",&inputNumber);            -> scan 1 number
  if ((inputCount != 1) || (inputNumber < 1)) {             -> must be 1 input
    explode_bomb();
  }
  inputCount = func4(inputNumber);
  if (inputCount != 0x37) {                                 -> 0x37 = 55
    explode_bomb();
  }
  return;
}

int func4(int inputNumber)
{
  int nb1;
  int nb2;
  
  if (inputNumber < 2) {
    nb2 = 1;
  }
  else {
    nb1 = func4(inputNumber + -1);
    nb2 = func4(inputNumber + -2);
    nb2 = nb2 + nb1;
  }
  return nb2;
}

Phase_4 will get a number as input and will go through func4 recursive function to translate it into another number
The result of that shoulde be 0x37 or 55, since its a recursive function, it will be easier if we run the compile the code and test it.
Answer = 9


PHASE 5

void phase_5(char* inputString)
{
  int number;
  char* string[6];
  int unused;
  
  number = string_length(inputString);
  if (number != 6) {                                                                -> check if inputString is 6 char
    explode_bomb();
  }
  number = 0;
  char*  array123= "isrveawhobpnutfg"
  do {
    string[number] = (&array123)[(char)(*(byte *)(number + inputString) & 0xf)];    -> (char)(*(byte *)(number + inputString) is the same as inputString[number]
    number = number + 1;                                                               inputString[number] & 0xf will get the final index
  } while (number < 6);
  unused = 0;
  number = strings_not_equal(string,"giants");
  if (number != 0) {
    explode_bomb();
  }
  return;
}

character index inside the array123
array123[0] = i
array123[1] = s
array123[2] = r
array123[3] = v
array123[4] = e
array123[5] = a
array123[6] = w
array123[7] = h
array123[8] = o
array123[9] = b
array123[10] = p
array123[11] = n
array123[12] = u
array123[13] = t
array123[14] = f
array123[15] = g

example of applying the mask 0xf,
a = 0x61 & 0xf = 0x1 = 1
b = 0x62 & 0xf = 0x2 = 2
basically the operation "& 0xf" will strip away the high nibble and left the low nibble

Base on this logic, we could deduct the following sequence (We asumme that the possible are only from a-z, but any char in ascii table could be possible as well)
abcde fghij klmno pqrst uvwxy z
srvea whobp nutfg isrve awhob p

From the order above we could have the following possible answer
g = o
i = p
a = e / u
n = k
t = m
s = a / q

Possible answer:
opekma
opekmq
opukma
opukmq


PHASE 6

0x0804b26c -> [0xfd, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x60, 0xb2, 0x04, 0x08]; 
0x0804b260 -> [0xd5, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x54, 0xb2, 0x04, 0x08]; 
0x0804b254 -> [0x2d, 0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x48, 0xb2, 0x04, 0x08]; 
0x0804b248 -> [0xe5, 0x03, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x3c, 0xb2, 0x04, 0x08]; 
0x0804b23c -> [0xd4, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x30, 0xb2, 0x04, 0x08]; 
0x0804b230 -> [0xb0, 0x01, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]; 

int node1 = [0x000000fd, 0x00000001, 0x0804b260];
int node2 = [0x000002d5, 0x00000002, 0x0804b254];
int node3 = [0x0000012d, 0x00000003, 0x0804b248];
int node4 = [0x000003e5, 0x00000004, 0x0804b23c];
int node5 = [0x000000d4, 0x00000005, 0x0804b230];
int node6 = [0x000001b0, 0x00000006, 0x00000000];

int node1 = [253, 1, 0x0804b260];
int node2 = [725, 2, 0x0804b254];
int node3 = [301, 3, 0x0804b248];
int node4 = [997, 4, 0x0804b23c];
int node5 = [212, 5, 0x0804b230];
int node6 = [432, 6, 0];


void phase_6(char* inputString)
{
  int* tmp_node;
  int counter;
  int* current_node;
  int index;
  void* head_node;
  int *node_array[6];
  int inputNb[6];
  
  head_node = node1;                                  -> Point head_node to global var node1 at address 0x0804b26c
  read_six_numbers(inputString,inputNb);              -> Convert string into int array

  index = 0;

  while (index < 6) {
    if (5 < inputNb[index] - 1U) {                    -> Accept any number as long as it is less or equal 6
      explode_bomb();
    }
    counter = index + 1;                              -> Start checking the input number starting from the next index
    if (counter < 6) {                                -> Loop through all the number in inputNb array
      while (counter < 6) {
        if (inputNb[index] == inputNb[counter]) {     -> Check if the current number is repeated
          explode_bomb();
        }
        counter++;
      }
    }
    index++;                                          -> (Conclusion) This double loop is to check if the input number is any number less or equal to 6
  }                                                       As well as making sure there is no repeating number
  


  index = 0;

  while (index < 6) {
    counter = 1;
    current_node = (int *)head_node;                  -> current_node is reset to address 0x0804b26c in every loop
    if (1 < inputNb[index]) {                         -> If the current input number is 1, current_node = head_node no need to go into the loop 
      while (counter < inputNb[index]) {              -> As long as the current input number is lesser then the counter
        current_node = (int *)current_node[2];        -> move current_node to the next node by using the address stored in index 2
        counter++;                                    -> (Conclusion) This loop is to retrive the nodeX base on the input number
      }
    }
    node_array[index] = current_node;                 -> Store the retrived node into the node_array
    index++;                                          -> (Conclusion) This loop will retrived the nodeX base on the input number
  }                                                       the order of the array is base on the order of our input,
                                                          example: input = 453216, node_array = [node4, node5, node3, node2, node1, node6]


  index = 1;                                          -> For example purpose, this loop will use the node_array from the example above
  current_node = node_array[0];                       -> node_array[0] = node4

  while (index < 6) {
    tmp_node = node_array[index];                     -> node_array[1] = node5, tmp_node = node5
    current_node[2] = (int)tmp_node;                  -> node4->next = node5
    current_node = tmp_node;                          -> current_node = node5
    index++;
  }                                                   -> (Conclusion) This loop is to relink all the next pointer in the node inside node_array 
  tmp_node[2] = 0;                                    -> last node inside node_array, point to 0 to prevent infinite loop


  index = 0;
  while (index < 5) (
    if (*node_array[0] < *(int *)node_array[0][2]) {  -> Compare the content of the head node to the next node, if next node is bigger, it will explode
      explode_bomb();
    }
    node_array[0] = (int *)node_array[0][2];          -> Set head node to the next node and continue the loop
    index++;
  )                                                   -> (Conclusion) This loop is to check if the node_array are in the right sorting order
                                                          base on the content of the node, we can also conclude that the order is DESC
  return;
}

Base on the analysis of the phase_6 function, we know that it is expecting 6 numbers which could sort the global node into the right DESC order
node1 = [253, 1, 0x0804b260]; -> node1[0] = 253
node2 = [725, 2, 0x0804b254]; -> node2[0] = 725
node3 = [301, 3, 0x0804b248]; -> node3[0] = 301
node4 = [997, 4, 0x0804b23c]; -> node4[0] = 997
node5 = [212, 5, 0x0804b230]; -> node5[0] = 212
node6 = [432, 6, 0];          -> node6[0] = 432
Correct order = node4, node2, node6, node3, node1, node5
Answer = 4 2 6 3 1 5

Final answer:
Phase_1 = Public speaking is very easy.
Phase_2 = 1 2 6 24 120 720
Phase_3 = 1 b 214 / 2 b 755 / 7 b 524
Phase_4 = 9
Phase_5 = opekma / opekmq / opukma / opukmq
Phase_6 = 4 2 6 3 1 5

After testing all the possible answer above, the correct answer is
Publicspeakingisveryeasy.
1 2 6 24 120 720
1 b 214 
9 
opekmq
4 2 6 1 3 5

In the README file, it told us that there is no space in the password,
Thus final solution is "Publicspeakingisveryeasy.126241207201b2149opekmq426135"