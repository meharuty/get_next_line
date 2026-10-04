*This project has been created as part of the 42 curriculum by meharuty.*

# Get Next Line

## Description

*Get Next Line (GNL)* is a project from the 42 curriculum whose goal is to implement a function capable of reading a file line by line using a file descriptor.

The function get_next_line() reads from a file descriptor and returns the next line each time it is called, including the newline character (`\n`) when present. The function must manage memory carefully and avoid reading the entire file at once.

This project introduces several important low-level programming concepts in C, including:

* File descriptors
* Static variables
* Memory management (malloc / free)
* Efficient buffered reading using read()
* Handling partial reads and leftover data

The function must behave correctly when reading from:

* Files
* Standard input (stdin)
* Different buffer sizes

The bonus part extends the implementation so that the function can **handle multiple file descriptors simultaneously using only one static variable, without losing track of each reading state.

---

## Project Structure

Mandatory files:

get_next_line.c
get_next_line_utils.c
get_next_line.h

Bonus files:

get_next_line_bonus.c
get_next_line_utils_bonus.c
get_next_line_bonus.h

---

## Function Prototype

char *get_next_line(int fd);

### Parameters

* fd – File descriptor to read from

### Return Value

* Returns the next line from the file descriptor
* Returns NULL when:

  * End of file is reached
  * An error occurs

The returned line includes the newline (`\n`) if it exists.

---

## How It Works (Algorithm Explanation)

The main challenge of the project is that the read() function reads a fixed number of bytes, not a complete line. Therefore, get_next_line() must repeatedly read chunks of data until a newline is found.

### Step-by-step algorithm

1. **Static storage**

   * A static variable stores leftover data that remains after extracting a line.
   * This allows the function to remember what was previously read between calls.

2. **Buffered reading**

   * A temporary buffer of size BUFFER_SIZE is allocated.
   * read() fills this buffer from the file descriptor.

3. **Appending data**

   * The read buffer is appended to the stored data string.
   * Reading continues until a newline (`\n`) appears or EOF is reached.

4. **Extracting the line**

   * Once a newline is found, the function extracts everything up to and including it.
   * This becomes the line returned to the caller.

5. **Saving remaining data**

   * The remaining characters after the newline are stored back in the static variable.
   * They will be used in the next function call.

6. **Memory cleanup**

   * Temporary buffers are freed to prevent memory leaks.

This process repeats every time get_next_line() is called.

---

## Bonus Implementation

The bonus version adds two features:

### 1. Multiple File Descriptor Support

Instead of a single storage variable, the function keeps track of data for each file descriptor independently.

Example usage:


get_next_line(fd1);
get_next_line(fd2);
get_next_line(fd1);
get_next_line(fd3);


Each file descriptor continues reading exactly where it left off.

This is typically implemented using:

static char *res[FD_MAX];


Each index corresponds to a specific file descriptor.

### 2. Only One Static Variable

The implementation uses a single static variable to track all file descriptors while still preserving each reading state.

---

## Compilation

Compile using:

cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c


You can change the buffer size:

cc -Wall -Wextra -Werror -D BUFFER_SIZE=10 get_next_line.c get_next_line_utils.c

If the flag is not provided, a default buffer size can be defined inside the header:

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

---

## Example Usage

Example main.c:

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	int fd;
	char *line;

	fd = open("text.txt", O_RDONLY);

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}

	close(fd);
}


Compile

cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c

Run:


./a.out


---

## Edge Cases Considered

The implementation handles:

* Files ending without a newline
* Very small BUFFER_SIZE (e.g. 1)
* Very large BUFFER_SIZE
* Empty files
* Reading from stdin
* Memory leaks prevention
* Invalid file descriptors

---

## Technical Choices

Key implementation decisions include:

* Using a static stash to preserve leftover data.
* Implementing custom string utility functions such as:

  * ft_strlen
  * ft_strjoin
  * ft_strdup
  * ft_strchr

These are implemented manually since using libft is forbidden.

---

## Resources

Helpful resources used while working on this project:

* 42 subject documentation
* The read() manual
  https://man7.org/linux/man-pages/man2/read.2.html
* C memory management tutorials
* File descriptor documentation

### Use of AI

AI tools were used for:

* Understanding the general structure of the project
* Reviewing algorithm approaches
* Improving documentation and README formatting

All implementation, debugging, and testing of the code were done manually.

---

## Key Concepts Learned

Through this project, the following C programming concepts are reinforced:

* Static variables
* File descriptors
* Buffered reading
* Dynamic memory management
* String manipulation
* Handling edge cases in system programming

---

## Conclusion

The *Get Next Line* project is an essential exercise in mastering low-level file reading and memory management in C. It builds a deeper understanding of how data flows between the operating system and a program, while also enforcing careful control over memory and program state.

