# Philosophers (100% PASSED)

The dilemma in the Philosophers project is known as the "Dining Philosophers problem." It is a classic synchronization problem that arises in concurrent programming. The dilemma revolves around a group of philosophers sitting at a round table with a bowl of spaghetti in the middle and a fork placed between each pair of adjacent philosophers.

The dilemma is that each philosopher requires two forks to eat their spaghetti. However, there are only as many forks as there are philosophers. This creates a potential conflict where multiple philosophers may try to acquire the same forks simultaneously, leading to deadlock or starvation.

The challenge is to devise a solution that allows each philosopher to pick up the necessary forks to eat, while ensuring that deadlocks (where philosophers are unable to make progress) and starvation (where philosophers are unable to eat) are avoided. This requires careful resource allocation, synchronization, and the use of mutexes or other mechanisms to prevent conflicts and maintain a balanced distribution of resources among the philosophers.

The goal of the project is to implement a solution that allows the philosophers to eat without experiencing conflicts or starvation, while also considering additional constraints such as the time limits for eating, thinking, and sleeping, as well as the number of times each philosopher must eat before the simulation stops.

## Key Features

- **Threads and Mutexes:** Implementation of threads and mutexes for synchronization.
- **Check User Input:** Command-line arguments to control the simulation parameters
- **Log of Threads:** Logging and visualization of philosopher(each philosopher is a thread) activities.
- **Norm Compliance:** The project adheres to coding standards and norms, ensuring clean and readable code.
- **Memory Management:** Philosophers takes care of dynamically allocated memory to avoid leaks and ensure efficient resource utilization.
- **Resources Management:** Pilosophers takes care of the destrution of threas and mutexs when are not longer needed to ensure efficient resource utilization.

## Why Philosophers?

The Philosophers project offers several benefits and learning opportunities:

- **Concurrency and Synchronization:** The project involves working with threads and mutexes to manage shared resources and ensure synchronization among the philosophers. It provides a practical understanding of concurrent programming concepts and challenges.

- **Problem Solving:** The Dining Philosophers problem is a classic synchronization problem that requires careful resource allocation and avoidance of deadlocks and starvation. By tackling this problem, programmers can enhance their problem-solving skills and develop strategies for managing shared resources.

- **Real-world Relevance:** The project simulates a scenario that reflects real-world situations where multiple entities need to access shared resources concurrently. Understanding how to handle such situations can be valuable in developing robust and efficient software systems.

- **Debugging and Testing:** Implementing the Philosophers project allows programmers to practice debugging and testing techniques. They can observe the behavior of the philosophers, identify potential issues, and apply debugging strategies to resolve them.

- **Algorithm Design:** The project offers an opportunity to design efficient algorithms for managing resource allocation and synchronization among the philosophers. It encourages programmers to think critically and optimize their solutions.

In conclusion, the Philosophers project provides a practical and engaging way to explore concurrency, synchronization and problem-solving. It offers valuable insights into concurrent programming challenges and equips programmers with essential skills for developing robust and efficient software systems.

## Getting Started

To run the program, follow these steps:

1. Clone the repository: `git clone git@github.com:abaiao-r/philosophers.git`
2. Navigate to the project directory: `cd Philosophers`
3. Compile the program: `make`
4. Run the program with appropriate arguments: `./philo <arguments>` You can find the documentation [here](/philosophers.pdf).

## Contributing

As this project is intended to showcase my Threads and Mutexes skills, I am currently not accepting direct contributions. However, I am open to feedback and suggestions that could help improve the project. If you have any ideas or spot any issues, feel free to raise them as GitHub issues.

## License

Odin-Recipes is released under the [MIT License](./LICENSE.txt).