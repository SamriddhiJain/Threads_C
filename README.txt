**************************README.txt***************************
Since we are using pthread library for making threads, compile the test files with -pthread.
The dining.c is the solution for first problem i.e. dining philosophers problem, in which we are using semaphores to synchronize between the threads
The second problem is solved using a mutex and conditional (threads.c)
In the third problem we had to compare the performances for matrix multiplication, while using threads (matth.c, th2.c) and in other case multiplying in the conventional way(mat1.c). We varied dimension size from 1, 5, 10, 50, 100, 200, 500, 1000, 2000, 3000.Log file with results and corresponding graphs are attached for both the cases. While using threads we made 100 threads which will equally distribute the task of multiplication among them. The matrices were randomly initialised.
