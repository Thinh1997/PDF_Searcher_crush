//
// Copyright (c) 2001-2021 by PDFTron Systems Inc. All Rights Reserved.
//

//Uncomment the line below if you have key ready.
public static class PDFTronLicense
{
    //Enter your key here. If you don't have it, please go to https://www.pdftron.com/pws/get-key to obtain a demo license or https://www.pdftron.com/form/contact-sales to obtain a production key.
    private static string key = "YOUR_PDFTRON_LICENSE_KEY";
    public static string Key
    {
        get
        {
            if (key == "YOUR_PDFTRON_LICENSE_KEY" || key == "")
                throw (new System.Exception("Please enter your license key by replacing \"YOUR_PDFTRON_LICENSE_KEY\" that is assigned to the static string key variable in Samples/LicenseKey/CS/LicenseKey.cs. If you do not have a license key, please go to https://www.pdftron.com/pws/get-key to obtain a demo license or https://www.pdftron.com/form/contact-sales to obtain a production key."));
            return key;
        }
    }
}
