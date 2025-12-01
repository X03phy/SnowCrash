# Level01

### 1. Identity

	$ id
	uid=2002(level02) gid=2002(level02) groups=2002(level02),100(users)

We are logged as **level02**.

### 2. Home directory

	$ pwd
	/home/user/level02

	$ ls -l
	...
	----r--r-- 1 flag02  level02 8302 Aug 30  2015 level02.pcap
	...

All files here are standard shell configuration files (.bashrc, .profile, etc.) with no exploitable content except for one : **level02.pcap**.

A PCAP (Packet Capture) file contains recorded raw network packets.

**More details:**

https://www.sysdig.com/learn-cloud-native/what-is-a-pcap-file


To analyze this file, we need to export it to our host machine and open it in **Wireshark**.

### 3. Analyze file with Wireshark

To extract the file from our VM to our PC, we do :

	dewqdew
	deew
	


	kooda2puivaav1idi4f57q8iq