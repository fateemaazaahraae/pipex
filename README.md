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
  <p>Handle multiple pipes :</p>
  <p>This :</p>
  <p>./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2</p>
  <p>Should behave like this :</p>
  <p>< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2</p>
  </li>
  <li>
    <p>Support « and » when the first parameter is "here_doc" :</p>
    <p>This :</p>
    <p> ./pipex here_doc LIMITER cmd cmd1 file</p>
    <p>Should behave like this :</p>
    <p>cmd1 << LIMITER | cmd2 >> file</p>
  </li>
</ul>
