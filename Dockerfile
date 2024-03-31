# Use a base image with the necessary runtime environment (e.g., Ubuntu with Apache)
FROM ubuntu:latest

# Install required packages (e.g., Apache, GCC for compiling C code)
RUN apt-get update && \
    apt-get install -y apache2 gcc && \
    rm -rf /var/lib/apt/lists/*

# Copy your project files into the container
COPY . /var/www/html/

# Compile the backend C code
RUN gcc /var/www/html/backend.c -o /var/www/html/backend

# Expose port 80 (default HTTP port)
EXPOSE 80

# Start the Apache web server
CMD ["apache2ctl", "-D", "FOREGROUND"]
