//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2022 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

#ifndef PDFTRON_H_CPPPDFDigestAlgorithm
#define PDFTRON_H_CPPPDFDigestAlgorithm
#include <C/Crypto/TRN_DigestAlgorithm.h>

#include <Common/BasicTypes.h>
#include <Common/UString.h>
#include <PDF/PDFDoc.h>

namespace pdftron { namespace Crypto { 


class DigestAlgorithm
{
public:
	//enums:
	enum Type {
		e_SHA1 = 0,
		e_SHA256 = 1,
		e_SHA384 = 2,
		e_SHA512 = 3,
		e_RIPEMD160 = 4,
		e_unknown_digest_algorithm = 5
	};

	/**
	* Calculates a digest of arbitrary data. Useful during CMS generation custom signing workflows for digesting signedAttributes before
	* sending off for CMS signatureValue generation (e.g. by HSM device or cloud signing platform).
	* @param in_digest_algorithm_type -- the digest algorithm to use
	* @param in_message_buf -- the message to digest
	* @return a container of bytes corresponding to the digest of the message
	*/
	static std::vector<UChar> CalculateDigest(DigestAlgorithm::Type in_digest_algorithm_type, const std::vector<UChar>& in_message_buf);
#ifndef SWIG
	/**
	* Calculates a digest of arbitrary data. Useful during CMS generation custom signing workflows for digesting signedAttributes before
	* sending off for CMS signatureValue generation (e.g. by HSM device or cloud signing platform).
	* @param in_digest_algorithm_type -- the digest algorithm to use
	* @param in_message_buf -- the message to digest
	* @param in_message_buf_size -- the size of in_message_buf
	* @return a container of bytes corresponding to the digest of the message
	*/
	static std::vector<UChar> CalculateDigest(DigestAlgorithm::Type in_digest_algorithm_type, const UChar* in_message_buf, const size_t in_message_buf_size);
#endif
};

#include <Impl/DigestAlgorithm.inl>
} //end Crypto
} //end pdftron


#endif //PDFTRON_H_CPPPDFDigestAlgorithm
