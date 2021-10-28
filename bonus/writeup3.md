# the secret of booting

during the booting of the VM, press `shift` key to trigger the boot loader
so we have `boot:` in our VM

init is responsible for all the system startup and creating a usable environment.
init= can take any executable, including shell scripts.
so we make it to `live init=/bin/sh`

and then, we try
`whoami`
we have
`root`

```sh
boot: live init=/bin/sh
/bin/sh: 0: can not access tty; job control turned off
# whoami
root
#
```sh