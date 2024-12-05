# FLASH Memory Instructions List

/ Device Reset______________________|FFh
/ JEDEC ID__________________________|9Fh Dummy EFh AAh 21h
/ Read Status Register______________|0Fh/05h SR Addr S7-0 S7-0 S7-0 S7-0 S7-0 S7-0 S7-0
/ Write Status Register_____________|1Fh/01h SR Addr S7-0
/ Write Enable______________________|06h
/ Write Disable_____________________|04h
* BB Management (Swap Blocks)_______|A1h LBA LBA PBA PBA
* Read BBM LUT______________________|A5h Dummy LBA0 LBA0 PBA0 PBA0 LBA1 LBA1 PBA1
* Last ECC failure (Page Address)___|A9h Dummy PA15-8 PA7-0 				
/ Block Erase_______________________|D8h Dummy PA15-8 PA7-0
* Program Data Load(Reset Buffer)___|02h CA15-8 CA7-0 Data-0 Data-1 Data-2 Data-3 Data-4 Data-5
* Random Program (Data Load)________|84h CA15-8 CA7-0 Data-0 Data-1 Data-2 Data-3 Data-4 Data-5
* Program Execute___________________|10h Dummy PA15-8 PA7-0
* Page Data Read____________________|13h Dummy PA15-8 PA7-0
* Read_ ____________________________|03h Dummy Dummy Dummy D7-0 D7-0 D7-0 D7-0 D7-0
* Fast Read_________________________|0Bh Dummy Dummy Dummy Dummy D7-0 D7-0 D7-0 D7-0