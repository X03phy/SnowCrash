# Level11

## 1. Identity

```bash
$ id
uid=2011(level11) gid=2011(level11) groups=2011(level11),100(users)
```

We are logged in as **level11**.

## 2. Home directory

```bash
$ pwd
/home/user/level11

$ ls -la
[...]
-rwsr-sr-x  1 flag11  level11  668 Mar  5  2016 level11.lua
[...]
```

## 3. Analyzing the lua file

About lua files : [Wikipedia](https://fr.wikipedia.org/wiki/Lua)

This file creates a local server with an IP adress and a port so let's listen it with netcat and try to understand how we can get our flag.

## 4. Testing it with netcat

```bash