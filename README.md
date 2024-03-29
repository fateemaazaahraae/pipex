<h1><strong>✏️ Pipex : </strong></h1>
<p><i>Pipex is a project that re-creates in C the way two commands are piped together via | in the shell </i><p><br>
<h1>💡 About the project : </h1>
<p>This project will let you discover in detail a UNIX mechanism that you already know
by using it in your program.</p> <br><br>

<h1>💯 Final Grade : </h1> <br>
<img width="269" alt="Screen Shot 2024-03-06 at 11 41 17 AM" src="https://github.com/fateemaazaahraae/pipex/assets/133344215/8aa8f74d-e23f-44d8-9255-c6105fad8d5e">

<h1>Description of mandatory part :</h1>
<p>Your program will be executed as follows:</p>
<p>./pipex file1 cmd1 cmd2 file2</p>
<p>It must take 4 arguments:</p>
<ul>
  <li>file1 and file2 are file names.</li>
  <li>cmd1 and cmd2 are shell commands with their parameters.</li>
</ul>
<p>It must behave exactly the same as the shell command below:</p>
<p>< file1 cmd1 | cmd2 > file2</p><br>
<h1>Description of bonus part :</h1>
<p>You will get extra points if you:</p>
<ul>
  <li>
  <p>Handle multiple pipes :<strong><i>(15 points)</i></strong></p>
  <p>This :</p>
  <pre>    $> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2</pre>
  <p>Should behave like this :</p>
  <pre>    $> < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2</pre>
  </li>
  <li>
    <p>Support « and » when the first parameter is "here_doc" :<strong><i>(10 points)</i></strong></p>
    <p>This :</p>
    <pre>    $> ./pipex here_doc LIMITER cmd cmd1 file</pre>
    <p>Should behave like this :</p>
    <pre>    $> cmd1 << LIMITER | cmd2 >> file</pre>
  </li>
</ul>
<br><br>
<h1>Functions used : </h1>
<p>You are allowed to use several functions in this project. You already know some of them like write, ft_printf, malloc, free and all the functions from your libft. However, other important functions that have never been used before will be essential to the success of this project. Let's look at them together.</p>
<ol>
  <li>
    <h2>Fork : </h2>
    <ol>
      <li>
        <h4>What is Fork ?</h4>
      <p>`fork()` is a system call in C programming that creates a new process by duplicating the calling process. After fork() is called, we have two processes : the parent process and the child process. You must include the <strong>unistd.h</strong> header file. The child process is a duplicate of the parent process. The child process inherits the memory space, file descriptors, and other         attributes of the parent process with its own unique process ID (PID). Both processes continue executing from the point where fork() was called, but they have different return values from fork(): the parent receives the PID of the child process, while the child receives a return value of 0 or negative value (usually -1) means the creation of the child process was               unsuccessful ❌.</p>
      </li>
      <li>
    <h4>How Fork works ?</h4>
    <p>When fork() is employed, the OS duplicates the parent process entirely, creating a new child process. This includes memory, open file descriptors, and other relevant attributes. However, the child process follows its own execution path and has its own PID.<br>
To optimize memory utilization, fork() employs the (COW) copy-on-write technique. Initially, both parent and child processes share the same physical memory pages. To prevent unintended modifications, a separate copy is generated when either process attempts to alter a shared memory page.</p>
    <ul>
      <li>
        <h5>What is COW ?</h5>
        <p>Copy-on-Write (COW) is a memory optimization technique where memory pages are shared between processes until one process tries to write to them. Then, and only then, does the operating system create a separate copy of that memory page for the process making the change. This helps save memory and improve efficiency when creating new processes.It takes as argument an array of 2 int (Ex : pipefd[2]). The array pipefd is used to return two file descriptors referring to the ends of the pipe. pipefd[0] refers to the read end of the pipe. pipefd[1] refers to the write end of the pipe. Data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe. <br> On success, 0 is returned. On error, -1 is returned, and errno is set appropriately.</p>
      </li>
    </ul>
  </li>
 </ol>
</li>
  <li>
    <h2>Pipe : </h2>
    <ul>
      <li>
        <h4>What is Pipe ? </h4>
        <p>In C, a pipe is a form of inter-process communication (IPC) that allows data to be passed between two processes. It acts as a unidirectional communication channel, typically used for communication between a parent process and its child process or between two related processes. You must include the <strong>unistd.h</strong> header file. <br> It takes an array of 2 int as an argument (Ex : pipefd(fd[2]) ). The array pipefd is used to return two file descriptors referring to the ends of the pipe. pipefd[0] refers to the read end of the pipe. pipefd[1] refers to the write end of the pipe. Data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe
On success, 0 is returned. On error, -1 is returned, and errno is set appropriately.</p>
      </li>
    </ul>
  </li>
<li>
  <h2>Access :</h2>
  <ul>
    <li>
      <h4>What is access ? </h4>
      <p>In C, the access() function is used to check whether a file exists and whether the calling process has permissions to access it in a specified mode. It allows you to perform access checks on files and directories in a portable way across different operating systems. You must include <strong>unistd.h</strong> header file.</p>
      <p>It takes two arguments. The first argument takes the path to the directory/file and the second argument takes flags R_OK, W_OK, X_OK or F_OK.</p>
      <ul>
        <li>
          <p><strong>F_OK flag</strong> : Used to check for the existence of file.</p>
        </li>
        <li>
          <p><strong>R_OK flag</strong> : Used to check for read permission bit.</p>
        </li>
        <li>
          <p><strong>W_OK flag</strong> : Used to check for write permission bit.</p>
        </li>
        <li>
          <p><strong>X_OK flag</strong> : Used to check for execute permission bit.</p>
        </li>
      </ul>
    </li>
  </ul>
</li>
<li>
  <h2> Dup2 : </h2>
  <ul>
    <li>
      <h4> What is Dup2 ? </h4>
      <p>In C, the dup2() function is used to duplicate an existing file descriptor onto another file descriptor. It's commonly used for file descriptor redirection, especially in scenarios like setting up input/output redirection for child processes after forking. You must include <strong>unistd.h</strong> header file.</p>
    </li>
  </ul>
</li>
</ol>


