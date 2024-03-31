# Simple Transaction System

This project implements a simple transaction system that allows users to send money to each other using a command-line interface (CLI) over HTTP. The system is built using a combination of C for the backend server and HTML/CSS/JavaScript for the frontend CLI interface.

## Features

- Allows users to send money from one user to another.
- Provides a command-line interface (CLI) for interacting with the system.
- Displays user balances and recent transactions.
- Supports commands such as sending money, displaying help information, and exiting the system.

## Prerequisites

- Docker installed on your machine.
- Basic understanding of HTTP requests and web servers.

## Getting Started

To get started with the Simple Transaction System, follow these steps:

1. Clone this repository to your local machine:

   ```bash
   git clone https://github.com/your_username/simple-transaction-system.git
   ```

2. Navigate to the project directory:

   ```bash
   cd simple-transaction-system
   ```

3. Build the Docker image:

   ```bash
   docker build -t simple-transaction-system .
   ```

4. Run the Docker container:

   ```bash
   docker run -p 80:80 simple-transaction-system
   ```

5. Access the system in your web browser at [http://localhost](http://localhost).

## Usage

Once the system is up and running, you can interact with it using the provided CLI interface. Here are some available commands:

- **send**: Send money from one user to another. Syntax: `send [sender_id] [receiver_id] [amount]`.
- **help**: Show available commands.
- **exit**: Close the transaction system.

## Architecture

The project consists of two main components:

1. **Backend Server (C)**:
   - Handles HTTP requests from clients.
   - Implements the logic for processing transactions.
   - Logs server activities to a file.

2. **Frontend CLI Interface (HTML/CSS/JavaScript)**:
   - Provides a user-friendly interface for interacting with the system.
   - Displays user balances, recent transactions, and help information.
   - Sends HTTP requests to the backend server to perform transactions.

## Contributing

Contributions are welcome! If you'd like to contribute to the project, please follow these steps:

1. Fork the repository.
2. Create your feature branch (`git checkout -b feature/your-feature-name`).
3. Commit your changes (`git commit -am 'Add some feature'`).
4. Push to the branch (`git push origin feature/your-feature-name`).
5. Create a new Pull Request.

## License

This project is licensed under the MIT License - see the [MIT LICENSE](LICENSE) file for details.

## Acknowledgements

- Thanks to [OpenAI](https://openai.com) for providing the language model used to generate this README.
