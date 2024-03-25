#include <stdio.h>
#include <stdlib.h>

int32_t add(int32_t a, int32_t b) { return a + b; }

int32_t sequential_compute(char *file_name,
                           int32_t (*reduce_fn)(int32_t a, int32_t b)) {
  FILE *file = fopen(file_name, "r");
  int32_t accumulator;
  char *line = 0;
  size_t len = 0, bytes_read = 0;

  // Initial values
  int32_t n1, n2;
  if ((bytes_read = getline(&line, &len, file)) == -1) {
    perror("File has less than 2 elements");
  }
  n1 = atoi(line);
  if ((bytes_read = getline(&line, &len, file)) == -1) {
    perror("File has less than 2 elements");
  }
  n2 = atoi(line);
  accumulator = reduce_fn(n1, n2);

  while ((bytes_read = getline(&line, &len, file)) != -1) {
    n1 = atoi(line);
    accumulator = reduce_fn(n1, accumulator);
  }
  return accumulator;
}

int main(int argc, char *argv[]) {
  printf("%d\n", sequential_compute("numbers.txt", add));
  return 0;
}
