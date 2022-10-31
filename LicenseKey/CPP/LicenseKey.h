//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2022 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------
//#define LicenseKey demo:1665078919824:7acd6c3a030000000008265d5d04aadabe58283ec48157cda351fc24a9
#ifndef   H_LICENSE_KEY
#define   H_LICENSE_KEY

namespace pdftron {
	//Uncomment the line below and replace YOUR_PDFTRON_LICENSE_KEY with your key.
	#define LicenseKey "demo:1665078919824:7acd6c3a030000000008265d5d04aadabe58283ec48157cda351fc24a9"
	#ifndef LicenseKey 
		#error "Please enter your license key by defining the LicenseKey macro in Samples/LicenseKey/CPP/LicenseKey.h. If you do not have a license key, please go to https://www.pdftron.com/pws/get-key to obtain a demo license or https://www.pdftron.com/form/contact-sales to obtain a production key."
	#endif
}

#endif
