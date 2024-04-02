/* SPDX-License-Identifier: Apache-2.0 */
/**
 * @file 		pcie.h
 *
 * @brief 		Header file for PCIe Config Space representation and operations
 *
 * @copyright 	Copyright (C) 2024 Jackrabbit Founders LLC. All rights reserved.
 *
 * @date 		Jan 2024
 * @author 		Barrett Edwards <code@jrlabs.io>
 * 
 * Macro / Enumeration Prefixes (PC)
 * PCAP - PCI Capabilities Registers (AP)
 * PCBC - PCI Class Codes (BC)
 * PCBD - PCI Sub Class Code for Bridge Devices (BD) 
 * PCCX - PCI Programming Interface for Sub Class: CXL memory (CX)
 * PCDC - PCI Sub Class Code for Dispaly Controllers (DC)
 * PCDS - PCI Sub Class Code for Docking Stations (DS)
 * PCEC - PCI Extended Capabilities Registers - (EC)
 * PCEN - PCI Sub Class Code for Encruyption Controllers (EN)
 * PCID - PCI Sub Class Code for Input Device (ID)
 * PCIO - PCI Sub Class Code for Intelligent IO Controllers (IO)
 * PCMC - PCI Sub Class Code for Memory Controllers (MC)
 * PCMS - PCI Sub Class Code for Mass Storage Controllers (MS)
 * PCNC - PCI Sub Class Code for Network Controllers (NC)
 * PCNE - PCI Sub Class Code for Non Essential Instrumentation (NE)
 * PCPR - PCI Sub Class Code for Processors (PR)
 * PCSA - PCI Sub Class Code for Satellite Controllers (SA)
 * PCSB - PCI Sub Class Code for Serial Bus Controllers (SB)
 * PCSC - PCI Sub Class Code for Simple communication controllers (SC)
 * PCSP - PCI Sub Class Code for Generic System Peripherals (SP)
 * PCUC - PCI Sub Class Code for Multimedia Controllers (UC)
 * PCWC - PCI Sub Class Code for Wireless Controllers (WC)
 */
#ifndef _PCIE_H 
#define _PCIE_H

/* INCLUDES ==================================================================*/

/* __u8
 * __u16
 */
#include <linux/types.h>

/* MACROS ====================================================================*/

#define PCLN_CFG 		4096
#define PCLN_HDR 		64  

/* ENUMERATIONS ==============================================================*/

/**
 * PCI Capabilities Registers (AP)
 *
 * These are 8-bit IDs 
 */
enum _PCAP 
{ 
	PCAP_PM        =   0x01, //!< PCI Power Management Interface 
	PCAP_AGP       =   0x02, //!< Accelerated Graphics Port 
	PCAP_VPD       =   0x03, //!< Vital Product Data
	PCAP_SLOTID    =   0x04, //!< Slot Numbering (for Bridge)
	PCAP_MSI       =   0x05, //!< Message Signaled Interrupts  
	PCAP_CHSWP     =   0x06, //!< CompactPCI Hot Swap 
	PCAP_PCIX      =   0x07, //!< PCI-X (Deprecated) 
	PCAP_HT        =   0x08, //!< HyperTransport (Deprecated)
	PCAP_VNDR      =   0x09, //!< Vendor Specific  
	PCAP_DBG       =   0x0a, //!< Debug port 
	PCAP_CCRC      =   0x0b, //!< CompactPCI central resource control 
	PCAP_HOTPLUG   =   0x0c, //!< PCI Hot-Plug (Deprecated) 
	PCAP_SSVID     =   0x0d, //!< PCI Bridge Subsystem Vendor ID 
	PCAP_AGP3      =   0x0e, //!< AGP 8x (Deprecated) 
	PCAP_SECURE    =   0x0f, //!< Secure Device (Deprecated) 
	PCAP_EXP       =   0x10, //!< PCI Express  
	PCAP_MSIX      =   0x11, //!< MSI-X  
	PCAP_SATA      =   0x12, //!< Serial ATA Data/Index Configuration 
	PCAP_AF        =   0x13, //!< Conventional PCI Advanced Features (AF) 
	PCAP_EA        =   0x14, //!< Enhanced Allocation
	PCAP_FPB	   =   0x15, //!< Flattening Portal Bridge                 
	PCAP_MAX
};

/**
 * PCI Extended Capabilities Registers - (EC)
 *
 * These are 16-bit IDs 
 */
enum _PCEC 
{
	PCEC_AER      	= 0x0001, //!< Advanced Error Reporting 
	PCEC_VC       	= 0x0002, //!< Virtual Channel (VC)
	PCEC_DSN      	= 0x0003, //!< Device Serial Number
	PCEC_PB       	= 0x0004, //!< Power Budgeting
	PCEC_RCLINK   	= 0x0005, //!< Root Complex Link Declaration
	PCEC_RCILINK  	= 0x0006, //!< Root Complex Internal Link Control
	PCEC_RCECOLL  	= 0x0007, //!< Root Complex Event Collector Endpoint Association 
	PCEC_MFVC     	= 0x0008, //!< Multi-Function Virtual Channel (MFVC)
	PCEC_VC2      	= 0x0009, //!< Virtual Channel (VC)
	PCEC_RBCB     	= 0x000a, //!< Root Complex Register Block (RCRB) Header
	PCEC_VNDR     	= 0x000b, //!< Vendor-Specific Extended Capability (VSEC)
	PCEC_ACS      	= 0x000d, //!< Access Control Services (ACS)
	PCEC_ARI      	= 0x000e, //!< Alternative Routing-ID Interpretation (ARI)
	PCEC_ATS      	= 0x000f, //!< Address Translation Services (ATS)
	PCEC_SRIOV    	= 0x0010, //!< Single Root I/O Virtualization (SR-IOV)
	PCEC_MRIOV    	= 0x0011, //!< Multi-Root I/O Virtualization (MR-IOV) (Deprecated)
	PCEC_MCAST    	= 0x0012, //!< Multicast 
	PCEC_PRI      	= 0x0013, //!< Page Request Interface (PRI)
	PCEC_REBAR    	= 0x0015, //!< Resizable BAR
	PCEC_DPA      	= 0x0016, //!< Dynamic Power Allocation (DPA)
	PCEC_TPH      	= 0x0017, //!< TPH Requester
	PCEC_LTR      	= 0x0018, //!< Latency Tolerance Reporting (LTR)
	PCEC_SECPCI   	= 0x0019, //!< Secondary PCI Express
	PCEC_PMUX     	= 0x001a, //!< Protocol Multiplexing (PMUX)
	PCEC_PASID    	= 0x001b, //!< Process Address Space ID (PASID)
	PCEC_LNR      	= 0x001c, //!< LN Requester (LNR)
	PCEC_DPC      	= 0x001d, //!< Downstream Port Containment (DPC)
	PCEC_L1PM     	= 0x001e, //!< L1 PM Substates
	PCEC_PTM      	= 0x001f, //!< Precision Time Measurement (PTM)
	PCEC_M_PCIE   	= 0x0020, //!< PCI Express over M-PHY (M-PCIe)
	PCEC_FRS      	= 0x0021, //!< FRS Queueing
	PCEC_RTR      	= 0x0022, //!< Readiness Time Reporting
	PCEC_DVSEC    	= 0x0023, //!< Designated Vendor-Specific Extended Capability
	PCEC_VF_REBAR 	= 0x0024, //!< VF Resizable BAR
	PCEC_DLNK     	= 0x0025, //!< Data Link Feature
	PCEC_16GT     	= 0x0026, //!< Physical Layer 16.0 GT/s
	PCEC_LMR      	= 0x0027, //!< Lane Margining at the Receiver
	PCEC_HIER_ID  	= 0x0028, //!< Hierarchy ID
	PCEC_NPEM     	= 0x0029, //!< Native PCIe Enclosure Management (NPEM)
	PCEC_PL 	  	= 0x002A, //!< Physical Layer 32.0 GT/s
	PCEC_AP 		= 0x002B, //!< Alternate Protocol
	PCEC_SFI 		= 0x002C, //!< System Firmware Intermediary (SFI)
	PCEC_SFUNC 		= 0x002D, //!< Shadow Functions
	PCEC_DOE 		= 0x002E, //!< Data Object Exchange
	PCEC_DEV3 		= 0x002F, //!< Device 3
	PCEC_IDE 		= 0x0030, //!< Integrity and Data Encryption (IDE)
	PCEC_64GT 		= 0x0031, //!< Physical Layer 64.0 GT/s Capability
	PCEC_FLITLOG 	= 0x0032, //!< Flit Logging
	PCEC_FLITPERF 	= 0x0033, //!< Flit Performance Measurement
	PCEC_FLITEI 	= 0x0034, //!< Flit Error Injection                                             

	PCEC_MAX
};

/**
 * PCI Class Codes (BC)
 */
enum _PCBC 
{
	PCBC_NULL			= 0x01, //!< 
	PCBC_MSC 			= 0x02, //!< Mass Storage Controller
	PCBC_NET  			= 0x02, //!< Network controller
	PCBC_DISPLAY		= 0x03, //!< Display controller
	PCBC_MULTIMEDIA 	= 0x04, //!< Multimedia device
	PCBC_MEM_CTRL 		= 0x05, //!< Memory controller
	PCBC_BRIDGE 		= 0x06, //!< Bridge device
	PCBC_SIMPLE_COMM	= 0x07, //!< Simple communication controllers
	PCBC_BASE_PERF  	= 0x08, //!< Base system peripherals
	PCBC_INPUT 			= 0x09, //!< Input devices
	PCBC_DOCKING 		= 0x0A, //!< Docking stations
	PCBC_PROCESSORS 	= 0x0B, //!< Processors
	PCBC_SERIAL_CTRL 	= 0x0C, //!< Serial bus controllers
	PCBC_WIRELESS 		= 0x0D, //!< Wireless controller
	PCBC_INTELLIGENT_IO	= 0x0E, //!< Intelligent I/O controllers
	PCBC_SATELLITE 		= 0x0F, //!< Satellite communication controllers
	PCBC_ENCRYPT 		= 0x10, //!< Encryption/Decryption controllers
	PCBC_SIG_PROCESS	= 0x11, //!< Data acquisition and signal processing controllers
	PCBC_PROC_ACCEL		= 0x12, //!< Processing accelerators
	PCBC_NON_ESSN 		= 0x13, //!< Non-Essential Instrumentation

};

/**
 * PCI Sub Class Code for Mass Storage Controllers (MS)
 *
 * Class Code 0x01
 */
enum _PCMS
{
	PCMS_SCSI		= 0x00, //!< SCSI Device or Controller 
	PCMS_IDE		= 0x01, //!< IDE Controller 
	PCMS_FLOPPY		= 0x02, //!< Floppy Disk Controller - Vendor Specific Interface 
	PCMS_IPI 		= 0x03, //!< IPI Bus Controller - Vendor Specific Interface 
	PCMS_RAID		= 0x04, //!< RAID Controller - Vendor Specific Interface 
	PCMS_ATA		= 0x05, //!< ATA Controller
	PCMS_SATA 		= 0x06, //!< SATA Controller 
	PCMS_SAS 		= 0x07, //!< SAS Controller 
	PCMS_NVM 		= 0x08, //!< Non-Volatile Memory Subsystem 
	PCMS_UFS 		= 0x09, //!< Universal Flash Storage Controller 
	PCMS_OTHER 		= 0x80  //!< Other Mass storage Controller 
};

/**
 * PCI Sub Class Code for Network Controllers (NC)
 *
 * Class Code 0x02
 */
enum _PCNC
{
	PCNC_ETH		= 0x00, //!< Ethernet Controller 
	PCNC_TOKEN		= 0x01, //!< Token Ring Controller 
	PCNC_FDDI 		= 0x02, //!< FDDI Controller 
	PCNC_ATM 		= 0x03, //!< ATM Controller 
	PCNC_ISDN 		= 0x04, //!< ISDN Controller 
	PCNC_WORLDFIP	= 0x05, //!< WorldFip Controller
	PCNC_PICMG 		= 0x06, //!< PICMG 
	PCNC_IB			= 0x07, //!< InfiniBand Controller 
	PCNC_HFC		= 0x08, //!< Host fabric Controller - Vendor Specific 
	PCNC_OTHER		= 0x80, //!< Other Network Controller 
};

/**
 * PCI Sub Class Code for Dispaly Controllers (DC)
 *
 * Class Code 0x03
 */
enum _PCDC
{
	PCDC_VGA 			= 0x00, //!< VGA Compatible Controller 
	PCDC_XGA 			= 0x01, //!< XGA Controller 
	PCDC_3D 			= 0x02, //!< 3D Controller 
	PCDC_OTHER 			= 0x80, //!< Other Controller 	
};

/**
 * PCI Sub Class Code for Multimedia Controllers (UC)
 *
 * Class Code 0x04
 */
enum _PCUC
{
	PCUC_VIDEO 				= 0x00, //!< Video Device - Vendor Specific Interface
	PCUC_AUDIO				= 0x01, //!< Audio Device - Vendor Specific Interface
	PCUC_TELEPHONE			= 0x02, //!< Computer Telephone Device - Vendor Specific Interface
	PCUC_HD_AUDIO 			= 0x03, //!< High Definition Audio 1.0 Compatible
	PCUC_OTHER 				= 0x80, //!< Other Multimedia device - Vendor Specific Interface
};

/**
 * PCI Sub Class Code for Memory Controllers (MC)
 *
 * Class Code 0x05
 */
enum _PCMC
{
	PCMC_RAM 		= 0x00,	//!< RAM 
	PCMC_FLASH		= 0x01,	//!< Flash
	PCMC_CXL_MEM	= 0x02,	//!< CXL Memory Device
	PCMC_OTHER		= 0x80 	//!< Other 
};

/**
 * PCI Sub Class Code for Bridge Devices (BD) 
 *
 * Class Code 0x06
 */
enum _PCBD
{
	PCBD_HOST 		= 0x00,	//!< Host Bridge
	PCBD_ISA 		= 0x01,	//!< ISA Bridge
	PCBD_EISA 		= 0x02,	//!< EISA
	PCBD_MCA 		= 0x03,	//!< MCA
	PCBD_PPB 		= 0x04,	//!< PCI-to-PCI Bridge
	PCBD_PCMCIA 	= 0x05,	//!< PCMCIA Bridge
	PCBD_NUBUS 		= 0x06,	//!< NuBus Bridge
	PCBD_CARDBUS 	= 0x07,	//!< CardBus Bridge
	PCBD_RACEWAY 	= 0x08,	//!< RaceWay Bridge
	PCBD_STPPB 		= 0x09,	//!< Semi-Transparent Bridge
	PCBD_IB_PCI 	= 0x0A,	//!< InfiniBand to PCI Host Bridge
	PCBD_AS_PCI		= 0x0B,	//!< Advanced Switching to PCI Host Bridge
	PCBD_OTHER  	= 0x80,	//!< Other Bridge
};

/**
 * PCI Sub Class Code for Simple communication controllers (SC)
 *
 * Class Code 0x07
 */
enum _PCSC
{
	PCSC_GENERIC_XT		= 0x00,	//!< Generic XT Compatible Serial Controller 
	PCSC_PARALLEL 		= 0x01,	//!< Parallel Port
	PCSC_MP_SERIAL 		= 0x02,	//!< Multi Port Serial Controller 
	PCSC_MODEM 			= 0x03,	//!< Generic Modem 
	PCSC_GPIB 			= 0x04,	//!< GPIB Controller 
	PCSC_SMRT_CARD 		= 0x05,	//!< SMART Card 
	PCSC_OTHER 			= 0x80 	//!< Other Communcations Device
};

/**
 * PCI Sub Class Code for Generic System Peripherals (SP)
 *
 * Class Code 0x08
 */
enum _PCSP
{
	PCSP_PCI		= 0x00,	//!< Programmable Interrupt Controller
	PCSP_DMA		= 0x01,	//!< DMA Controller 
	PCSP_TIMER		= 0x02,	//!< System Timer 
	PCSP_RTC		= 0x03,	//!< Generic Real Time Clock (RTC) Controller 
	PCSP_HOT_PLUG	= 0x04,	//!< Generic PCI Hot Plug Contoller 
	PCSP_SD			= 0x05,	//!< SD Host Controller 
	PCSP_IOMMU		= 0x06,	//!< IOMMU
	PCSP_RCEC		= 0x07,	//!< Root Complex Event Collector 
	PCSP_OTHER		= 0x80,	//!< Other System Peripheral 
};

/**
 * PCI Sub Class Code for Input Device (ID)
 *
 * Class Code 0x09
 */
enum _PCID
{
	PCID_KEYBOARD		= 0x00,	//!< Keyboard Controller 
	PCID_PEN  			= 0x01,	//!< Digitizer (pen)
	PCID_MOUSE 			= 0x02,	//!< Mouse Controller 
	PCID_SCANNER 		= 0x03,	//!< Scanner Controller 
	PCID_GAME  			= 0x04,	//!< Gameport Controller 
	PCID_OTHER 			= 0x80,	//!< Other Controller 
};

/**
 * PCI Sub Class Code for Docking Stations (DS)
 *
 * Class Code 0x0A
 */
enum _PCDS
{
	PCDS_GENERIC  		= 0x00,	//!< Generic Docking Station 
	PCDS_OTHER 			= 0x01,	//!< Other type of Docking Station 
};

/**
 * PCI Sub Class Code for Processors (PR)
 *
 * Class Code 0x0B
 */
enum _PCPR
{
	PCPR_386  			= 0x00,	//!< 386
	PCPR_486  			= 0x01,	//!< 486
	PCPR_PENTIUM 		= 0x02,	//!< Pentium
	PCPR_ALPHA 			= 0x10,	//!< Alpha
	PCPR_POWERPC 		= 0x20,	//!< PowerPC
	PCPR_MIPS  			= 0x30,	//!< MIPS
	PCPR_COPROCESSOR  	= 0x40,	//!< Co-Processor
	PCPR_OTHER  		= 0x80,	//!< Other Processor
};

/**
 * PCI Sub Class Code for Serial Bus Controllers (SB)
 *
 * Class Code 0x0C
 */
enum _PCSB
{
	PCSB_FIREWIRE  		= 0x00,	//!< Firewire
	PCSB_ACCESS  		= 0x01,	//!< ACCESS.bus
	PCSB_SSA  			= 0x02,	//!< SSA
	PCSB_USB  			= 0x03,	//!< USB
	PCSB_FC  			= 0x04,	//!< Fibre Channel 
	PCSB_SMBUS 			= 0x05,	//!< SM Bus
	PCSB_IB  			= 0x06,	//!< Infiniband (Depricated)
	PCSB_IPMI  			= 0x07,	//!< IPMI 
	PCSB_SERCOS 		= 0x08,	//!< SERCOS
	PCSB_CANBUS  		= 0x09,	//!< CANbus
	PCSB_I3C  			= 0x0A,	//!< MIPI I3C Controller
	PCSB_OTHER  		= 0x80,	//!< OTher Controller 
};

/**
 * PCI Sub Class Code for Wireless Controllers (WC)
 *
 * Class Code 0x0D
 */
enum _PCWC
{
	PCWC_IRDA 		= 0x00,	//!< iRDA Compatible Controller
	PCWC_IR 		= 0x01,	//!< IR Controller
	PCWC_RF 		= 0x10,	//!< RF Controller 
	PCWC_BT 		= 0x11,	//!< Bluetooth
	PCWC_BROADBAND 	= 0x12,	//!< Broadband
	PCWC_ETH5G 		= 0x20,	//!< Ethernet 5 GHz
	PCWC_ETH2_4G 	= 0x21,	//!< Ethernet 2.4 GHz
	PCWC_CELL 		= 0x40,	//!< Cellular Controller / Modem
	PCWC_CELL_ETH 	= 0x41,	//!< Cellular Controller + Ethrenet
	PCWC_OTHER 		= 0x80,	//!< Other Wireless Controller 
};

/**
 * PCI Sub Class Code for Intelligent IO Controllers (IO)
 *
 * Class Code 0x0E
 */
enum _PCIO
{
	PCIO_I2O 	 = 0x00,	//!< Intelligent IO (I2O) Specification 1.0 
};

/**
 * PCI Sub Class Code for Satellite Controllers (SA)
 *
 * Class Code 0x0F
 */
enum _PCSA
{
	PCSA_TV 	 = 0x01,	//!< TV
	PCSA_AUDIO 	 = 0x02,	//!< Audio
	PCSA_VOICE 	 = 0x03,	//!< Voice
	PCSA_DATA 	 = 0x04,	//!< Data
	PCSA_OTHER 	 = 0x80,	//!< Other 
};

/**
 * PCI Sub Class Code for Encryption Controllers (EN)
 *
 * Class Code 0x10
 */
enum _PCEN
{
	PCEN_NET 	 = 0x00,	//!< Network and Computing Encryption Decryption controller 
	PCEN_ENT 	 = 0x10,	//!< Entertainment encryption and decryption controller 
	PCEN_OTHER 	 = 0x80,	//!< Other encryption and decryption controller
};

/**
 * PCI Sub Class Code for Data Acquisition and Signal Processing Controllers (DA)
 *
 * Class Code 0x11
 */
enum _PCDA
{
	PCDA_DPIO 	 = 0x00,	//!< DPIO Modules 
	PCDA_PERF 	 = 0x01,	//!< Performance Counters 
	PCDA_SYNC 	 = 0x10,	//!< Communications synchronization 
	PCDA_MGMT 	 = 0x20,	//!< Management Card
	PCDA_OTHER 	 = 0x80,	//!< Other data acquisition controller 
};

/**
 * PCI Sub Class Code for Processing Accelerators (PA)
 *
 * Class Code 0x12
 */
enum _PCPA
{
	PCPA_ACCEL 	 = 0x00,	//!< Processing Accelerator - Vendor Specific Interface
	PCPA_SDXI 	 = 0x01,	//!< SNIA Smart Data Acceleration Interface (SDXI)
};

/**
 * PCI Sub Class Code for Non Essential Instrumentation (NE)
 *
 * Class Code 0x13
 */
enum _PCNE
{
	PCNE_INST 	 = 0x00,	//!< Non Essential Instrumentation - Vendor Specific Interface
};

/**
 * PCI Programming Interface for Sub Class: CXL memory (CX)
 * 
 * Class Code: 		0x05
 * Sub Class code 	0x02
 */
enum _PCCX
{
	PCCX_VS			= 0x00, //!< CXL Memory Device - Vendor Specific Interface
	PCCX_CXL2_0		= 0x01  //!< CXL Memory Device compliant with CXL 2.0 or later
};


/* STRUCTS ===================================================================*/


/**
 * PCI Capability Header 
 */
struct __attribute__((__packed__)) pcie_cap
{
	__u8 id; 	//!< PCI Capability ID 
	__u8 next; 	//!< Offset of next capability. 0=end of list
};

/**
 * Power Management Capabilities Register (PMC) 
 *
 * This is the first 2B of the PCI Power Management Capabilities entry
 * All Read Only Fields
 */
struct __attribute__((__packed__)) pcie_cap_pm_pmc
{
	__u16 ver 			: 3; //!< Version 0x03 = complies with 1.2 of the PCI Power Mgmt Interface specification (RO)
	__u16 clock 		: 1; //!< PME Clock Required. Always 0 for PCIe (RO)

	__u16 rsvd1 		: 1;
	__u16 dsi 			: 1; //!< Device Specific Initialization is required (RO)
	__u16 aux 			: 3; //!< Maximum AUX Current required 
							 // 000 =   0 mA
							 // 001 =  55 mA 
							 // 010 = 100 mA 
							 // 011 = 160 mA 
							 // 100 = 220 mA
							 // 101 = 270 mA
							 // 110 = 320 mA 
							 // 111 = 375 mA 
	__u16 d1 			: 1; //!< D1 Power State Supported (RO)
	__u16 d2 			: 1; //!< D2 Power State Supported (RO)
	__u16 pme_sup		: 5; //!< PME Support. Indicates the power states in which the function may assert PME# (RO)
};

/**
 * Power Management Control/Status Register (PMCSR)
 *
 * This is the 3rd and 4th bytes of the PCI Power Management Capabilities entry 
 * 
 */
struct __attribute__((__packed__)) pcie_cap_pm_pmcsr
{
	__u16 state 		: 2; //!< Current Power State. Sets power state when written to (RW) 00 = D0, 01 = D1, 10 = D3, 11 = D3 hot
	__u16 rsvd2 		: 1; //!< Device specific. Reserved for PCIe
	__u16 no_soft_rst 	: 1; //!< No soft Reset. When going to D0 does this device require a reset? (RO)
	__u16 rsvd3 		: 4; 

	__u16 pme_en 		: 1; //!< PME Enable. When set, enable power management events
	__u16 data_sel 		: 4; //!< Data Select. Select what data is reported in last byte of pcie_cap_pm (RW)
	__u16 data_scale 	: 2; //!< Data Scale (RO)
	__u16 pme_status    : 1; //!< PME Status. Shows state of PME# signal regardless if PME is enabled or not (RW)
};

/**
 * Bridge Support Extension Register (PMCSR_BSE) 
 *
 * Required for all PCI-to-PCI bridges 
 */
struct __attribute__((__packed__)) pcie_cap_pm_bse
{
	__u8 rsvd4 			: 6; //!< (RO)
	__u8 b2_b3 			: 1; //!< Action when transitioning to D3Hot. (RO)
	__u8 bpcc_en 		: 1; //!< Bus Power / Clock Control Enable (RO)
};

/**
 * PCI Capability - Power Management
 *
 * ID: 0x01
 * LEN: 6B
 */
struct __attribute__((__packed__)) pcie_cap_pm
{
	struct pcie_cap_pm_pmc pmc;		//!< Power Management Capabilities Register (PMC) [2B]
	struct pcie_cap_pm_pmcsr pmcsr;	//!< Power Management Control/Status Register (PMCSR) [2B]
	struct pcie_cap_pm_bse bse;		//!< Bridge Support Extension Register (PMCSR_BSE) [1B]
	__u8 data; 						//!< Data 
};

/**
 * PCI Capability - MSI Message Control
 */
struct __attribute__((__packed__)) pcie_cap_msi_ctrl
{
	__u16 enable 	: 1; //!< MSI Enable (RW)
	__u16 request 	: 3; //!< Requested number of vectors. 000=1, 001=2, 010=4,011=8,100=16,101=32,110=rsvd, 111=rsvd (RO)
	__u16 allocated : 3; //!< Allocated number of vectors by host. (RW)
	__u16 bit64 	: 1; //!< 64 Bit address capable (RO)

	__u16 maskable  : 1; //!< Per vector masking capable. (RO)
	__u16 rsvd  	: 7; //!< 
};

/**
 * PCI Extended Capability Header 
 */
struct __attribute__((__packed__)) pcie_ecap
{
	__u16 id; 			//!< PCI Extended Capability ID 
	__u16 ver 	: 4; 	//!< Capability Version
	__u16 next 	: 12; 	//!< Offset of next capability. 0=end of list
};

/**
 * PCI Extended Capability: Device Serial Number
 *
 * ID: 0x0003
 */
struct __attribute__((__packed__)) pcie_ecap_dsn
{
	__u32 lo; 	//!< Low 4 bytes of serial number
	__u32 hi; 	//!< Hi 4 bytes of serial number
};

/**
 * PCI Header - Type field 
 */
struct __attribute__((__packed__)) pcie_cfg_type
{
	__u8 type 	: 7; 	//!< PCIe Header Type code
	__u8 mf 	: 1; 	//!< Multi-function Device 
};

/**
 * PCI Header - Command Register
 *
 * A typical value for a modern PCIe device is 
 * 0x0506 
 * - Interupt Disable 	- This is 1 as devivce uses MSI 
 * - SERR  				- 
 * - Bus Master 		- Device can initiate DMA transactions
 * - Mem Space 			- Device is accessible over PCI MemRd/Wr not PCIe IO
 *
 * lspic naming: I/O- Mem+ BusMaster+ SpecCycle- MemWINV- VGASnoop- ParErr- Stepping- SERR+ FastB2B- DisINTx+
 */
struct __attribute__((__packed__)) pcie_cfg_cmd
{
	__u16 io 			: 1; //!< IO Space. If 1, dev can respond to IO space access
	__u16 mem 			: 1; //!< Mem space. If 1, dev can respond to Memory Space access
	__u16 busmaster 	: 1; //!< Bus Master. If 1, dev can behave as a bus master
	__u16 speccycle 	: 1; //!< Special Cycles. If 1, dev can monitor special cycles operations

	__u16 memwine      	: 1; //!< Memory write and invalidate enable
	__u16 vgasnoop 		: 1; //!< VGA Palette Snoop. If 1 dev does not respond to palette register writes and will snoop the data
	__u16 parerr 		: 1; //!< Parity Error Response. If 1 dev will take its normal action when a parity error is detected 
	__u16 stepping 		: 1; //!< 

	__u16 serr 			: 1; //!< SERR Enable. If 1 SERR# driver is enabled
	__u16 fastb2b 		: 1; //!< Fast back to back enable 
	__u16 disintx 		: 1; //!< Interrupt Disable, If 1 the assertion of the devices INTx# signal is disabled
	__u16 rsvd2 		: 1; 

	__u16 rsvd3 		: 4; 
};

/**
 * PCI Header - Status Register
 * 
 * A typical value for a modern PCIe device is 
 * 0x0010
 * - Interupts disabled
 * - Has Capabilities List
 * - Only runs at 33 MHz (not 66MHz)
 * - No Fast Back-to-Back transactions
 * - DEVSEL = fast 
 *
 * lspci naming: Cap+ 66MHz- UDF- FastB2B- ParErr- DEVSEL=fast >TAbort- <TAbort- <MAbort- >SERR- <PERR- INTx-
 */
struct __attribute__((__packed__)) pcie_cfg_status
{
	__u16 rsvd1 		: 3; 
	__u16 intx			: 1; //!< Interrupt Status. Represents the state of the device's INTx# signal

	__u16 cap 			: 1; //!< Capabilities List. If 1 dev implements capabilities ptr at offset 0x34; otherwise, the linked list is not available.
	__u16 mhz 			: 1; //!< If set to 1 the device is capable of running at 66 
	__u16 rsvd2 		: 1; 
	__u16 fastb2b 		: 1; //!< Fast Back-to-Back Capable. If 1 dev can accept fast back-to-back transactions 

	__u16 parerr 		: 1; //!< Master Data Parity Error. 
	__u16 devsel 		: 2; //!< DEVSEL Timing. RO. 0=fast, 1=medium 2=slow
	__u16 sig_tabort 	: 1; //!< Signaled Target Abort. Set to 1 whenever a target device terminates a transaction with Target-Abort.

	__u16 recv_tabort 	: 1; //!< Received Target Abort. Set to 1, by a master device, whenever its transaction is terminated with Target-Abort.
	__u16 recv_mabort 	: 1; //!< Received Master Abort. Set to 1, by a master device, whenever its transaction is terminated with Master-Abort.
	__u16 sig_sys_err 	: 1; //!< Signalled System Error. Set to 1 whenever the device asserts SERR#.
	__u16 parity_err 	: 1; //!< Detected Parity Error. Set to 1 whenever the device detects a parity error, even if parity error handling is disabled.
};

/**
 * PCIe Config Space Header 
 * 
 * The PCIe config space is 4KB and consists of:
 * 1.   64 B Header 
 * 2.  192 B Region for PCIe Capabilities entries
 * 3. 3840 B Region for PCIe Extended Capabilities entries
 */
struct __attribute__((__packed__)) pcie_cfg_hdr 
{
	__u16 vendor;		//!< Vendor ID 
	__u16 device;		//!< Device ID
	__u16 command;      //!< Command register 
	__u16 status;		//!< Status register 
	__u8 rev;			//!< Class Revision ID
	__u8 pi;			//!< Programming Interface 
	__u8 subclass;		//!< Sub Class Code 
	__u8 baseclass;		//!< Base Class Code 
	__u8 cls;			//!< Cache Line Size 
	__u8 timer;			//!< PCIe Latency Timer
	__u8 type;			//!< 0 = Endpoint, 1 = Switch, 2 = cardbus 
	__u8 bist;			//!< Capable & Start bits
	__u32 bar0;			//!< Base Address Register 0
	__u32 bar1;			//!< Base Address Register 1
	__u32 bar2;			//!< Base Address Register 2
	__u32 bar3;			//!< Base Address Register 3
	__u32 bar4;			//!< Base Address Register 4
	__u32 bar5;			//!< Base Address Register 5
	__u32 cis;			//!< Cardbud CIS pointer 
	__u16 subvendor;	//!< Subsystem Vendor ID
	__u16 subsystem;	//!< Subsystem ID 
	__u32 rom;			//!< Expansion ROM Base Address
	__u8 cap;			//!< Capability List Offset to first entry
	__u32 rsvd : 24;	
	__u32 rsvd2;
	__u8 intline;		//!< Interrupt line
	__u8 intpin;		//!< Interrupt pin 
	__u8 mingnt;		//!< Minimum grant for burst period length in 1/4 microsecond units assuming 33MHz clock 
	__u8 maxlat;		//!< Maximum LAtency 
	
};


/* PROTOTYPES ================================================================*/

const char *pcap(unsigned u);
const char *pcec(unsigned u);
const char *pccx(unsigned u);
const char *pcmc(unsigned u);
const char *pcms(unsigned u);
const char *pcnc(unsigned u);
const char *pcdc(unsigned u);
const char *pcuc(unsigned u);
const char *pcbd(unsigned u);
const char *pcsc(unsigned u);
const char *pcsp(unsigned u);
const char *pcid(unsigned u);
const char *pcds(unsigned u);
const char *pcpr(unsigned u);
const char *pcsb(unsigned u);
const char *pcwc(unsigned u);
const char *pcio(unsigned u);
const char *pcsa(unsigned u);
const char *pcen(unsigned u);
const char *pcda(unsigned u);
const char *pcpa(unsigned u);
const char *pcne(unsigned u);

void pcie_prnt_cfgspace(__u8 *cfgspace, unsigned indent);

/* GLOBAL VARIABLES ==========================================================*/

#endif //ifndef _PCIE_H
