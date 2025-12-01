# Level03

### 1. Identity

	$ id
	uid=2004(level04) gid=2004(level04) groups=2004(level04),100(users)

We are logged as **level04**.

### 2. Home directory

	$ pwd
	/home/user/level04

	$ ls -la
	...
	-rwsr-sr-x  1 flag04  level04  152 Mar  5  2016 level04.pl
	...

All files here are standard shell configuration files (.bashrc, .profile, etc.) with no exploitable content except for one : **level04.pl**.

It is a Perl scripting file. Executing it gives us :

	$ ./level04.pl 
	Content-type: text/html

### 3. Analyzing the script

