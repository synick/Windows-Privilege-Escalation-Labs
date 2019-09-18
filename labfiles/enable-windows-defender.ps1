Get-Service WinDefend | Set-Service -StartupType Automatic
Get-Service WinDefend | Start-Service -PassThru