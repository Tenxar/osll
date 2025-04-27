
Create two files here

A.c
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    int fd;
    char *myfifo = "myfifo";
    char *message = "Hello Everyone! Welcome to Modern College of Engineering, Pune. This is the second line.\nSecond Paragraph starts here.\n";

    // Create FIFO
    mkfifo(myfifo, 0666);

    // Open FIFO for writing
    fd = open(myfifo, O_WRONLY);

    // Send message to the FIFO
    write(fd, message, sizeof(message));

    // Close the FIFO
    close(fd);

    // Unlink FIFO
    unlink(myfifo);

    return 0;
}

B.c
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd, fd1;
    char *myfifo = "myfifo";
    char *myfifo1 = "myfifo1";
    char buf[1024];
	char ch[1024];
    int words = 0, characters = 0, lines = 0;
    FILE *fp;

    // Create FIFO for writing the result
    mkfifo(myfifo1, 0777);

    // Open the FIFO for reading from A_FIFO
    fd = open(myfifo, O_RDONLY);

    // Read data from FIFO
    read(fd, buf, sizeof(buf));

    // Print the received message
    printf("\nFirst message received: \n\n%s\n\n", buf);

    // Count words, characters, and lines
    int i = 0;
    int in_word = 0; // Flag to track whether we are inside a word

    while (buf[i] != '\0') {
        characters++;  // Every character counts

        // If the character is space, tab, or newline, consider it a word boundary
        if (buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n') {
            if (in_word) {
                words++; // Count a word when we reach a word boundary
                in_word = 0; // Reset the word flag
            }

            if (buf[i] == '\n') {
                lines++; // Count a line when we encounter a newline
            }
        } else {
            in_word = 1; // We are inside a word
        }

        i++;
    }

    // If the last character was part of a word, count it as a word
    if (in_word) {
        words++;
    }

    // If there are no newlines in the text, count at least one line
    if (lines == 0 && characters > 0) {
        lines = 1;
    }

    // Display the results
    printf("\nTotal Words: %d\n", words);
    printf("Total Lines: %d\n", lines);
    printf("Total Characters: %d\n", characters);

    // Write the result to a file
    fp = fopen("test.txt", "w+");
    fprintf(fp, "\nTotal Words: %d\n", words);
    fprintf(fp, "Total Lines: %d\n", lines);
    fprintf(fp, "Total Characters: %d\n", characters);
    fclose(fp);

    // Read the file back and send it through FIFO1
    fp = fopen("test.txt", "r");
    int j = 0;
    while ((ch[j] = fgetc(fp)) != EOF) {
        j++;
    }
    fclose(fp);

    // Open FIFO1 to send the result
    fd1 = open(myfifo1, O_WRONLY);
    write(fd1, ch, strlen(ch) + 1); // Write the result content to FIFO1
    close(fd1);

    // Close the original FIFO
    close(fd);

    return 0;
}



RUN:
gcc A.c -o A
gcc B.c -o B
Run Program A in one terminal:
./A
Run Program B in another terminal:
./B