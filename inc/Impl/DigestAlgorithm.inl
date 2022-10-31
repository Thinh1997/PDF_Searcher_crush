inline std::vector<UChar> DigestAlgorithm::CalculateDigest(DigestAlgorithm::Type in_digest_algorithm_type, const std::vector<UChar>& in_message_buf)
{
	TRN_Vector cvector;
	REX(TRN_DigestAlgorithmCalculateDigest((TRN_DigestAlgorithm_Type)in_digest_algorithm_type, in_message_buf.empty() ? 0 : &in_message_buf.front(), in_message_buf.size(), &cvector));
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
inline std::vector<UChar> DigestAlgorithm::CalculateDigest(DigestAlgorithm::Type in_digest_algorithm_type, const UChar* in_message_buf, const size_t in_message_buf_size)
{
	TRN_Vector cvector;
	REX(TRN_DigestAlgorithmCalculateDigest((TRN_DigestAlgorithm_Type)in_digest_algorithm_type, in_message_buf, in_message_buf_size, &cvector));
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
