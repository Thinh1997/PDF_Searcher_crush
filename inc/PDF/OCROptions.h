// This file is autogenerated: please see the codegen template "Options"
#ifndef PDFTRON_H_CPPPDFOCROptions
#define PDFTRON_H_CPPPDFOCROptions

#include <PDF/OptionsBase.h>
#include <Common/UString.h>

namespace pdftron{ namespace PDF{ 

class OCROptions
{
public:
	OCROptions();
	~OCROptions();

	

	/**
	* Adds a collection of ignorable regions for the given page,
	* an optional list of page areas not to be included in analysis
	* @param regions: the zones to be added to the ignore list
	* @param page_num: the page number the added regions belong to
	* @return this object, for call chaining
	*/
	OCROptions& AddIgnoreZonesForPage(const RectCollection& regions, int page_num);



	/**
	* Adds a language to the list of to be considered when
	* processing this document
	* @param lang: the new language to be added to the language list
	* @return this object, for call chaining
	*/
	OCROptions& AddLang(const UString& lang);



	/**
	* Adds a collection of text regions of interest for the given page,
	* an optional list of known text zones that will be used to improve OCR quality
	* @param regions: the zones to be added to the text region list
	* @param page_num: the page number the added regions belong to
	* @return this object, for call chaining
	*/
	OCROptions& AddTextZonesForPage(const RectCollection& regions, int page_num);


	/**
	* Knowing proper image resolution is important,
	* as it enables the OCR engine to translate pixel heights of characters to their respective font sizes.
	* We do our best to retrieve resolution information from the input's metadata, however it occasionally can be corrupt or missing.
	* Hence we allow manual override of source's resolution, which supersedes any metadata found (both explicit as in image metadata and implicit as in PDF).
	* @param dpi: image resolution
	* @return this object, for call chaining
	*/
	OCROptions& AddDPI(int dpi);

	/**
	* Sets the value for UsePDFPageCoords in the options object
	* Sets origin of the coordinate system for input/output
	* @param value: If true, sets origin of the coordinate system for input/output to the bottom left corner and reverses the direction of y-coordinate axis from downward to upward, otherwise top left corner is used as the origin and the y-coordinate axis direction is downward
	* @return this object, for call chaining
	*/
	OCROptions& SetUsePDFPageCoords(bool value);

	/**
	* Sets the value for IgnoreExistingText in the options object
	* Default value is false, so that areas with existing text will be automatically skipped during OCR. Setting to true probably only makes sense when used with GetOCRJson/XML, as pre-existing text might end up being duplicated in the document when used with ImageToPDF and ProcessPDF.
	* @param value: the new value for IgnoreExistingText
	* @return this object, for call chaining
	*/
	OCROptions& SetIgnoreExistingText(bool value);
	
	/**
	* Gets the value AutoRotate from the options object
	* Default value is false. Setting to true will deskew the image before conducting OCR.
	* @return a bool, the current value for AutoRotate.
	*/
	bool GetAutoRotate();

	/**
	* Sets the value for AutoRotate in the options object
	* Default value is false. Setting to true will deskew the image before conducting OCR.
	* @param value: the new value for AutoRotate
	* @return this object, for call chaining
	*/
	OCROptions& SetAutoRotate(bool value);
	
	/**
	* Gets the value OCREngine from the options object
	* Backend engine to use for OCR processing. Options include 'default', 'any', or 'iris'. Chosen module must be present and correctly licensed.
	* @return a UString, the current value for OCREngine.
	*/
	UString GetOCREngine();

	/**
	* Sets the value for OCREngine in the options object
	* Backend engine to use for OCR processing. Options include 'default', 'any', or 'iris'. Chosen module must be present and correctly licensed.
	* @param value: the new value for OCREngine
	* @return this object, for call chaining
	*/
	OCROptions& SetOCREngine(const UString& value);

	// @cond PRIVATE_DOC
	#ifndef SWIGHIDDEN
	SDF::Obj& GetInternalObj();

private:
	
	SDF::ObjSet m_obj_set;
	SDF::Obj m_dict;
	#endif
	// @endcond
};

}
}

#include "../Impl/OCROptions.inl"
#endif // PDFTRON_H_CPPPDFOCROptions
