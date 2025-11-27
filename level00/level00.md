# Level00

### 1. Identity

	$ id
	uid=2000(level00) gid=2000(level00) groups=200(level00),100(users)

We are logged as level00.

### 2. Home directory

	$ pwd
	/home/user/level00

	$ ls -la
	...

All files here are standard shell configuration files (.bashrc, .profile, etc.) with no exploitable content.

### 3. Searching files owned by our user

	$ find / -user level00 2>/dev/null

Nothing interesting here.

Since the goal of each level is to obtain the flagXX token, we also search for files belonging to flag00:

	$ find / -user flag00 2>/dev/null
	/usr/sbin/john
	/rofs/usr/sbin/john

Two files appear, one on the live system and one on the read‑only filesystem.

Just to know, rofs means : Read-Only File System. rofs contains an original version of the system.

### 4. Inspecting the files

	$ cat /usr/sbin/john
	cdiiddwpgswtgt
	$ cat /rofs/usr/sbin/john
	cdiiddwpgswtgt

Both files contain the same string.

Trying this as a password for flag00 does not work.
The string looks like a simple substitution cipher, more specifically a Caesar cipher.

### 5. Decoding

Let's decode this using this website : https://www.dcode.fr/chiffre-cesar

Using a Caesar shift of +15 (or -11), the decoded string is:

	nottoohardhere

### 6. Getting the flag

Let's test this to login to flag00.

	$ su flag00
	Password: 
	Don't forget to launch getflag !

It works !!!

	$ getflag
	Check flag.Here is your token : x24ti5gi3x0ol2eh4esiuxias

Flag successfully retrieved.