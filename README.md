# Windows Privilege Escalation Labs

The Windows labs make use of modified Microsoft modern.ie virtual machines hosted in Vagrant Cloud.

## Getting Started

You will require a few packages to be installed before we kick off, they are listed below.

### Prerequisites

The following packages will need to be installed:

```
Virtual Box
Vagrant
Internets
```
This can be acheived by running the following on an elevated Windows command line:

```
@"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))" && SET "PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin"
choco install virtualbox vagrant -y
```

### Running

Once the labs are cloned, they are pretty simple to run. Simply navigate to the directory where they are and run the following

```
C:\git\Windows-Privilege-Escalation-Labs> set LabIndex=0 && vagrant up
```
The 'LabIndex' is maps to the corresponding Lab file within the labs folder. There are powershell scripts that make various changes to the operating system within the the virtual machine. Within the VagrantFile, there is a difficulty index as well, change from 0 to 1 to slightly increase the difficulty of the labs. This mainly enables some security controls within Windows, like Anti-Virus.

The initial 'vagrant up' will pull down the 50Gb image off vagrant cloud, so go make a cup of tea and watch a short Netflix series.

Once you have verified that everything is work, you can change the lab index and proceed to the next one. 

```
C:\git\Windows-Privilege-Escalation-Labs> vagrant destroy -f
C:\git\Windows-Privilege-Escalation-Labs> set LabIndex=1 && vagrant up
```

Gladly accepting Pull Requests for bug fixes, but especially vulnerables labs. The image has chocolatey installed, so you can install any package you need during the vagrant up phase.
