# Level08

### 1. Identity

```bash
$ id
uid=2009(level09) gid=2009(level09) groups=2009(level09),100(users)
```

We are logged in as **level09**.

### 2. Home directory

```bash
$ pwd
/home/user/level09

$ ls -la
...
-rwsr-sr-x 1 flag09  level09 7640 Mar  5  2016 level09
----r--r-- 1 flag09  level09   26 Mar  5  2016 token
...
```

Let's execute this binary :

```bash
$ ./level08 token
You may not access 'token'
```

### 3. Analyzing the files

`token` contains a cryptic message.

Testing our file gives us :

```bash
$ ./level09 
You need to provied only one arg.

./level09 hello
hfnos

./level09 aaaaaa
abcdef
```

It looks like our program is encrypting our first argument.
It adds to each letter of our word its index.

```bash
./level09 `cat token`
f5mpq;v�E��{�{��TS�W�����
```

Testing it with `token` does not give us anything.

The message in `token` is probably the outpu of our binary.

We have to create a function that reverses our binary logic and decrypt our message.

### 4. Coding

Here is our code in C :

```c
#include <stdio.h>

int main(int argc, char **argv)
{
	int i;

	if (argc != 2)
		return 1;
	i = 0;
	while (argv[1][i])
	{
		printf("%c", (argv[1][i] - i));
		i++;
	}
	printf("\n");
	return 0;
}
```

Let's create a binary to use :

```bash
$ gcc crypto.c
```

### 5. Getting the flag

Using our binary with token gives us :

```bash
$ ./a.out token
f3iji1ju5yuevaus41q1afiuq
```

We can now login to flag09 and use `getflag` :

```bash
$ su flag09

Password: f3iji1ju5yuevaus41q1afiuq
Don't forget to launch getflag !

$ getflag
Check flag.Here is your token : s5cAJpM8ev6XHw998pRWG728z
```

Yaaaayyyy !!!