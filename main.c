/* SPDX-License-Identifier: Apache-2.0 */
/**
 * @file 		pcie.c
 *
 * @brief 		Code file for PCIe Config space operations
 *
 * @copyright 	Copyright (C) 2024 Jackrabbit Founders LLC. All rights reserved.
 *
 * @date 		Jan 2024
 * @author 		Barrett Edwards <code@jrlabs.io>
 * 
 */

/* INCLUDES ==================================================================*/

/* printf()
 */
#include <stdio.h>

#include <arrayutils.h>

#include "main.h"

/* MACROS ====================================================================*/

#define MAX_INDENT 32

/* ENUMERATIONS ==============================================================*/

/* STRUCTS ===================================================================*/

/* PROTOTYPES ================================================================*/

/* GLOBAL VARIABLES ==========================================================*/

/**
 * String representation of _PCAP 
 *
 * These are 8-bit IDs 
 */
const char *STR_PCAP[] = { 
	"PCI Power Management Interface",			// 0x01
	"Accelerated Graphics Port",      			// 0x02
	"Vital Product Data",      					// 0x03
	"Slot Numbering (for Bridge)",   			// 0x04
	"Message Signaled Interrupts",      		// 0x05
	"CompactPCI Hot Swap",    					// 0x06
	"PCI-X (Deprecated)",     					// 0x07
	"HyperTransport (Deprecated)",       		// 0x08
	"Vendor Specific",     						// 0x09
	"Debug port",      							// 0x0a
	"CompactPCI central resource control", 		// 0x0b
	"PCI Hot-Plug (Deprecated)",  				// 0x0c
	"PCI Bridge Subsystem Vendor ID",    		// 0x0d
	"AGP 8x (Deprecated)",     					// 0x0e
	"Secure Device (Deprecated)",   			// 0x0f
	"PCI Express",      						// 0x10
	"MSI-X",     								// 0x11
	"Serial ATA Data/Index Configuration",   	// 0x12
	"Conventional PCI Advanced Features (AF)", 	// 0x13
	"Enhanced Allocation",      				// 0x14
	"Flattening Portal Bridge"      			// 0x15
};

/**
 * String representation of _PCEC 
 *
 */
const char *STR_PCEC[] = {
	"Advanced Error Reporting",								// 0x0001	
	"Virtual Channel (VC)",                                 // 0x0002
	"Device Serial Number",                                 // 0x0003
	"Power Budgeting",                                      // 0x0004
	"Root Complex Link Declaration",                        // 0x0005
	"Root Complex Internal Link Control",                   // 0x0006
	"Root Complex Event Collector Endpoint Association",    // 0x0007
	"Multi-Function Virtual Channel (MFVC)",                // 0x0008
	"Virtual Channel (VC)",                                 // 0x0009
	"Root Complex Register Block (RCRB) Header",            // 0x000a
	"Vendor-Specific Extended Capability (VSEC)",           // 0x000b
	"Access Control Services (ACS)",                        // 0x000d
	"Alternative Routing-ID Interpretation (ARI)",          // 0x000e
	"Address Translation Services (ATS)",                   // 0x000f
	"Single Root I/O Virtualization (SR-IOV)",              // 0x0010
	"Multi-Root I/O Virtualization (MR-IOV) (Deprecated)",  // 0x0011
	"Multicast",                                            // 0x0012
	"Page Request Interface (PRI)",                         // 0x0013
	"Resizable BAR",                                        // 0x0015
	"Dynamic Power Allocation (DPA)",                       // 0x0016
	"TPH Requester",                                        // 0x0017
	"Latency Tolerance Reporting (LTR)",                    // 0x0018
	"Secondary PCI Express",                                // 0x0019
	"Protocol Multiplexing (PMUX)",                         // 0x001a
	"Process Address Space ID (PASID)",                     // 0x001b
	"LN Requester (LNR)",                                   // 0x001c
	"Downstream Port Containment (DPC)",                    // 0x001d
	"L1 PM Substates",                                      // 0x001e
	"Precision Time Measurement (PTM)",                     // 0x001f
	"PCI Express over M-PHY (M-PCIe)",                      // 0x0020
	"FRS Queueing",                                         // 0x0021
	"Readiness Time Reporting",                             // 0x0022
	"Designated Vendor-Specific Extended Capability",       // 0x0023
	"VF Resizable BAR",                                     // 0x0024
	"Data Link Feature",                                    // 0x0025
	"Physical Layer 16.0 GT/s",                             // 0x0026
	"Lane Margining at the Receiver",                       // 0x0027
	"Hierarchy ID",                                         // 0x0028
	"Native PCIe Enclosure Management (NPEM)",              // 0x0029
	"Physical Layer 32.0 GT/s",                             // 0x002A
	"Alternate Protocol",                                   // 0x002B
	"System Firmware Intermediary (SFI)",                   // 0x002C
	"Shadow Functions",                                     // 0x002D
	"Data Object Exchange",                                 // 0x002E
	"Device 3",                                             // 0x002F
	"Integrity and Data Encryption (IDE)",                  // 0x0030
	"Physical Layer 64.0 GT/s Capability",                  // 0x0031
	"Flit Logging",                                         // 0x0032
	"Flit Performance Measurement",                         // 0x0033
	"Flit Error Injection"                                  // 0x0034
};

/**
 * String representation of PCI Sub Class Code for Memory Controllers (MC)
 *
 * Class Code 0x05
 */
const char *STR_PCMC[] =
{
	"Ram", 				// 0x00
	"Flash",			// 0x01
	"CXL Memory",		// 0x02
	"Other Memory",		// 0x80
};


/**
 * String representations of PCI Programming Interface for Sub Class: CXL memory (CX)
 * 
 * Class Code: 		0x05
 * Sub Class code 	0x02
 */
const char *STR_PCCX[] =
{
	"Vendor Specific Interface)",	// 0x00
	"CXL 2.0 or later"				// 0x01
};

/**
 * String representation of PCI Sub Class Code for Mass Storage Controllers (MS)
 *
 * Class Code 0x01
 */
const char *STR_PCMS[] =
{
	"SCSI Device or Controller", 							// 0x00 
	"IDE Controller", 										// 0x01 
	"Floppy Disk Controller - Vendor Specific Interface", 	// 0x02 
	"IPI Bus Controller - Vendor Specific Interface", 		// 0x03 
	"RAID Controller - Vendor Specific Interface", 			// 0x04  
	"ATA Controller",										// 0x05 
	"SATA Controller",										// 0x06 
	"SAS Controller",										// 0x07 
	"Non-Volatile Memory Subsystem",						// 0x08 
	"Universal Flash Storage Controller",					// 0x09  
	"Other Mass storage Controller" 						// 0x80 
};

/**
 * String representation of PCI Sub Class Code for Network Controllers (NC)
 *
 * Class Code 0x02
 */
const char *STR_PCNC[] =
{
	"Ethernet Controller", 							// 0x00 
	"Token Ring Controller", 						// 0x01 
	"FDDI Controller", 								// 0x02 
	"ATM Controller", 								// 0x03 
	"ISDN Controller", 								// 0x04 
	"WorldFip Controller", 							// 0x05 
	"PICMG", 										// 0x06 
	"InfiniBand Controller", 						// 0x07 
	"Host fabric Controller - Vendor Specific", 	// 0x08 
	"Other Network Controller" 						// 0x80 
};

/**
 * String representation of PCI Sub Class Code for Dispaly Controllers (DC)
 *
 * Class Code 0x03
 */
const char *STR_PCDC[] =
{
	"VGA Compatible Controller", 	// 0x00 
	"XGA Controller", 				// 0x01 
	"3D Controller", 				// 0x02 
	"Other Controller" 				// 0x80 
};

/**
 * String representation of PCI Sub Class Code for Multimedia Controllers (UC)
 *
 * Class Code 0x04
 */
const char *STR_PCUC[] =
{
	"Video Device", 				// 0x00
	"Audio Device", 				// 0x01
	"Computer Telephone Device", 	// 0x02
	"HD Audio Device", 				// 0x03
	"Other Multimedia device", 		// 0x80
};

/**
 * String representation of PCI Sub Class Code for Bridge Devices (BD) 
 *
 * Class Code 0x06
 */
const char *STR_PCBD[] =
{
	"Host Bridge", 								// 0x00 
	"ISA Bridge", 								// 0x01 
	"EISA", 									// 0x02 
	"MCA", 										// 0x03 
	"PCI-to-PCI Bridge", 						// 0x04 
	"PCMCIA Bridge", 							// 0x05 
	"NuBus Bridge", 							// 0x06 
	"CardBus Bridge", 							// 0x07 
	"RaceWay Bridge", 							// 0x08 
	"Semi-Transparent Bridge", 					// 0x09 
	"InfiniBand to PCI Host Bridge", 			// 0x0A 
	"Advanced Switching to PCI Host Bridge", 	// 0x0B 
	"Other Bridge", 							// 0x80 
};
 
/**
 * String representation of PCI Sub Class Code for Simple Communication Controllers (SC)
 *
 * Class Code 0x07
 */
const char *STR_PCSC[] =
{
	"Generic XT Compatible Serial Controller", 	// 0x00 
	"Parallel Port", 							// 0x01 
	"Multi Port Serial Controller", 			// 0x02 
	"Generic Modem", 							// 0x03 
	"GPIB Controller", 							// 0x04 
	"SMART Card", 								// 0x05 
	"Other Communcations Device"  				// 0x80 
};

/**
 * String representation of PCI Sub Class Code for Generic System Peripherals (SP)
 *
 * Class Code 0x08
 */
const char *STR_PCSP[] =
{
	"Programmable Interrupt Controller", 		// 0x00 
	"DMA Controller", 							// 0x01 
	"System Timer", 							// 0x02 
	"Generic Real Time Clock (RTC) Controller", // 0x03 
	"Generic PCI Hot Plug Contoller", 			// 0x04 
	"SD Host Controller", 						// 0x05 
	"IOMMU", 									// 0x06 
	"Root Complex Event Collector", 			// 0x07 
	"Other System Peripheral" 					// 0x08   
};

/**
 * String representaton of PCI Sub Class Code for Input Device (ID)
 *
 * Class Code 0x09
 */
const char *STR_PCID[] =
{
	"Keyboard Controller", 	// 0x00 
	"Digitizer (pen)", 		// 0x01 
	"Mouse Controller", 	// 0x02 
	"Scanner Controller", 	// 0x03 
	"Gameport Controller", 	// 0x04 
	"Other Controller" 		// 0x80 
};

/**
 * String representation of PCI Sub Class Code for Docking Stations (DS)
 *
 * Class Code 0x0A
 */
const char *STR_PCDS[] = 
{
	"Generic Docking Station", 			// 0x00 
	"Other type of Docking Station", 	// 0x01 
};

/**
 * PCI Sub Class Code for Processors (PR)
 *
 * Class Code 0x0B
 */
const char *STR_PCPR[] = 
{
	"386", 					// 0x00 
	"486", 					// 0x01 
	"Pentium", 				// 0x02 
	"Alpha", 				// 0x10 
	"PowerPC", 				// 0x20 
	"MIPS", 				// 0x30 
	"Co-Processor", 		// 0x40 
	"Other Processor"  		// 0x80 
};

/**
 * String representation of PCI Sub Class Code for Serial Bus Controllers (SB)
 *
 * Class Code 0x0C
 */
const char *STR_PCSB[] = 
{
	"Firewire", 				// 0x00 
	"ACCESS.bus", 				// 0x01 
	"SSA", 						// 0x02 
	"USB", 						// 0x03 
	"Fibre Channel", 			// 0x04 
	"SM Bus", 					// 0x05 
	"Infiniband (Depricated)", 	// 0x06 
	"IPMI", 					// 0x07 
	"SERCOS", 					// 0x08 
	"CANbus", 					// 0x09 
	"MIPI I3C Controller", 		// 0x0A 
	"OTher Controller"  		// 0x80 
};

/**
 * String representation of PCI Sub Class Code for Wireless Controllers (WC)
 *
 * Class Code 0x0D
 */
const char *STR_PCWC[] =
{
	"iRDA Compatible Controller", 		// 0x00 
	"IR Controller", 					// 0x01 
	"RF Controller", 					// 0x10 
	"Bluetooth", 						// 0x11 
	"Broadband", 						// 0x12 
	"Ethernet 5 GHz", 					// 0x20 
	"Ethernet 2.4 GHz", 				// 0x21 
	"Cellular Controller / Modem", 		// 0x40 
	"Cellular Controller + Ethrenet", 	// 0x41 
	"Other Wireless Controller", 		// 0x80 
};

/**
 * String representation of PCI Sub Class Code for Intelligent IO Controllers (IO)
 *
 * Class Code 0x0E
 */
const char *STR_PCIO[] =
{
	"Intelligent IO", // 0x00 
};

/**
 * String represenation of PCI Sub Class Code for Satellite Controllers (SA)
 *
 * Class Code 0x0F
 */
const char *STR_PCSA[] = 
{
	"TV", 		// 0x01 
	"Audio", 	// 0x02 
	"Voice", 	// 0x03 
	"Data", 	// 0x04 
	"Other"  	// 0x80 
};


/**
 * String representation of PCI Sub Class Code for Encryption Controllers (EN)
 *
 * Class Code 0x10
 */
const char *STR_PCEN[] =
{
	"Network and Computing Encryption Decryption controller", 	// 0x00 
	"Entertainment encryption and decryption controller", 		// 0x10 
	"Other encryption and decryption controller", 				// 0x80 
};

/**
 * String representation of PCI Sub Class Code for Data Acquisition and Signal Processing Controllers (DA)
 *
 * Class Code 0x11
 */
const char *STR_PCDA[] =
{
	"DPIO Modules", 						// 0x00 
	"Performance Counters", 				// 0x01 
	"Communications synchronization", 		// 0x10 
	"Management Card", 						// 0x20 
	"Other data acquisition controller"  	// 0x80 
};

/**
 * String representation of PCI Sub Class Code for Processing Accelerators (PA)
 *
 * Class Code 0x12
 */
const char *STR_PCPA[] = 
{
	"Processing Accelerator - Vendor Specific Interface", 	// 0x00 
	"SNIA Smart Data Acceleration Interface (SDXI)", 		// 0x00 
};

/**
 * String representation of PCI Sub Class Code for Non Essential Instrumentation (NE)
 *
 * Class Code 0x13
 */
const char *STR_PCNE[] =
{
	"Non Essential Instrumentation - Vendor Specific Interface", // 0x00 
};

























/* FUNCTIONS =================================================================*/

/**
 * Return a string representation of enumeration _PCAP
 */
const char *pcap(unsigned u)
{
	if (u >= PCAP_MAX)
		return NULL;
	return STR_PCAP[u];
}

/**
 * Return a string representation of enumeration _PCCX  
 */
const char *pccx(unsigned u)
{
	switch (u)
	{
		case PCCX_VS:		return STR_PCCX[0];
		case PCCX_CXL2_0:	return STR_PCCX[1];
	}
	return NULL;
}

/**

 * Return a string representation of enumeration _PCEC
 */
const char *pcec(unsigned u)
{
	if (u >= PCEC_MAX)
		return NULL;
	return STR_PCEC[u];
}

/**
 * Return a string representation of enumeration _PCMC
 */
const char *pcmc(unsigned u)
{
	switch(u)
	{
		case PCMC_RAM: 		return STR_PCMC[0]; 
		case PCMC_FLASH:	return STR_PCMC[1]; 
		case PCMC_CXL_MEM:	return STR_PCMC[2]; 
		case PCMC_OTHER:	return STR_PCMC[3]; 
	}
	return NULL;
}

/**
 * Return a string representation of enumeration _PCMS 
 */
const char *pcms(unsigned u)
{
	switch (u)
	{
		case PCMS_SCSI:		return STR_PCMS[0];
		case PCMS_IDE:		return STR_PCMS[1];
		case PCMS_FLOPPY: 	return STR_PCMS[2];
		case PCMS_IPI:		return STR_PCMS[3];
		case PCMS_RAID:		return STR_PCMS[4];
		case PCMS_ATA:		return STR_PCMS[5];
		case PCMS_SATA:		return STR_PCMS[6];
		case PCMS_SAS:		return STR_PCMS[7];
		case PCMS_NVM: 		return STR_PCMS[8];
		case PCMS_UFS: 		return STR_PCMS[9];
		case PCMS_OTHER: 	return STR_PCMS[10];
	}
	return NULL;
};

/**
 * Return a string representation of enumeration _PCNC 
 */
const char *pcnc(unsigned u)
{
	switch (u)
	{
		case PCNC_ETH:			return STR_PCNC[0];
		case PCNC_TOKEN:		return STR_PCNC[1];
		case PCNC_FDDI:			return STR_PCNC[2];
		case PCNC_ATM:			return STR_PCNC[3];
		case PCNC_ISDN:			return STR_PCNC[4];
		case PCNC_WORLDFIP:		return STR_PCNC[5];
		case PCNC_PICMG:		return STR_PCNC[6];
		case PCNC_IB:			return STR_PCNC[7];
		case PCNC_HFC:			return STR_PCNC[8];
		case PCNC_OTHER:		return STR_PCNC[9];
	}
	return NULL;
};

/**
 * Return a string representation of enumeration _PCDC
 */
const char *pcdc(unsigned u)
{
	switch (u)
	{
		case PCDC_VGA: 			return STR_PCDC[0];
		case PCDC_XGA: 			return STR_PCDC[1];
		case PCDC_3D: 			return STR_PCDC[2];
		case PCDC_OTHER: 		return STR_PCDC[3];
	}
	return NULL;
};

/**
 * Return a string representation of enumeration _PCUC 
 */
const char *pcuc(unsigned u)
{
	switch (u)
	{
		case PCUC_VIDEO: 		return STR_PCUC[0];
		case PCUC_AUDIO:		return STR_PCUC[1];
		case PCUC_TELEPHONE:	return STR_PCUC[2];
		case PCUC_HD_AUDIO: 	return STR_PCUC[3];
		case PCUC_OTHER: 		return STR_PCUC[4];
	}
	return NULL;
};

/**
 * Return a string representation of enumeration _PCBD
 */
const char *pcbd(unsigned u)
{
	switch (u)
	{
		case PCBD_HOST:		return STR_PCBD[0];
		case PCBD_ISA:		return STR_PCBD[1];
		case PCBD_EISA:		return STR_PCBD[2];
		case PCBD_MCA:		return STR_PCBD[3];
		case PCBD_PPB:		return STR_PCBD[4];
		case PCBD_PCMCIA:	return STR_PCBD[5];
		case PCBD_NUBUS:	return STR_PCBD[6];
		case PCBD_CARDBUS:	return STR_PCBD[7];
		case PCBD_RACEWAY:	return STR_PCBD[8];
		case PCBD_STPPB:	return STR_PCBD[9];
		case PCBD_IB_PCI:	return STR_PCBD[10];
		case PCBD_AS_PCI:	return STR_PCBD[11];
		case PCBD_OTHER:	return STR_PCBD[12];
	}
	return NULL;
};

/**
 * Return a string representation of enumeration _PCSC
 */
const char *pcsc(unsigned u)
{
	switch (u)
	{
		case PCSC_GENERIC_XT: 	return STR_PCBD[0];
		case PCSC_PARALLEL:  	return STR_PCBD[1]; 
		case PCSC_MP_SERIAL:	return STR_PCBD[2];
		case PCSC_MODEM: 	 	return STR_PCBD[3];
		case PCSC_GPIB: 		return STR_PCBD[4];
		case PCSC_SMRT_CARD:	return STR_PCBD[5];
		case PCSC_OTHER: 	 	return STR_PCBD[6];
	}
	return NULL;
}


/**
 * Return a string representation of enumeration _PCSP
 */
const char *pcsp(unsigned u)
{
	switch (u)
	{
		case PCSP_PCI:			return STR_PCSP[0];	
		case PCSP_DMA:			return STR_PCSP[1];	
		case PCSP_TIMER:		return STR_PCSP[2];	
		case PCSP_RTC:			return STR_PCSP[3];	
		case PCSP_HOT_PLUG:		return STR_PCSP[4];	
		case PCSP_SD:			return STR_PCSP[5];	
		case PCSP_IOMMU:		return STR_PCSP[6];	
		case PCSP_RCEC:			return STR_PCSP[7];	
		case PCSP_OTHER:		return STR_PCSP[8];	
	}
	return NULL;
}

/**
 * Return a string representation of enumeration _PCID
 */
const char *pcid(unsigned u)
{
	switch (u)
	{
		case PCID_KEYBOARD:		return STR_PCID[0];
		case PCID_PEN:			return STR_PCID[1];
		case PCID_MOUSE:		return STR_PCID[2];
		case PCID_SCANNER:		return STR_PCID[3];
		case PCID_GAME:			return STR_PCID[4];
		case PCID_OTHER:		return STR_PCID[5];
	}
	return NULL;
}

/**
 * Return a string representation of enumeration _PCDS
 */
const char *pcds(unsigned u)
{
	switch (u)
	{
		case PCDS_GENERIC: 		return STR_PCDS[0];
		case PCDS_OTHER:		return STR_PCDS[1];
	}
	return NULL;
}

/**
 * Return a string representation of enumeration _PCPR
 */
const char *pcpr(unsigned u)
{
	switch (u)
	{
		case PCPR_386:				return STR_PCPR[0];
		case PCPR_486:				return STR_PCPR[1];
		case PCPR_PENTIUM:			return STR_PCPR[2];
		case PCPR_ALPHA:			return STR_PCPR[3];
		case PCPR_POWERPC:			return STR_PCPR[4];
		case PCPR_MIPS:				return STR_PCPR[5];
		case PCPR_COPROCESSOR:		return STR_PCPR[6];
		case PCPR_OTHER:			return STR_PCPR[7];
	}
	return NULL;
}

/**
 * Return a string representation of enumeration _PCSB
 */
const char *pcsb(unsigned u)
{
	switch (u)
	{
		case PCSB_FIREWIRE:		return STR_PCSB[0];
		case PCSB_ACCESS:		return STR_PCSB[1];
		case PCSB_SSA:			return STR_PCSB[2];
		case PCSB_USB:			return STR_PCSB[3];
		case PCSB_FC:			return STR_PCSB[4];
		case PCSB_SMBUS:		return STR_PCSB[5];
		case PCSB_IB:			return STR_PCSB[6];
		case PCSB_IPMI:			return STR_PCSB[7];
		case PCSB_SERCOS:		return STR_PCSB[8];
		case PCSB_CANBUS:		return STR_PCSB[9];
		case PCSB_I3C:			return STR_PCSB[10];
		case PCSB_OTHER:		return STR_PCSB[11];
	}
	return NULL;
}

/**
 * Return a string representation of enumeration _PCWC
 */
const char *pcwc(unsigned u)
{
	switch (u)
	{
		case PCWC_IRDA:			return STR_PCWC[0];
		case PCWC_IR:			return STR_PCWC[1];
		case PCWC_RF:			return STR_PCWC[2];
		case PCWC_BT:			return STR_PCWC[3];
		case PCWC_BROADBAND:	return STR_PCWC[4];
		case PCWC_ETH5G:		return STR_PCWC[5];
		case PCWC_ETH2_4G:		return STR_PCWC[6];
		case PCWC_CELL:			return STR_PCWC[7];
		case PCWC_CELL_ETH:		return STR_PCWC[8];
		case PCWC_OTHER:		return STR_PCWC[9];
	}
	return NULL;
}

/**
 * Return a string representation of enumeration _PCIO
 */
const char *pcio(unsigned u)
{
	switch (u)
	{
		case PCIO_I2O:	return STR_PCIO[0];
	}
	return NULL;
}

/**
 * Return a string representation of enumeration _PCSA
 */
const char *pcsa(unsigned u)
{
	switch (u)
	{
		case PCSA_TV:		return STR_PCSA[0];
		case PCSA_AUDIO:	return STR_PCSA[1];
		case PCSA_VOICE:	return STR_PCSA[2];
		case PCSA_DATA:		return STR_PCSA[3];
		case PCSA_OTHER:	return STR_PCSA[4];
	}
	return NULL;
}

/**
 * Return a string representation of enumeration _PCEN
 */
const char *pcen(unsigned u)
{
	switch (u)
	{
		case PCEN_NET:		return STR_PCEN[0];
		case PCEN_ENT:		return STR_PCEN[1];
		case PCEN_OTHER:	return STR_PCEN[2];
	}
	return NULL;
}

/**
 * Return a string representation of enumeration _PCDA
 */
const char *pcda(unsigned u)
{
	switch (u)
	{
		case PCDA_DPIO:		return STR_PCDA[0];
		case PCDA_PERF:		return STR_PCDA[1];
		case PCDA_SYNC:		return STR_PCDA[2];
		case PCDA_MGMT:		return STR_PCDA[3];
		case PCDA_OTHER:	return STR_PCDA[4];
	}
	return NULL;
}

/**
 * Return a string representation of enumeration _PCPA
 */
const char *pcpa(unsigned u)
{
	switch (u)
	{
		case PCPA_ACCEL: 	return STR_PCPA[0];
		case PCPA_SDXI: 	return STR_PCPA[1];
	}
	return NULL;
}

/**
 * Return a string representation of enumeration _PCNE
 */
const char *pcne(unsigned u)
{
	switch (u)
	{
		case PCNE_INST: 	return STR_PCNE[0];
	}
	return NULL;
}

/**
 * Print the PCIe Config space
 *
 * @param cfgspace 	__u8* to a buffer with the PCIe cfg space 
 * @param indent  	The number of spaces to indent 
 */
void pcie_prnt_cfgspace(__u8 *cfgspace, unsigned indent)
{
	struct pcie_cfg_hdr *ph;
	char space[MAX_INDENT] = "                                ";

	if (cfgspace == NULL)
		return;

	if (indent >= MAX_INDENT) 
		indent = MAX_INDENT; 
	space[indent] = 0;

	ph = (struct pcie_cfg_hdr*) cfgspace;

	printf("%sPCIe Config Space HDR:\n", 			space);

	if ( (indent + 2) < MAX_INDENT) 
	{
		space[indent] = ' ';
		space[indent+2] = 0;
	}

    printf("%sVendor ID             0x%04x\n", 		space, ph->vendor);
  	printf("%sDevice ID             0x%04x\n", 		space, ph->device);
  	printf("%sCommand               0x%04x\n", 		space, ph->command);
  	printf("%sStatus                0x%04x\n", 		space, ph->status);
  	printf("%sRevision ID           0x%02x\n", 		space, ph->rev);
  	printf("%sProgramming Interface 0x%02x\n", 		space, ph->pi);
  	printf("%sSub Class             0x%02x\n", 		space, ph->subclass);
  	printf("%sBase Class            0x%02x\n", 		space, ph->baseclass);
  	printf("%sCache Line Size       0x%02x\n", 		space, ph->cls);
  	printf("%sLatency Timer         0x%02x\n", 		space, ph->timer);
  	printf("%sHeader Type           0x%02x\n", 		space, ph->type);
  	printf("%sBIST                  0x%02x\n", 		space, ph->bist);
  	printf("%sBAR0                  0x%08x\n", 		space, ph->bar0);
  	printf("%sBAR1                  0x%08x\n", 		space, ph->bar1);
  	printf("%sBAR2                  0x%08x\n", 		space, ph->bar2);
  	printf("%sBAR3                  0x%08x\n", 		space, ph->bar3);
  	printf("%sBAR4                  0x%08x\n", 		space, ph->bar4);
  	printf("%sBAR5                  0x%08x\n", 		space, ph->bar5);
  	printf("%sCardbus CIS Ptr       0x%08x\n", 		space, ph->cis);
	printf("%sSubsystem Vendor ID   0x%04x\n", 		space, ph->subvendor);
  	printf("%sSubsystem Device ID   0x%04x\n", 		space, ph->subsystem);
  	printf("%sExpansion ROM Addr    0x%08x\n", 		space, ph->rom);
  	printf("%sCapabilities Ptr      0x%02x\n", 		space, ph->cap);
  	printf("%sInterrupt Line        %u\n", 			space, ph->intline);
  	printf("%sInterrupt Pin         %u\n", 			space, ph->intpin);
  	printf("%sMinimum Grant         %u\n", 			space, ph->mingnt);
  	printf("%sMaximum Latency       %u\n", 			space, ph->maxlat);
}

