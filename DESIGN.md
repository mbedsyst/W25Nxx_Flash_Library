# FLASH Memory Instructions List

/ Device Reset____________________|FFh
/ JEDEC ID________________________|9Fh Dummy EFh AAh 21h
/ Read Status Register____________|0Fh/05h SR Addr S7-0 S7-0 S7-0 S7-0 S7-0 S7-0 S7-0
/ Write Status Register___________|1Fh/01h SR Addr S7-0
/ Write Enable____________________|06h
/ Write Disable___________________|04h
* BB Management___________________|A1h LBA LBA PBA PBA
* Read BBM LUT____________________|A5h Dummy LBA0 LBA0 PBA0 PBA0 LBA1 LBA1 PBA1
* Last ECC failure________________|A9h Dummy PA15-8 PA7-0 				
/ Block Erase_____________________|D8h Dummy PA15-8 PA7-0
/ Program Data Load_______________|02h CA15-8 CA7-0 Data-0 Data-1 Data-2 Data-3 Data-4 Data-5
* Random Program__________________|84h CA15-8 CA7-0 Data-0 Data-1 Data-2 Data-3 Data-4 Data-5
/ Program Execute_________________|10h Dummy PA15-8 PA7-0
/ Page Data Read__________________|13h Dummy PA15-8 PA7-0
/ Read____________________________|03h Dummy Dummy Dummy D7-0 D7-0 D7-0 D7-0 D7-0
* Fast Read_______________________|0Bh Dummy Dummy Dummy Dummy D7-0 D7-0 D7-0 D7-0