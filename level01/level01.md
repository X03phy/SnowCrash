# Level01

### 1. Identity

	$ id
	uid=2001(level01) gid=2001(level01) groups=2001(level01),100(users)

We are logged as level01.

### 2. Home directory

	$ pwd
	/home/user/level01

	$ ls -la
	...

All files here are standard shell configuration files (.bashrc, .profile, etc.) with no exploitable content.

### 3. Searching files owned by our user

	$ find / -user level01 2>/dev/null
	...
	$ find / -user flag01 2>/dev/null

Nothing interesting here.

### 4. Searching password files

	$ ls -l etc/shadow
	-rw-r----- 1 root shadow 4428 Mar  6  2016 etc/shadow

This file does not have the read permissions.

	$ ls -l etc/passwd
	-rw-r--r-- 1 root root 2477 Mar  5  2016 etc/passwd

This file can be read.

	$ cat etc/passwd
	...
	flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
	...

https://www.cyberciti.biz/faq/understanding-etcpasswd-file-format/

There is one hashed password only for the user flag01.

Let's decode it.

### 5. Decode hashed password

https://man.archlinux.org/man/crypt.5.en#descrypt_(Traditional_DES)

https://tldp.org/HOWTO/Security-HOWTO/password-security.html

Most Unicies (and Linux is no exception) primarily use a one-way encryption algorithm, called DES (Data Encryption Standard) to encrypt your passwords.
This encrypted password is then stored in (typically) /etc/passwd (or less commonly) /etc/shadow.


	42hDRfypTqqnw:abcdefg

### 6. Getting the flag

	$ getflag
	Check flag.Here is your token : f2av5il02puano7naaf6adaaf
