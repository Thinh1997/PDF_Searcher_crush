inline ObjectIdentifier::~ObjectIdentifier()
{
	Destroy();
}

#ifdef SWIG
inline ObjectIdentifier::ObjectIdentifier()
	: m_impl(0)
	, m_owner(false)
{}
#endif

inline ObjectIdentifier::ObjectIdentifier(const ObjectIdentifier& other)
	: m_impl(other.m_impl)
	, m_owner(false)
{
	if(other.m_owner) {
		other.m_owner = false;
		m_owner = true;
	}
}

inline void ObjectIdentifier::Destroy()
{
	if(m_owner)
	{
		DREX(m_impl, TRN_ObjectIdentifierDestroy(m_impl));
		m_owner = false;
	}
}

inline ObjectIdentifier& ObjectIdentifier::operator= (const ObjectIdentifier& other)
{
	Destroy();

	m_impl = other.m_impl;

	if(other.m_owner) {
		other.m_owner = false;
		m_owner = true;
	}

	return *this;
}

inline ObjectIdentifier::ObjectIdentifier(TRN_ObjectIdentifier impl)
	: m_impl(impl)
	, m_owner(true)
{}

inline ObjectIdentifier::ObjectIdentifier(const Predefined in_oid_enum)
	: m_owner(true)
{
	REX(TRN_ObjectIdentifierCreateFromPredefined((enum TRN_ObjectIdentifier_Predefined*)&in_oid_enum, &m_impl));
}

#ifdef SWIG
inline ObjectIdentifier::ObjectIdentifier(const std::vector<int>& in_arr)
	: m_owner(true)
{
	std::vector<UInt32> arr;
	for (size_t i = 0; i < in_arr.size(); i++)
	{
		BASE_ASSERT(in_arr[i] >= 0, "Invalid OID component -- component integer is less than zero.");
		arr.push_back((UInt32) in_arr[i]);
	}
	REX(TRN_ObjectIdentifierCreateFromIntArray((TRN_UInt32*)(arr.empty() ? 0 : &arr.front()), (TRN_UInt32)arr.size(), &m_impl));
}
#else
inline ObjectIdentifier::ObjectIdentifier(const UInt32* in_arr, const size_t in_size)
	: m_owner(true)
{
	REX(TRN_ObjectIdentifierCreateFromIntArray((TRN_UInt32*)in_arr, (TRN_UInt32)in_size, &m_impl));
}
#endif

inline ObjectIdentifier::ObjectIdentifier(const DigestAlgorithm::Type in_digest_algorithm_type)
	: m_owner(true)
{
	REX(TRN_ObjectIdentifierCreateFromDigestAlgorithm((TRN_DigestAlgorithm_Type)in_digest_algorithm_type, &m_impl));
}

inline std::vector<UInt32> ObjectIdentifier::GetRawValue() const
{
	TRN_Vector vec = NULL;
	REX(TRN_ObjectIdentifierGetRawValue((TRN_ObjectIdentifier)m_impl,(TRN_Vector*)&vec));

	TRN_UInt32 vec_size;
	TRN_VectorGetSize(vec, &vec_size);

	std::vector<UInt32> result;
	for (TRN_UInt32 i = 0; i < vec_size; i++)
	{
		TRN_UInt32* current_ustr = NULL;
		TRN_VectorGetAt(vec, i, (void**)&current_ustr);
		result.push_back((UInt32)(*current_ustr));
	}

	TRN_VectorDestroyKeepContents(vec);
	return result;
}

