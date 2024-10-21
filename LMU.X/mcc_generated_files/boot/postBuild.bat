Set reset=[0m
Set cyan=[46m
Set compilerDir=%1
Set projectDir=%~2
Set imageDir=%~3
Set imageName=%~4
Set isDebug=%5
if %isDebug%=="true" (
echo %cyan% NOTE: You have built in DEBUG mode, therefore a .hex file was not generated. If you would like to generate a .hex file, please build in production mode. For more information, please open MCC and click on the question mark symbol next to the 16-bit Bootloader Library under Resource Management. %reset%
exit 0
)
hexmate r0-4FFF,"%projectDir%\%imageDir%\%imageName%" r5008-FFFFFFFF,"%projectDir%\%imageDir%\%imageName%" -O"%projectDir%\%imageDir%\temp_original_copy.X.production.hex" -FILL=w1:0x00,0x00,0x00,0x00@0x5000:0x5007
hexmate r5000-FFFFFFFF,"%projectDir%\%imageDir%\temp_original_copy.X.production.hex" -O"%projectDir%\%imageDir%\temp_crc.X.production.hex" -FILL=w1:0xFF,0xFF,0xFF,0x00@0x5000:0xAEFFF +-CK=5000-AEFFF@AF000w-4g5p814141AB
hexmate rAF000-AF001s-AA000,"%projectDir%\%imageDir%\temp_crc.X.production.hex" rAF002-AF003s-A9FFE,"%projectDir%\%imageDir%\temp_crc.X.production.hex" r5006-FFFFFFFF,"%projectDir%\%imageDir%\%imageName%" r5002-5003,"%projectDir%\%imageDir%\%imageName%" r0-4FFF,"%projectDir%\%imageDir%\%imageName%" -O"%projectDir%\%imageDir%\%imageName%"
del "%projectDir%\%imageDir%\temp_original_copy.X.production.hex"
del "%projectDir%\%imageDir%\temp_crc.X.production.hex"