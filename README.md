<h1><strong>✏️ Pipex : </strong></h1>
<p><i>Pipex is a project that re-creates in C the way two commands are piped together via | in the shell </i><p><br>
<h1>💡 About the project : </h1>
<p>This project will let you discover in detail a UNIX mechanism that you already know
by using it in your program.</p> <br><br>

<h1>💯 Final Grade : </h1> <br>


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
<ol>
  <li>
    <h2>Fork : </h2>
    <ol>
      <li>
        <h4>What is Fork ?</h4>
      <p>`fork()` is a system call in C programming that creates a new process by duplicating the calling process. After fork() is called, we have two processes : the parent process and the child process. You must include the <unistd.h> header file. The child process is a duplicate of the parent process. The child process inherits the memory space, file descriptors, and other         attributes of the parent process with its own unique process ID (PID). Both processes continue executing from the point where fork() was called, but they have different return values from fork(): the parent receives the PID of the child process, while the child receives a return value of 0 or negative value (usually -1) means the creation of the child process was               unsuccessful ❌.</p>
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
    <ol>
      <li>
        <h4>What is Pipe ? </h4>
        <p>In C, a pipe is a form of inter-process communication (IPC) that allows data to be passed between two processes. It acts as a unidirectional communication channel, typically used for communication between a parent process and its child process or between two related processes. <br> It takes an array of 2 int as an argument (Ex : pipefd(fd[2]) ). The array pipefd is used to return two file descriptors referring to the ends of the pipe. pipefd[0] refers to the read end of the pipe. pipefd[1] refers to the write end of the pipe. Data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe
On success, 0 is returned. On error, -1 is returned, and errno is set appropriately.</p>
      </li>
    </ol>
  </li>
</ol>


