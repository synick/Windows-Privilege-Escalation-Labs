# Lab 1 - Information Leakage
# Here be spoliers, if you are really really stuck then you can have a look here. Otherwise, keep trying.































































# Enable the Administrator user.
net user Administrator ThisIsThePasswordYouAreLookingFor!! /active:yes


# Add some data to be found.
reg add HKLM\Software\VNCServer
reg add HKLM\Software\VNCServer /v VNCPassword /d "ThisIsThePasswordYouAreLookingFor!!"
reg add HKLM\Software\VNCServer /v Version /d "v 1.0"
reg add HKLM\Software\VNCServer /v Host /d "localhost"
reg add HKLM\Software\VNCServer /v Username /d "Administrator"
reg add HKLM\Software\VNCServer /v Author /d "Indi Gogo"