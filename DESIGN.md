# FLASH Memory Instructions List

/ Device Reset___________|FFh
/ JEDEC ID_______________|9Fh Dummy EFh AAh 21h
/ Read Status Register___|0Fh/05h SR Addr S7-0 S7-0 S7-0 S7-0 S7-0 S7-0 S7-0
/ Write Status Register__|1Fh/01h SR Addr S7-0
/ Write Enable___________|06h
/ Write Disable__________|04h
* BB Management__________|A1h LBA LBA PBA PBA
* Read BBM LUT___________|A5h Dummy LBA0 LBA0 PBA0 PBA0 LBA1 LBA1 PBA1
* Last ECC failure_______|A9h Dummy PA15-8 PA7-0 				
/ Block Erase____________|D8h Dummy PA15-8 PA7-0
/ Program Data Load______|02h CA15-8 CA7-0 Data-0 Data-1 Data-2 Data-3 Data-4 Data-5
* Random Program_________|84h CA15-8 CA7-0 Data-0 Data-1 Data-2 Data-3 Data-4 Data-5
/ Program Execute________|10h Dummy PA15-8 PA7-0
/ Page Data Read_________|13h Dummy PA15-8 PA7-0
/ Read___________________|03h Dummy Dummy Dummy D7-0 D7-0 D7-0 D7-0 D7-0
* Fast Read______________|0Bh Dummy Dummy Dummy Dummy D7-0 D7-0 D7-0 D7-0