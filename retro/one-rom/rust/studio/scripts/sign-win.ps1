#!/usr/bin/env pwsh
#Requires -Version 5.0

# Signs One ROM Studio for Windows
#
# Used for both the application and installer executables

$ErrorActionPreference = "Stop"

# Get and check filename arg
$FileName = $args[0]
if (-not $FileName) {   
    Write-Error "No filename specified."
    exit 1
}

# Path to signtool.exe
$SignToolPath = "C:\Program Files (x86)\Windows Kits\10\bin\10.0.26100.0\x64\signtool.exe"

# SHA1 of the code signing certificate
# "Open Source Developer, Piers Finlayson"
$KeySHA1 = "3ec83ab1684d6cb49b81e9736585f46da999ac9e"

# Call signtool to sign the file
& $SignToolPath sign /sha1 $KeySHA1 /fd SHA256 /tr http://timestamp.digicert.com /td SHA256 $FileName

if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
