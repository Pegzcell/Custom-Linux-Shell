# Pratham's Shell

This shell supports most of the `zsh` commands along with some custom commands, all of which execute the functions invoking system calls of a linux system.

> #### just 'make' to run the project

### Files
    * makefile
    * headers.h         - contains most required headers and functions
    * main.c            - contains the main functioning of the shell: 
                            1. initializes required global variables 
                            2. sets signals
                            3. calls signal handling functions
                            4. resets STDIN, STDOUT file descriptors                
                            4. invokes shell prompt
                            5. reads user commands and sends to command fn
    * signals.c         - contains signal handlers for:
                            1. SIGINT (CTRL-C)
                            2. SIGCHLD (background process management for exit status, fg/bg, sig functions)
                            3. SIGTSTP (CTRL-Z)
                            4. EOF (CTRL-D)
    * commands.c        - receives user input from main
                            1. command fn tokenizes w ';'
                            2. piping fn sets pipes by tokenizing w '|'
                            3. io fn conducts redirection on all pipes
                            4. execute fn calls individual fns in other files
                            5. repeat fn calls execute fn alternatively if required
                            6. replay fn may directly call individual fns in other files
    * commands.h        - contains functions and declarations required for operations in the command file solely
    * prompt.c          - has functions to create the prompt and initialize the general shell environment
    * relative_path.c   - has function to make a path relative to the directory that contains a.out. This has been used for prompt and pinfo.
    * basic_fns.c       - contains a sorting and string to int conversion function
    * cd.c              - cd command
    * pinfo.c           - pinfo command
    * echo.c            - echo command
    * pwd.c             - pwd command
    * ls.c              - ls command
    * sys_com.c         - has function to execute system commands as background/foreground processes using execvp.
    * history.c         - history command
    * jobs.c            - jobs command
    * sig.c             - sig command
    * fg_bg.c           - fg and bg commands


### Functioning
    * cd <directory path>                                   - changes directory to the given path. Changes to shell home if no directory is provided
    * pwd                                                   - shows the absolute path of the current working directory 
    * echo <text>                                           - prints the text to the terminal.
    * ls [al] <directory path>                              - handles all variations of ls with a and l flags and directory path
    * pinfo [pid]                                           - prints process related info (pid, Process Status {R, R+, S, S+, Z}, memory and Executable Path) about given pid. Prints process related info of shell program if no pid is provided
    * exit                                                  - exits the shell
    * repeat [n] <command>                                  - executes command, n times
    * history [n]                                           - prints history of n (max 20) commands. Prints history of maximum 20 commands if n is not provided
    * jobs [rs]                                             - prints list of all existing background jobs along with their pid and their current state. flag -r, -s to display only running, stopped processes respectively
    * sig [rs] <job> <signal>                               - passes signal to job using kill syscall
    * fg <jobNumber>                                        - brings a running or a stopped background job with a given job number to background
    * bg <jobNumber>                                        - changes a stopped background job to a running background job
    * input-output redirection functionality                - replicates (almost) what bash does
    * piping functionality                                  - replicates (almost) what bash does
    * CTRL-C                                                - cause a SIGINT signal to be sent to the current foreground job of this shell.
    * CTRL-D                                                - exits the shell like the EOF character
    * CTRL-Z                                                - changes the status of currently running job to stop, and pushes it in background process
    * replay -command <command> -interval [i] -period [p]   - executes command at i seconds interval for p seconds period.
    * All other commands are implemented using execvp. 
    * Background Processing (can be run with '&') is handled for commands executed through execvp