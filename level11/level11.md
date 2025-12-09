# Level11

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