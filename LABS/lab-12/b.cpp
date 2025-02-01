#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>
using namespace std;

int main() {
  int fd = open("data.txt", O_RDWR); // Open the file for reading and writing
  if (fd == -1) {
    perror("Error opening file");
    return 1;
  }

  int file_size = lseek(fd, 0, SEEK_END); // Get the file size
  if (file_size == -1) {
    perror("Error getting file size");
    close(fd);
    return 1;
  }

  // Map the file into memory
  char *mapped_data =
      (char *)mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (mapped_data == MAP_FAILED) {
    perror("Error mapping file into memory");
    close(fd);
    return 1;
  }

  // Display the content of the mapped memory region
  cout << "Original content: " << (mapped_data) << endl;

  // Modify the content of the mapped memory region
  const char *additional_text = " - Updated!";
  int additional_text_len = strlen(additional_text);
  memcpy((mapped_data) + file_size, additional_text, additional_text_len);

  // Update the file size after modification
  file_size += additional_text_len;

  // Display the updated content of the mapped memory region
  cout << "Updated content: " << (mapped_data) << endl;

  // Unmap the memory region and close the file
  if (munmap(mapped_data, file_size) == -1) {
    perror("Error unmapping memory");
    close(fd);
    return 1;
  }
  close(fd);

  return 0;

}