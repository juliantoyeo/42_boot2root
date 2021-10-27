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

void phase_6(char* inputString)
{
  int *numberArray1;
  int index1;
  int *numberArray2;
  int index;
  undefined1 *local_38;
  int *local_34 [6];
  int inputNumber[6];
  
  local_38 = node1;
  read_six_numbers(inputString,inputNumber);

  index = 0;

  do {
    if (5 < inputNumber[index] - 1U) {
      explode_bomb();
    }
    index1 = index + 1;
    if (index1 < 6) {
      do {
        if (inputNumber[index] == inputNumber[index1]) {
          explode_bomb();
        }
        index1 = index1 + 1;
      } while (index1 < 6);
    }
    index = index + 1;
  } while (index < 6);

  index = 0;
  while (index < 6) {
    if (5 < inputNumber[index] - 1U) {
      explode_bomb();
    }
    index1 = index + 1;
    if (index1 < 6) {
      while (index1 < 6) {
        if (inputNumber[index] == inputNumber[index1]) {
          explode_bomb();
        }
        index1++;
      }
    }
    index++;
  }

  index = 0;

  do {
    index1 = 1;
    numberArray2 = (int *)local_38;
    if (1 < inputNumber[index]) {
      do {
        numberArray2 = (int *)numberArray2[2];
        index1 = index1 + 1;
      } while (index1 < inputNumber[index]);
    }
    local_34[index] = numberArray2;
    index = index + 1;
  } while (index < 6);

  index = 1;
  numberArray2 = local_34[0];

  do {
    numberArray1 = local_34[index];
    numberArray2[2] = (int)numberArray1;
    index = index + 1;
    numberArray2 = numberArray1;
  } while (index < 6);

  numberArray1[2] = 0;
  index = 0;

  do {
    if (*local_34[0] < *(int *)local_34[0][2]) {
      explode_bomb();
    }
    local_34[0] = (int *)local_34[0][2];
    index = index + 1;
  } while (index < 5);

  return;
}