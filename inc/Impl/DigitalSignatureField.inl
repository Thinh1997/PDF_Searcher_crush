inline DigitalSignatureField::DigitalSignatureField(const DigitalSignatureField& other)
	: m_impl(other.m_impl)
{
}

inline DigitalSignatureField& DigitalSignatureField::operator= (const DigitalSignatureField& other)
{
	m_impl = other.m_impl;
	return *this;
}

inline DigitalSignatureField::DigitalSignatureField(TRN_DigitalSignatureField impl)
	: m_impl(impl)
{}

inline DigitalSignatureField::DigitalSignatureField(const PDF::Field& in_field)
{
	REX(TRN_DigitalSignatureFieldCreateFromField(&in_field.mp_field, &m_impl));
}

inline bool DigitalSignatureField::HasCryptographicSignature() const
{
	TRN_Bool result = 0;
	REX(TRN_DigitalSignatureFieldHasCryptographicSignature(&m_impl, &result));
	return result != 0;
}

inline DigitalSignatureField::SubFilterType DigitalSignatureField::GetSubFilter() const
{
	SubFilterType result;
	REX(TRN_DigitalSignatureFieldGetSubFilter(&m_impl, (enum TRN_DigitalSignatureField_SubFilterType*) &result));
	return result;
}

inline UString DigitalSignatureField::GetSignatureName() const
{
	TRN_UString result;
	REX(TRN_DigitalSignatureFieldGetSignatureName(&m_impl, &result));
	return UString(result);
}

inline Date DigitalSignatureField::GetSigningTime() const
{
	TRN_Date result;
	REX(TRN_DigitalSignatureFieldGetSigningTime(&m_impl, &result));
	return *((Date*)&result);
}

inline UString DigitalSignatureField::GetLocation() const
{
	TRN_UString result;
	REX(TRN_DigitalSignatureFieldGetLocation(&m_impl, &result));
	return UString(result);
}

inline UString DigitalSignatureField::GetReason() const
{
	TRN_UString result;
	REX(TRN_DigitalSignatureFieldGetReason(&m_impl, &result));
	return UString(result);
}

inline UString DigitalSignatureField::GetContactInfo() const
{
	TRN_UString result;
	REX(TRN_DigitalSignatureFieldGetContactInfo(&m_impl, &result));
	return UString(result);
}

inline std::vector<UChar> DigitalSignatureField::GetCert(UInt32 in_index) const {
	TRN_Vector cvector;
	REX(TRN_DigitalSignatureFieldGetCert(&m_impl, in_index, &cvector));
	void* arr;
	UInt32 size;
	REX(TRN_VectorGetData(cvector, &arr));
	REX(TRN_VectorGetSize(cvector, &size));
	std::vector<UChar> result(size);
	memcpy(&result[0], arr, size);
	TRN_VectorDestroy(cvector);
	return result;
}

inline UInt32 DigitalSignatureField::GetCertCount() const
{
	UInt32 result = 0;
	REX(TRN_DigitalSignatureFieldGetCertCount(&m_impl, &result));
	return result;
}

inline bool DigitalSignatureField::HasVisibleAppearance() const
{
	TRN_Bool result = 0;
	REX(TRN_DigitalSignatureFieldHasVisibleAppearance(&m_impl, &result));
	return result != 0;
}

inline void DigitalSignatureField::SetContactInfo(const UString& in_contact_info)
{
	REX(TRN_DigitalSignatureFieldSetContactInfo(&m_impl, in_contact_info.mp_impl));
}

inline void DigitalSignatureField::SetLocation(const UString& in_location)
{
	REX(TRN_DigitalSignatureFieldSetLocation(&m_impl, in_location.mp_impl));
}

inline void DigitalSignatureField::SetReason(const UString& in_reason)
{
	REX(TRN_DigitalSignatureFieldSetReason(&m_impl, in_reason.mp_impl));
}

// We use an std::vector of UTF-8 std::strings for SWIG, because SWIG has trouble with mapping UString to string when it's in a vector<UString>.
#ifdef SWIG
inline void DigitalSignatureField::SetFieldPermissions(const FieldPermissions in_action, const std::vector<std::string>& in_field_names)
{
	if (in_field_names.size() > 0)
	{
		std::vector<UString> tmp;
		tmp.reserve(in_field_names.size());
		for (std::vector<std::string>::const_iterator it = in_field_names.begin(); it != in_field_names.end(); ++it)
		{
			tmp.push_back(UString(*it));
		}
		TRN_UString* tmp2 = (TRN_UString*) &tmp[0];
		REX(TRN_DigitalSignatureFieldSetFieldPermissions(&m_impl, (enum TRN_DigitalSignatureField_FieldPermissions) in_action, tmp2, (TRN_UInt32)in_field_names.size()));
	}
	else // If the container is empty, the returned iterator value shall not be dereferenced.
	{
		REX(TRN_DigitalSignatureFieldSetFieldPermissions(&m_impl, (enum TRN_DigitalSignatureField_FieldPermissions) in_action, NULL, 0));
	}
}
#else
inline void DigitalSignatureField::SetFieldPermissions(const FieldPermissions in_action, const std::vector<UString>& in_field_names)
{
	// UString class contains only a TRN_UString and no virtual functions, so an array of UStrings is also an array of TRN_UStrings
	TRN_UString* tmp = in_field_names.size() > 0? (TRN_UString*) &in_field_names[0] : NULL;
	REX(TRN_DigitalSignatureFieldSetFieldPermissions(&m_impl, (enum TRN_DigitalSignatureField_FieldPermissions) in_action, tmp, (TRN_UInt32)in_field_names.size()));
}
inline void DigitalSignatureField::SetFieldPermissions(const FieldPermissions in_action, const UString* in_field_names, const size_t in_field_names_num_elems)
{
	// UString class contains only a TRN_UString and no virtual functions, so an array of UStrings is also an array of TRN_UStrings
	TRN_UString* tmp = (TRN_UString*)&in_field_names[0];
	REX(TRN_DigitalSignatureFieldSetFieldPermissions(&m_impl, (enum TRN_DigitalSignatureField_FieldPermissions) in_action, tmp, (TRN_UInt32)in_field_names_num_elems));
}
#endif

inline void DigitalSignatureField::SetDocumentPermissions(DigitalSignatureField::DocumentPermissions in_perms)
{
	REX(TRN_DigitalSignatureFieldSetDocumentPermissions(&m_impl, (enum TRN_DigitalSignatureField_DocumentPermissions) in_perms));
}

inline void DigitalSignatureField::SignOnNextSave(const UString& in_pkcs12_keyfile_path, const UString& in_password)
{
	REX(TRN_DigitalSignatureFieldSignOnNextSave(&m_impl, in_pkcs12_keyfile_path.mp_impl, in_password.mp_impl));
}

inline void DigitalSignatureField::SignOnNextSave(const UChar* in_pkcs12_buffer, size_t in_buf_size, const UString& in_password)
{
	REX(TRN_DigitalSignatureFieldSignOnNextSaveFromBuffer(&m_impl, (const TRN_UChar*)in_pkcs12_buffer, (TRN_UInt32)in_buf_size, in_password.mp_impl));
}

inline void DigitalSignatureField::SignOnNextSaveWithCustomHandler(const SDF::SignatureHandlerId in_signature_handler_id)
{
	REX(TRN_DigitalSignatureFieldSignOnNextSaveWithCustomHandler(&m_impl, (const TRN_SignatureHandlerId) in_signature_handler_id));
}

inline void DigitalSignatureField::CertifyOnNextSave(const UString& in_pkcs12_keyfile_path, const UString& in_password)
{
	REX(TRN_DigitalSignatureFieldCertifyOnNextSave(&m_impl, in_pkcs12_keyfile_path.mp_impl, in_password.mp_impl));
}

inline void DigitalSignatureField::CertifyOnNextSave(const UChar* in_pkcs12_buffer, size_t in_buf_size, const UString& in_password)
{
	REX(TRN_DigitalSignatureFieldCertifyOnNextSaveFromBuffer(&m_impl, (const TRN_UChar*)in_pkcs12_buffer, (TRN_UInt32)in_buf_size, in_password.mp_impl));
}

inline void DigitalSignatureField::CertifyOnNextSaveWithCustomHandler(const SDF::SignatureHandlerId in_signature_handler_id)
{
	REX(TRN_DigitalSignatureFieldCertifyOnNextSaveWithCustomHandler(&m_impl, (const TRN_SignatureHandlerId) in_signature_handler_id));
}

inline SDF::Obj DigitalSignatureField::GetSDFObj() const
{
	TRN_Obj result;
	REX(TRN_DigitalSignatureFieldGetSDFObj(&m_impl,&result));
	return SDF::Obj(result);
}

inline bool DigitalSignatureField::IsLockedByDigitalSignature() const
{
	TRN_Bool result = 0;
	REX(TRN_DigitalSignatureFieldIsLockedByDigitalSignature(&m_impl, &result));
	return result != 0;
}

// We use an std::vector of UTF-8 std::strings for SWIG, because SWIG has trouble with mapping UString to string when it's in a vector<UString>.
#ifdef SWIG
inline std::vector<std::string> DigitalSignatureField::GetLockedFields() const
{
	// Broadly similar to PDFDraw::GetSeparationBitmaps implementation
	TRN_Vector fields_vec = NULL;
	REX(TRN_DigitalSignatureFieldGetLockedFields(&m_impl, (TRN_Vector*)&fields_vec));
	
	TRN_UInt32 fields_vec_size;
	TRN_VectorGetSize(fields_vec, &fields_vec_size);
	
	std::vector<std::string> result;
	for (TRN_UInt32 i = 0; i < fields_vec_size; i++)
	{
		TRN_UString current_ustr = NULL;
		TRN_VectorGetAt(fields_vec, i, (void**)&current_ustr);
		
		result.push_back(UString(current_ustr).ConvertToUtf8());
	}

	TRN_VectorDestroyKeepContents(fields_vec);
	return result;
}
#else
inline std::vector<UString> DigitalSignatureField::GetLockedFields() const
{
	// Broadly similar to PDFDraw::GetSeparationBitmaps implementation
	TRN_Vector fields_vec = NULL;
	REX(TRN_DigitalSignatureFieldGetLockedFields(&m_impl, (TRN_Vector*)&fields_vec));
	
	TRN_UInt32 fields_vec_size;
	TRN_VectorGetSize(fields_vec, &fields_vec_size);
	
	std::vector<UString> result;
	for (TRN_UInt32 i = 0; i < fields_vec_size; i++)
	{
		TRN_UString current_ustr = NULL;
		TRN_VectorGetAt(fields_vec, i, (void**)&current_ustr);
		result.push_back(UString(current_ustr));
	}

	TRN_VectorDestroyKeepContents(fields_vec);
	return result;
}
#endif

inline DigitalSignatureField::DocumentPermissions DigitalSignatureField::GetDocumentPermissions() const
{
	DigitalSignatureField::DocumentPermissions result;
	REX(TRN_DigitalSignatureFieldGetDocumentPermissions(&m_impl, (enum TRN_DigitalSignatureField_DocumentPermissions*) &result));
	return result;
}

inline void DigitalSignatureField::ClearSignature()
{
	REX(TRN_DigitalSignatureFieldClearSignature(&m_impl));
}

inline VerificationResult DigitalSignatureField::Verify(const VerificationOptions& in_opts) const
{
	TRN_VerificationResult tmp;
	REX(TRN_DigitalSignatureFieldVerify(&m_impl, (const TRN_VerificationOptions)in_opts.m_impl, (TRN_VerificationResult*) &tmp));
	return VerificationResult(tmp);
}

inline bool DigitalSignatureField::IsCertification() const
{
	TRN_Bool result = 0;
	REX(TRN_DigitalSignatureFieldIsCertification(&m_impl, &result));
	return result != 0;
}

inline Crypto::X509Certificate DigitalSignatureField::GetSignerCertFromCMS() const
{
	TRN_X509Certificate result;
	REX(TRN_DigitalSignatureFieldGetSignerCertFromCMS((TRN_DigitalSignatureField*)&m_impl, (TRN_X509Certificate*) &result));
	return Crypto::X509Certificate(result);
}


inline std::vector<Common::ByteRange> DigitalSignatureField::GetByteRanges() const
{
	TRN_Vector vec = NULL;
	REX(TRN_DigitalSignatureFieldGetByteRanges(&m_impl, (TRN_Vector*)&vec));

	TRN_UInt32 size;
	TRN_VectorGetSize(vec, &size);

	std::vector< Common::ByteRange > result(size);
	for (UInt32 i = 0; i < size; ++i)
	{
		TRN_ByteRange* current;
		TRN_VectorGetAt(vec, i, (void**)& current);
		memcpy(&result[i], current, sizeof(TRN_ByteRange));
	}

	TRN_VectorDestroyKeepContents(vec);
	return result;
}


inline std::vector<std::vector<Crypto::X509Certificate> > DigitalSignatureField::GetCertPathsFromCMS() const
{
	// Broadly similar to PDFDraw::GetSeparationBitmaps implementation
	
	TRN_UInt32 outer_vec_size;
	REX(TRN_DigitalSignatureFieldGetCertPathsFromCMS_GetOutterVecSize((TRN_DigitalSignatureField*)&m_impl, (TRN_UInt32*)&outer_vec_size));

	std::vector < std::vector<Crypto::X509Certificate> > ret;
	for (TRN_UInt32 m = 0; m < outer_vec_size; m++)
	{
		TRN_Vector vec = NULL;
		REX(TRN_DigitalSignatureFieldGetCertPathsFromCMS((TRN_DigitalSignatureField*)&m_impl, (TRN_Vector*)&vec, m));

		TRN_UInt32 vec_size;
		TRN_VectorGetSize(vec, &vec_size);

		std::vector<Crypto::X509Certificate> result;
		for (TRN_UInt32 i = 0; i < vec_size; i++)
		{
			TRN_X509Certificate current = NULL;
			TRN_VectorGetAt(vec, i, (void**)&current);
			result.push_back(Crypto::X509Certificate(current));
		}
		ret.push_back(result);
		TRN_VectorDestroyKeepContents(vec);
	}

	return ret;
}

inline bool DigitalSignatureField::EnableLTVOfflineVerification(const VerificationResult& in_verification_result) const
{
	TRN_Bool result = 0;
	REX(TRN_DigitalSignatureFieldEnableLTVOfflineVerification((TRN_DigitalSignatureField*)&m_impl, (TRN_VerificationResult)in_verification_result.m_impl, &result));
	return result != 0;
}

inline void DigitalSignatureField::TimestampOnNextSave(const TimestampingConfiguration& in_timestamping_config,
	const VerificationOptions& in_timestamp_response_verification_options)
{
	REX(TRN_DigitalSignatureFieldTimestampOnNextSave((TRN_DigitalSignatureField*)&m_impl, in_timestamping_config.m_impl, in_timestamp_response_verification_options.m_impl));
}

inline TimestampingResult DigitalSignatureField::GenerateContentsWithEmbeddedTimestamp(const TimestampingConfiguration& in_timestamping_config,
	const VerificationOptions& in_timestamp_response_verification_options)
{
	TRN_TimestampingResult result;
	REX(TRN_DigitalSignatureFieldGenerateContentsWithEmbeddedTimestamp((TRN_DigitalSignatureField*)&m_impl, in_timestamping_config.m_impl, in_timestamp_response_verification_options.m_impl, (TRN_TimestampingResult*)&result));
	return TimestampingResult(result);
}

inline void DigitalSignatureField::UseSubFilter(SubFilterType in_subfilter_type, bool in_make_mandatory)
{
	REX(TRN_DigitalSignatureFieldUseSubFilter((TRN_DigitalSignatureField*)&m_impl, (enum TRN_DigitalSignatureField_SubFilterType) in_subfilter_type, in_make_mandatory));
}

inline std::vector<UChar> DigitalSignatureField::CalculateDigest(const Crypto::DigestAlgorithm::Type in_digest_algorithm_type) const
{
	TRN_Vector cvector;
	REX(TRN_DigitalSignatureFieldCalculateDigest((TRN_DigitalSignatureField*)&m_impl, (TRN_DigestAlgorithm_Type)in_digest_algorithm_type, &cvector));
	void* arr;
	UInt32 size;
	REX(TRN_VectorGetData(cvector, &arr));
	REX(TRN_VectorGetSize(cvector, &size));
	std::vector<UChar> result(size);
	memcpy(&result[0], arr, size);
	TRN_VectorDestroy(cvector);
	return result;
}

inline void DigitalSignatureField::SetPreferredDigestAlgorithm(Crypto::DigestAlgorithm::Type in_digest_algorithm_type, const bool in_make_mandatory)
{
	REX(TRN_DigitalSignatureFieldSetPreferredDigestAlgorithm((TRN_DigitalSignatureField*)&m_impl, (TRN_DigestAlgorithm_Type)in_digest_algorithm_type, in_make_mandatory));
}

inline void DigitalSignatureField::CreateSigDictForCustomCertification(const UString& in_filter_name,
	const SubFilterType& in_subfilter_type,
	const UInt32 in_contents_size_to_reserve)
{
	REX(TRN_DigitalSignatureFieldCreateSigDictForCustomCertification((TRN_DigitalSignatureField*)&m_impl, 
		in_filter_name.mp_impl,
		(enum TRN_DigitalSignatureField_SubFilterType) in_subfilter_type,
		in_contents_size_to_reserve));
}

inline void DigitalSignatureField::CreateSigDictForCustomSigning(const UString& in_filter_name,
	const SubFilterType& in_subfilter_type,
	const UInt32 in_contents_size_to_reserve)
{
	REX(TRN_DigitalSignatureFieldCreateSigDictForCustomSigning((TRN_DigitalSignatureField*)&m_impl,
		in_filter_name.mp_impl,
		(enum TRN_DigitalSignatureField_SubFilterType) in_subfilter_type,
		in_contents_size_to_reserve));
}

inline void DigitalSignatureField::SetSigDictTimeOfSigning(const PDF::Date& in_date)
{
	REX(TRN_DigitalSignatureFieldSetSigDictTimeOfSigning((TRN_DigitalSignatureField*)&m_impl, (const TRN_Date*)&in_date));
}

inline std::vector<pdftron::UChar> pdftron::PDF::DigitalSignatureField::SignDigest(const std::vector<UChar>& in_digest, const UString& in_pkcs12_keyfile_path, const UString& in_keyfile_password, const bool in_pades_mode, const Crypto::DigestAlgorithm::Type in_digest_algorithm_type)
{
	TRN_Vector cvector;
	REX(TRN_DigitalSignatureFieldSignDigestPath(in_digest.empty() ? 0 : &in_digest.front(), in_digest.size(), in_pkcs12_keyfile_path.mp_impl, in_keyfile_password.mp_impl, in_pades_mode, (TRN_DigestAlgorithm_Type)in_digest_algorithm_type, &cvector));
	void* arr;
	UInt32 size;
	REX(TRN_VectorGetData(cvector, &arr));
	REX(TRN_VectorGetSize(cvector, &size));
	std::vector<UChar> result(size);
	memcpy(&result[0], arr, size);
	TRN_VectorDestroy(cvector);
	return result;
}

inline std::vector<pdftron::UChar> pdftron::PDF::DigitalSignatureField::SignDigest(const std::vector<UChar>& in_digest, const std::vector<UChar>& in_pkcs12_buffer, const UString& in_keyfile_password, const bool in_pades_mode, const Crypto::DigestAlgorithm::Type in_digest_algorithm_type)
{
	TRN_Vector cvector;
	REX(TRN_DigitalSignatureFieldSignDigestBuffer(in_digest.empty() ? 0 : &in_digest.front(), in_digest.size(), in_pkcs12_buffer.empty() ? 0 : &in_pkcs12_buffer.front(), in_pkcs12_buffer.size(), in_keyfile_password.mp_impl, in_pades_mode, (TRN_DigestAlgorithm_Type)in_digest_algorithm_type, &cvector));
	void* arr;
	UInt32 size;
	REX(TRN_VectorGetData(cvector, &arr));
	REX(TRN_VectorGetSize(cvector, &size));
	std::vector<UChar> result(size);
	memcpy(&result[0], arr, size);
	TRN_VectorDestroy(cvector);
	return result;
}
#ifndef SWIG
inline std::vector<pdftron::UChar> pdftron::PDF::DigitalSignatureField::SignDigest(const UChar* in_digest, const size_t in_digest_size, const UString& in_pkcs12_keyfile_path, const UString& in_keyfile_password, const bool in_pades_mode, const Crypto::DigestAlgorithm::Type in_digest_algorithm_type)
{
	TRN_Vector cvector;
	REX(TRN_DigitalSignatureFieldSignDigestPath(in_digest, in_digest_size, in_pkcs12_keyfile_path.mp_impl, in_keyfile_password.mp_impl, in_pades_mode, (TRN_DigestAlgorithm_Type)in_digest_algorithm_type, &cvector));
	void* arr;
	UInt32 size;
	REX(TRN_VectorGetData(cvector, &arr));
	REX(TRN_VectorGetSize(cvector, &size));
	std::vector<UChar> result(size);
	memcpy(&result[0], arr, size);
	TRN_VectorDestroy(cvector);
	return result;
}

inline std::vector<pdftron::UChar> pdftron::PDF::DigitalSignatureField::SignDigest(const UChar* in_digest, const size_t in_digest_size, const UChar* in_pkcs12_buffer, const size_t in_pkcs12_buffer_size, const UString& in_keyfile_password, const bool in_pades_mode, const Crypto::DigestAlgorithm::Type in_digest_algorithm_type)
{
	TRN_Vector cvector;
	REX(TRN_DigitalSignatureFieldSignDigestBuffer(in_digest, in_digest_size, in_pkcs12_buffer, in_pkcs12_buffer_size, in_keyfile_password.mp_impl, in_pades_mode, (TRN_DigestAlgorithm_Type)in_digest_algorithm_type, &cvector));
	void* arr;
	UInt32 size;
	REX(TRN_VectorGetData(cvector, &arr));
	REX(TRN_VectorGetSize(cvector, &size));
	std::vector<UChar> result(size);
	memcpy(&result[0], arr, size);
	TRN_VectorDestroy(cvector);
	return result;
}
#endif

inline std::vector<UChar> pdftron::PDF::DigitalSignatureField::GenerateESSSigningCertPAdESAttribute(
		const Crypto::X509Certificate& in_signer_cert,
		const Crypto::DigestAlgorithm::Type in_digest_algorithm_type)
{
	TRN_Vector cvector;
	REX(TRN_DigitalSignatureFieldGenerateESSSigningCertPAdESAttribute((TRN_X509Certificate)in_signer_cert.m_impl, (TRN_DigestAlgorithm_Type)in_digest_algorithm_type, &cvector));
	void* arr;
	UInt32 size;
	REX(TRN_VectorGetData(cvector, &arr));
	REX(TRN_VectorGetSize(cvector, &size));
	std::vector<UChar> result(size);
	memcpy(&result[0], arr, size);
	TRN_VectorDestroy(cvector);
	return result;
}

inline std::vector<UChar> pdftron::PDF::DigitalSignatureField::GenerateCMSSignedAttributes(
		const std::vector<UChar>& in_digest_buf,
		const std::vector<UChar>& in_custom_signedattributes_buf)
{
	TRN_Vector cvector;
	REX(TRN_DigitalSignatureFieldGenerateCMSSignedAttributes(in_digest_buf.empty() ? 0 : &in_digest_buf.front(), in_digest_buf.size(), in_custom_signedattributes_buf.empty() ? 0 : &in_custom_signedattributes_buf.front(), in_custom_signedattributes_buf.size(), &cvector));
	void* arr;
	UInt32 size;
	REX(TRN_VectorGetData(cvector, &arr));
	REX(TRN_VectorGetSize(cvector, &size));
	std::vector<UChar> result(size);
	memcpy(&result[0], arr, size);
	TRN_VectorDestroy(cvector);
	return result;
}
#ifndef SWIG
inline std::vector<UChar> pdftron::PDF::DigitalSignatureField::GenerateCMSSignedAttributes(
		const UChar* in_digest_buf,
		const size_t in_digest_buf_size, 
		const UChar* in_custom_signedattributes_buf, 
		const size_t in_custom_signedattributes_buf_size)
{
	TRN_Vector cvector;
	REX(TRN_DigitalSignatureFieldGenerateCMSSignedAttributes(in_digest_buf, in_digest_buf_size, in_custom_signedattributes_buf, in_custom_signedattributes_buf_size, &cvector));
	void* arr;
	UInt32 size;
	REX(TRN_VectorGetData(cvector, &arr));
	REX(TRN_VectorGetSize(cvector, &size));
	std::vector<UChar> result(size);
	memcpy(&result[0], arr, size);
	TRN_VectorDestroy(cvector);
	return result;
}
#endif

inline std::vector<UChar> pdftron::PDF::DigitalSignatureField::GenerateCMSSignature(
		const Crypto::X509Certificate& in_signer_cert,
		const std::vector<Crypto::X509Certificate>& in_chain_certs_buf,
		const Crypto::ObjectIdentifier& in_digest_algorithm_oid,
		const Crypto::ObjectIdentifier& in_signature_algorithm_oid,
		const std::vector<UChar>& in_signature_value_buf,
		const std::vector<UChar>& in_signedattributes_buf)
{
	std::vector<TRN_X509Certificate> chain_certs_buf_in_internal_format;
	for (size_t i = 0; i < in_chain_certs_buf.size(); i++)
	{
		chain_certs_buf_in_internal_format.push_back((TRN_X509Certificate)in_chain_certs_buf[i].m_impl);
	}

	TRN_Vector cvector;
	REX(TRN_DigitalSignatureFieldGenerateCMSSignature((TRN_X509Certificate)in_signer_cert.m_impl, (TRN_X509Certificate*)(chain_certs_buf_in_internal_format.empty() ? 0 : &chain_certs_buf_in_internal_format.front()), chain_certs_buf_in_internal_format.size(), (TRN_ObjectIdentifier)in_digest_algorithm_oid.m_impl, (TRN_ObjectIdentifier)in_signature_algorithm_oid.m_impl, 
		in_signature_value_buf.empty() ? 0 : &in_signature_value_buf.front(), in_signature_value_buf.size(), in_signedattributes_buf.empty() ? 0 : &in_signedattributes_buf.front(), in_signedattributes_buf.size(), &cvector));
	void* arr;
	UInt32 size;
	REX(TRN_VectorGetData(cvector, &arr));
	REX(TRN_VectorGetSize(cvector, &size));
	std::vector<UChar> result(size);
	memcpy(&result[0], arr, size);
	TRN_VectorDestroy(cvector);
	return result;
}
#ifndef SWIG
inline std::vector<UChar> pdftron::PDF::DigitalSignatureField::GenerateCMSSignature(
		const Crypto::X509Certificate& in_signer_cert,
		const Crypto::X509Certificate* in_chain_certs_buf,
		const size_t in_chain_certs_buf_size,
		const Crypto::ObjectIdentifier& in_digest_algorithm_oid,
		const Crypto::ObjectIdentifier& in_signature_algorithm_oid,
		const UChar* in_signature_value_buf,
		const size_t in_signature_value_buf_size,
		const UChar* in_signedattributes_buf,
		const size_t in_signedattributes_buf_size)
{
	std::vector<TRN_X509Certificate> chain_certs_buf_in_internal_format;
	for (size_t i = 0; i < in_chain_certs_buf_size; i++)
	{
		chain_certs_buf_in_internal_format.push_back((TRN_X509Certificate)in_chain_certs_buf[i].m_impl);
	}

	TRN_Vector cvector;
	REX(TRN_DigitalSignatureFieldGenerateCMSSignature((TRN_X509Certificate)in_signer_cert.m_impl, (TRN_X509Certificate*)(chain_certs_buf_in_internal_format.empty() ? 0 : &chain_certs_buf_in_internal_format.front()), chain_certs_buf_in_internal_format.size(), (TRN_ObjectIdentifier)in_digest_algorithm_oid.m_impl, (TRN_ObjectIdentifier)in_signature_algorithm_oid.m_impl, in_signature_value_buf, in_signature_value_buf_size, in_signedattributes_buf, in_signedattributes_buf_size, &cvector));
	void* arr;
	UInt32 size;
	REX(TRN_VectorGetData(cvector, &arr));
	REX(TRN_VectorGetSize(cvector, &size));
	std::vector<UChar> result(size);
	memcpy(&result[0], arr, size);
	TRN_VectorDestroy(cvector);
	return result;
}
#endif
