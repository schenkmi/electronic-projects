# RemoteX with HP16702B Logic Analyzer
Date: 2021.04.29

For Ubuntu 16.04 (https://askubuntu.com/questions/34657/how-to-make-x-org-listen-to-remote-connections-on-port-6000)

The goal is that the XServer from Ubuntu listen to TCP:6000
```
netstat -an | grep -F 6000
```

## Preparing

### Create/edit /etc/lightdm/lightdm.conf
```
sudo vi /etc/lightdm/lightdm.conf
```
```
[Seat:*]

xserver-allow-tcp=true
xserver-command=X -listen tcp
```

### Create/edit /etc/lightdm/lightdm.conf.d/50-xserver-command.conf
```
sudo vi /etc/lightdm/lightdm.conf.d/50-xserver-command.conf
```
```
[Seat:*]

xserver-command=X -core -listen tcp
```

### Reboot
After reboot check if tcp listening on port 6000 by
```
 netstat -nal | grep 6000
```
Sould look like
```
tcp        0      0 0.0.0.0:6000            0.0.0.0:*               LISTEN
tcp6       0      0 :::6000                 :::*                    LISTEN
```

## Connect

On Linux PC (Ubuntu) allow X connection with
```
xhost +
```

Login to HP16702B (192.168.0.7)
```
telnet 192.168.0.7
```
Username: root
Password: uh,uhuh

On HP16702B start the session with (192.168.0.189 is the IP of the Linux PC)
```
export DISPLAY=192.168.0.189:0.0
vp &
```
