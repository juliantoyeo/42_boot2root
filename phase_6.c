0x0804b26c -> [0xfd, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x60, 0xb2, 0x04, 0x08]; 
0x0804b260 -> [0xd5, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x54, 0xb2, 0x04, 0x08]; 
0x0804b254 -> [0x2d, 0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x48, 0xb2, 0x04, 0x08]; 
0x0804b248 -> [0xe5, 0x03, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x3c, 0xb2, 0x04, 0x08]; 
0x0804b23c -> [0xd4, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x30, 0xb2, 0x04, 0x08]; 
0x0804b230 -> [0xb0, 0x01, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]; 

int node1 = [0x0000fd, 0x00000001, 0x0804b260];
int node2 = [0x0002d5, 0x00000002, 0x0804b254];
int node3 = [0x00012d, 0x00000003, 0x0804b248];
int node4 = [0x0003e5, 0x00000004, 0x0804b23c];
int node5 = [0x0000d4, 0x00000005, 0x0804b230];
int node6 = [0x0001b0, 0x00000006, 0x00000000];

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