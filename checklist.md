Mandatory Part Checklist

    Define the structure for a philosopher:
        Create a struct definition for the philosopher.
        Include fields for philosopher ID, fork IDs, and any other necessary data.

    Implement the main function:
        Declare necessary variables and data structures.
        Call the function to parse and validate command-line arguments.
        Initialize forks and mutexes.
        Set simulation start time.
        Create philosopher threads.
        Wait for philosopher threads to finish.
        Clean up and release any allocated resources.

    Parse and validate command-line arguments:
        Read the command-line arguments.
        Validate the number and format of arguments.
        Store the arguments in appropriate variables.

    Initialize forks and mutexes:
        Create an array of fork structures.
        Initialize a mutex for each fork.

    Create philosopher threads:
        Create the required number of philosopher threads.
        Pass the necessary data (e.g., philosopher ID, fork IDs) to each thread.

    Implement the logic for philosophers to eat, sleep, think, and die:
        Implement the philosopher thread function.
        Use mutex locks to acquire and release forks.
        Implement the necessary delays for eating, sleeping, and thinking.
        Update the philosopher's state and print the corresponding messages.

    Print the state changes of philosophers with timestamps:
        Get the current timestamp in milliseconds.
        Format and print the state change messages for philosophers.

    Handle the termination conditions:
        Check if a philosopher has died (e.g., by monitoring their last meal's timestamp).
        If a philosopher dies, print the death message and exit the program.
        If all philosophers have eaten the required number of times, print the completion message and exit the program.

    Clean up and release any allocated resources before program termination:
        Destroy mutexes and release any other resources used.
        Free dynamically allocated memory.