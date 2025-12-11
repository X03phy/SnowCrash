# Level13

## 1. Identity

```bash
$ id
uid=2014(level14) gid=2014(level14) groups=2014(level14),100(users)
```

We are logged in as **level14**.

## 2. Home directory

```bash
$ pwd
/home/user/level14

$ ls -la
[...]
```

Nothing here

```bash
$ find / -user level14 2>/dev/null
[...]
$ find / -user flag14 2>/dev/null
[...]
```

Nothing interesting here, let's check `/bin/getflag`

## 3. Analyzing the binary

Using `gdb` :

```bash
gdb /bin/getflag

(gdb) run
You should not reverse this
```

Clearly, our debugging is being blocked.

Let's see why :

```bash
(gdb) disas main
[...]
0x08048989 <+67>:	call   0x8048540 <ptrace@plt>
[...]

```

`ptrace` is blocking our access.

We also have this info :

```bash
$ id flag14
uid=3014(flag14) gid=3014(flag14) groups=3014(flag14),1001(flag)
```

```bash

Let's bypass it :

```bash
(gdb) catch syscall ptrace
(gdb) commands 1
> set ($eax) = 0
> continue
> end
```

## 4. Getting our flag

It uses getuid to use our uid.

Let's use gdb to modify our uid and get our flag

```bash
(gdb) b getuid
(gdb) run
(gdb) step
(gdb) print $eax
$1 = 2014

(gdb) set $eax = 3014
(gdb) step
Check flag.Here is your token : 7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ
```

End of simulation