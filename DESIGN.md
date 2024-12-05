# FLASH Memory Instructions List

/ Device Reset 						FFh
/ JEDEC ID 							9Fh Dummy EFh AAh 21h
/ Read Status Register 				0Fh/05h SR Addr S7-0 S7-0 S7-0 S7-0 S7-0 S7-0 S7-0
/ Write Status Register 			1Fh/01h SR Addr S7-0
/ Write Enable 						06h
/ Write Disable 					04h
* BB Management (Swap Blocks)		A1h LBA LBA PBA PBA
* Read BBM LUT 						A5h Dummy LBA0 LBA0 PBA0 PBA0 LBA1 LBA1 PBA1
* Last ECC failure (Page Address)	A9h Dummy PA15-8 PA7-0 				
/ Block Erase 						D8h Dummy PA15-8 PA7-0
* Program Data Load(Reset Buffer)	02h CA15-8 CA7-0 Data-0 Data-1 Data-2 Data-3 Data-4 Data-5
* Random Program (Data Load)		84h CA15-8 CA7-0 Data-0 Data-1 Data-2 Data-3 Data-4 Data-5
* Program Execute 					10h Dummy PA15-8 PA7-0
* Page Data Read 					13h Dummy PA15-8 PA7-0
* Read 								03h Dummy Dummy Dummy D7-0 D7-0 D7-0 D7-0 D7-0
* Fast Read 						0Bh Dummy Dummy Dummy Dummy D7-0 D7-0 D7-0 D7-0