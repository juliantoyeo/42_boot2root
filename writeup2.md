# Write Up 2

After some search on google for "gain root access linux hack"

This website "https://book.hacktricks.xyz/linux-unix/privilege-escalation" mentioned a CVE (Common Vulnerabilities and Exposures) called dirty cow CVE-2016-5195 (DirtyCow)

The CVE DirtyCow can be used to do "Linux Privilege Escalation" if the linux Kernel is a older version then 3.19.0-73.8

# Once upon a time there is famous vulnerability on linux called dirty cow.

```
Dirty COW (Dirty copy-on-write) is a computer security vulnerability for the Linux kernel that affected all Linux-based operating systems, including Android devices, that used older versions of the Linux kernel created before 2018. It is a local privilege escalation bug that exploits a race condition in the implementation of the copy-on-write mechanism in the kernel's memory-management subsystem. Computers and devices that still use the older kernels remain vulnerable.

The vulnerability was discovered by Phil Oester.Because of the race condition, with the right timing, a local attacker can exploit the copy-on-write mechanism to turn a read-only mapping of a file into a writable mapping. Although it is a local privilege escalation, remote attackers can use it in conjunction with other exploits that allow remote execution of non-privileged code to achieve remote root access on a computer. The attack itself does not leave traces in the system log.

The vulnerability has the Common Vulnerabilities and Exposures designation CVE-2016-5195. Dirty Cow was one of the first security issues transparently fixed in Ubuntu by the Canonical Live Patch service.

The vulnerability has existed in the Linux kernel since version 2.6.22 released in September 2007, and there is information about it being actively exploited at least since October 2016. The vulnerability has been patched in Linux kernel versions 4.8.3, 4.7.9, 4.4.26 and newer.

The patch produced in 2016 did not fully address the issue and a revised patch was released on November 27, 2017, before public dissemination of the vulnerability.
```


source vulnerability : https://github.com/dirtycow/dirtycow.github.io/wiki/VulnerabilityDetails

source forum : https://github.com/FireFart/dirtycow/blob/master/dirty.c
source github exploit : https://github.com/dirtycow/dirtycow.github.io/wiki/PoCs
source github code exploit : https://github.com/FireFart/dirtycow/blob/master/dirty.c

# Can we try the same technique ? -

I checked the kernel version to see if any vulnerability exist

check kernel version : `uname –r`

and we have : `3.2.0-91-generic-pae`

source check kernel version : https://phoenixnap.com/kb/check-linux-kernel-version

so this vulnerability does exsit

#  --------------------

from above resource, we have code in dirty.c like https://github.com/FireFart/dirtycow/blob/master/dirty.c

#  Explaination

Base on the explaination from this youtuber "https://www.youtube.com/watch?v=kEsshExn7aE"

The dirtyCow is using the race condition with 2 thread,

<h3>First thread</h3>

`map = mmap(NULL, st.st_size + sizeof(long), PROT_READ, MAP_PRIVATE, f, 0)`

nmap is the foundation of malloc which will set aside an allocated zone where the program could use to do data manipulation,

PROT_READ means that the memory is read only, but MAP_PRIVATE will allow the program to `copy-on-write` (COW) which will create a copy to write on, instead of writing directly on the data itself.

But copy of data will require some time, so this is the condition were the 2nd thread is trying to race on.

<h3>Second thread</h3>

`madvise(map, 100, MADV_DONTNEED)`

madvise is memory advice, which as the name suggest will give advice on how the memory will behave,

Here it advice that first 100 bytes is probably `Not needed` so it is available to be use.


Combining the 2 thread, what will normally happens is that we will make the program to do a write on the memory, which MAP_PRIVATE will cause a copy of the data to be created which will be used to write on,

Next `madvise` will mark the 1st 100bytes as `Not needed` so this allocated zone will be available to be use.

But on a rare case where the 2nd thread catched up on the 1st thread while it is creating a copy,

The copied data will be marked as `Not needed` and the 1st thread will write to the original read only data, instead of the copied data.

This will cause the file that normally could not be written on become overwritten, this completing the exploit

with this, we just have to compile it with : `gcc -pthread dirty.c -o dirty -lcrypt`

Now, just run the binary with `./dirty`, enter the password for new user, or leave it blank

Depending on the machine, this might take several minutes, so grab a coffee and wait the exploit to work :)

```console
laurie@BornToSecHackMe:~$ ./dirty
/etc/passwd successfully backed up to /tmp/passwd.bak
Please enter the new password:
Complete line:
firefart:figsoZwws4Zu6:0:0:pwned:/root:/bin/bash

mmap: b7fda000
madvise 0

ptrace 0
Done! Check /etc/passwd to see if the new user was created.
You can log in with the username 'firefart' and the password ''.


DON'T FORGET TO RESTORE! $ mv /tmp/passwd.bak /etc/passwd
Done! Check /etc/passwd to see if the new user was created.
You can log in with the username 'firefart' and the password ''.


DON'T FORGET TO RESTORE! $ mv /tmp/passwd.bak /etc/passwd
```

Since in the original c code, we use `firefart` as username
so now we can use this username and the password we just creacted : `su firefart` , we succsufully logged in
`whoami`
we have
`firefart`
use command id: `id`, we have:
`uid=0(firefart) gid=0(root) groups=0(root)`
we are root

restore the password:
`mv /tmp/passwd.bak /etc/passwd`

Now whe have another root access !! 🥳 🎉 🎉 🎉
