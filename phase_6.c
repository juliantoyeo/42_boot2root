void phase_6(char* inputString)
{
  int* numberArray1;
  int counter;
  int* numberArray2;
  int index;
  void* nodeRef;
  int *local_34 [6];
  int inputNb[6];
  
  nodeRef = node1;                                 -> Point nodeRef to global var node1
  read_six_numbers(inputString,inputNb);           -> Convert string into int array

  index = 0;

  while (index < 6) {
    if (5 < inputNb[index] - 1U) {                 -> Accept any number as long as it is less or equal 6
      explode_bomb();
    }
    counter = index + 1;                           -> Start checking the input number starting from the next index
    if (counter < 6) {                             -> Loop through all the number in inputNb array
      while (counter < 6) {
        if (inputNb[index] == inputNb[counter]) {  -> Check if the current number is repeated
          explode_bomb();
        }
        counter++;
      }
    }
    index++;                                       -> This double loop is to check if the input number is any number less or equal to 6
  }                                                   As well as making sure there is no repeating number
  


  index = 0;

  while (index < 6) {
    counter = 1;
    numberArray2 = (int *)nodeRef;                 -> numberArray2 is set to nodeRef which pointed to node1 in every loop
    if (1 < inputNb[index]) {                      -> If the current input number is bigger then 1, number 6,5,4,3,2 should be accepted
      while (counter < inputNb[index]) {           -> As long as the current input number is lesser then the counter
        numberArray2 = (int *)numberArray2[2];     -> 
        counter++;
      }
    }
    local_34[index] = numberArray2;
    index++;
  }

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