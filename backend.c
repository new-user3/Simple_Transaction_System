#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define HTML_FILE "index.html"
#define LOG_FILE "server_log.txt"

void log_message(const char *msg) {
    FILE *log_file = fopen(LOG_FILE, "a");
    if (log_file != NULL) {
        fprintf(log_file, "%s\n", msg);
        fclose(log_file);
    }
}

void error(const char *msg) {
    perror(msg);
    log_message(msg);
    exit(1);
}

int main() {
    int sockfd, newsockfd;
    socklen_t clilen;
    char buffer[1024];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    } else {
        printf("Socket created successfully.\n");
    }

    // Initialize server address struct
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    // Bind socket to address
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    } else {
        printf("Socket bound successfully.\n");
    }

    // Listen for incoming connections
    listen(sockfd, 5);
    printf("Listening for incoming connections...\n");

    // Accept incoming connections in a loop
    while (1) {
        clilen = sizeof(cli_addr);

        // Accept incoming connection
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            error("ERROR on accept");
        } else {
            printf("Connection accepted.\n");
        }

        // Read request from client
        memset(buffer, 0, 1024);
        n = read(newsockfd, buffer, 1023);
        if (n < 0) {
            error("ERROR reading from socket");
        } else {
            printf("Received request:\n%s\n", buffer);
            log_message("Received request:\n");
            log_message(buffer);
        }

        // Send HTTP response header
        char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
        n = write(newsockfd, response, strlen(response));
        if (n < 0) {
            error("ERROR writing to socket");
        } else {
            printf("HTTP response header sent.\n");
        }

        // Send HTML file
        FILE *html_file = fopen(HTML_FILE, "r");
        if (html_file == NULL) {
            error("ERROR opening HTML file");
        } else {
            printf("HTML file opened successfully.\n");
        }

        while ((n = fread(buffer, 1, sizeof(buffer), html_file)) > 0) {
            if (write(newsockfd, buffer, n) < 0) {
                error("ERROR writing to socket");
            }
        }
        fclose(html_file);
        printf("HTML file sent.\n");

        // Close the new socket
        close(newsockfd);
        printf("Connection closed.\n");

        // Check for user input to close the server
        printf("Press Enter to close the server, or type 'exit' to quit without waiting...\n");
        char input[100];
        fgets(input, sizeof(input), stdin);
        if (strcmp(input, "exit\n") == 0) {
            break;
        }
    }

    // Close the listening socket
    close(sockfd);
    printf("Server closed.\n");

    return 0;
}
