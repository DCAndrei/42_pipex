# 42_pipex
The Pipex project from 42 Wolfsburg school

For the mandatory part you have to create a pipe between 2 linux commands, and for the bonus, you have to create multi pipes between more than 2 commands, and also to be able to read from the terminal as input for the first command.

The project is an introduction to pipe, fork, file descriptors, exec commands, handling errors etc.

The program works perfect, except that it will time-out when it will read from endless files like urandom file, it cannot support cat ./dev/urandom | head -1 pipe command
