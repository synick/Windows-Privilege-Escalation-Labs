# Chaining Multiple Vulnerabilities to gain Administrator password



















































































































































mkdir c:\Users\IEUser\Documents\Share
mkdir c:\Users\IEUser\Documents\Testing
mkdir c:\Users\IEUser\Documents\Transfer
copy c:\vagrant\labfiles\lab8\Backup.xml C:\Users\IEUser\Documents\Transfer\
net share Backup=C:\Users\IEUser\Documents

# Enable the Administrator user.
net user Administrator Password1 /active:yes
net user sshd_server ThisIsAReallyGoodPassword /active:yes

# Insert run script in to IEUser's Startup Directory
$acl = Get-Acl HKLM:\SYSTEM\CurrentControlSet\Services\OpenSSHd
$rule = New-Object System.Security.AccessControl.RegistryAccessRule ("sshd_server","FullControl","Allow")
$acl.SetAccessRule($rule)
$acl |Set-Acl -Path HKLM:\SYSTEM\CurrentControlSet\Services\OpenSSHd

#Enable Applocker
Import-Module AppLocker
Set-AppLockerPolicy -XmlPolicy C:\vagrant\labfiles\lab8\lab8-AppLocker.xml
Set-Service -Name AppIDSVC -StartupType Automatic
