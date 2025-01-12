## PIPEX (with bonus)

Pipex is a 42 school project written in C, which is about recreating the behaviour of a pipe symbol in a command line, redirecting the output of one command as input for the following.<br>
The project followins a specific command set up: the first command gets its input from a file and the last command outputs to another file.<br>
<br>
To try the program, type make in the terminal to compile the executable.<br>
Run the program following this structure:<br>
./pipex file1 cmd1 cmd2 file2<br>
<br>
Example:<br>
$> ./pipex infile "ls -l" "wc -l" outfile<br>
<br>
The bonus part includes several pipes and redirection from a heredoc.<br> 
To run several piped commands, follow this structure:<br>
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2<br>
<br>
The program also supports « and » when the first parameter is "here_doc".<br>
Example:<br>
$> ./pipex here_doc LIMITER cmd cmd1 file<br>
Will behave like:<br>
cmd << LIMITER | cmd1 >> file
