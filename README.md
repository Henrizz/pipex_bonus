## PIPEX
### with bonus

Pipex is a 42 school project written in C, which is about recreating the behaviour of a pipe symbol in a command line, redirecting the output of one command as input for the following. 
The porject followins a specific command set up: the first command gets its input from a file and the last command outputs to another file. 

To try the program, type make in the terminal to compile the executable. 
Run the program following this structure: ./pipex file1 cmd1 cmd2 file2
Example: 
$> ./pipex infile "ls -l" "wc -l" outfile

The bonus part includes several pipes and redirection from a heredoc. 
To run several piped commands, follow this structure: 
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2

The program also supports « and » when the first parameter is "here_doc".
Example:
$> ./pipex here_doc LIMITER cmd cmd1 file
Will behave like:
cmd << LIMITER | cmd1 >> file
