# Level12

## 1. Identity

```bash
$ id
uid=2013(level13) gid=2013(level13) groups=2013(level13),100(users)
```

We are logged in as **level13**.

## 2. Home directory

```bash
$ pwd
/home/user/level13

$ ls -la
[...]
-rwsr-sr-x 1 flag13 level13 7303 Aug 30  2015 level13
[...]
```

We have a binary file.

Let's run it :

```bash
$ ./level13 
UID 2013 started us but we we expect 4242
```

## 3. Analyzing the binary

Using `strings` :

```bash
[...]
getuid
[...]
0123456
UID %d started us but we we expect %d
boe]!ai0FB@.:|L6l@A?>qJ}I
your token is %s
[...]
```

It uses getuid to use our uid.

Let's use gdb to modify our uid and get our flag

## 4. Getting our flag

```bash
$ gdb level13

(gdb) b getuid
(gdb) print $eax
$1 = 1

(gdb) step
(gdb) print $eax
$2 = 2013

(gdb) set $eax=4242
(gdb) print $eax
$3 = 4242

(gdb) step
your token is 2A31L79asukciNyi8uppkEuSx
```

End of simulation