# Level02

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

### 3. Extracting the PCAP file

We copy the file from the VM to our local machine using SCP:

	scp -P 4243 level02@127.0.0.1:/home/user/level02/level02.pcap ~/snowcrash/

### 4. Analyzing the PCAP with Wireshark

To analyze the **.pcap** file, open it with Wireshark and follow the TCP stream:

	Analyze -> Follow -> TCP Stream

This shows the data sent by the client :

	ft_wandr...NDRel.L0L

The password seems to contain dots (.), but trying it directly fails :

	$ su flag02
	Password: ft_wandr...NDRel.L0L
	su: Authentication failure

**Why do we see dots?**

Wireshark displays non-printable ASCII characters as dots.
By switching the display to Hex Dump (bottom section), we can view the raw bytes.

Each dot (.) corresponds to the byte :

	7F

Hex 7F is ASCII DEL, meaning a delete/backspace character.

So the user actually typed:
- A few characters,
- Then pressed Backspace (DEL),
- Then continued typing.

After removing the deleted chars, the real password becomes:

	ft_waNDReL0L


### 5. Getting the flag

	$ su flag02
	Password: ft_waNDReL0L

	$ getflag
	Check flag.Here is your token : kooda2puivaav1idi4f57q8iq

Flag successfully retrieved.