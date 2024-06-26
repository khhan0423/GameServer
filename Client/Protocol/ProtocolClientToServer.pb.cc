// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtocolClientToServer.proto

#include "ProtocolClientToServer.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace ProtocolClientToServer {
PROTOBUF_CONSTEXPR RequestLogin::RequestLogin(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.m_accountid_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct RequestLoginDefaultTypeInternal {
  PROTOBUF_CONSTEXPR RequestLoginDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~RequestLoginDefaultTypeInternal() {}
  union {
    RequestLogin _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 RequestLoginDefaultTypeInternal _RequestLogin_default_instance_;
PROTOBUF_CONSTEXPR RequestCreateAccount::RequestCreateAccount(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.m_accountid_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct RequestCreateAccountDefaultTypeInternal {
  PROTOBUF_CONSTEXPR RequestCreateAccountDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~RequestCreateAccountDefaultTypeInternal() {}
  union {
    RequestCreateAccount _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 RequestCreateAccountDefaultTypeInternal _RequestCreateAccount_default_instance_;
}  // namespace ProtocolClientToServer
static ::_pb::Metadata file_level_metadata_ProtocolClientToServer_2eproto[2];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_ProtocolClientToServer_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_ProtocolClientToServer_2eproto = nullptr;

const uint32_t TableStruct_ProtocolClientToServer_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::ProtocolClientToServer::RequestLogin, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::ProtocolClientToServer::RequestLogin, _impl_.m_accountid_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::ProtocolClientToServer::RequestCreateAccount, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::ProtocolClientToServer::RequestCreateAccount, _impl_.m_accountid_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::ProtocolClientToServer::RequestLogin)},
  { 7, -1, -1, sizeof(::ProtocolClientToServer::RequestCreateAccount)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::ProtocolClientToServer::_RequestLogin_default_instance_._instance,
  &::ProtocolClientToServer::_RequestCreateAccount_default_instance_._instance,
};

const char descriptor_table_protodef_ProtocolClientToServer_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\034ProtocolClientToServer.proto\022\026Protocol"
  "ClientToServer\032 ProtocolClientToServerEn"
  "um.proto\"#\n\014RequestLogin\022\023\n\013m_accountID\030"
  "\001 \001(\t\"+\n\024RequestCreateAccount\022\023\n\013m_accou"
  "ntID\030\001 \001(\tb\006proto3"
  ;
static const ::_pbi::DescriptorTable* const descriptor_table_ProtocolClientToServer_2eproto_deps[1] = {
  &::descriptor_table_ProtocolClientToServerEnum_2eproto,
};
static ::_pbi::once_flag descriptor_table_ProtocolClientToServer_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_ProtocolClientToServer_2eproto = {
    false, false, 178, descriptor_table_protodef_ProtocolClientToServer_2eproto,
    "ProtocolClientToServer.proto",
    &descriptor_table_ProtocolClientToServer_2eproto_once, descriptor_table_ProtocolClientToServer_2eproto_deps, 1, 2,
    schemas, file_default_instances, TableStruct_ProtocolClientToServer_2eproto::offsets,
    file_level_metadata_ProtocolClientToServer_2eproto, file_level_enum_descriptors_ProtocolClientToServer_2eproto,
    file_level_service_descriptors_ProtocolClientToServer_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_ProtocolClientToServer_2eproto_getter() {
  return &descriptor_table_ProtocolClientToServer_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_ProtocolClientToServer_2eproto(&descriptor_table_ProtocolClientToServer_2eproto);
namespace ProtocolClientToServer {

// ===================================================================

class RequestLogin::_Internal {
 public:
};

RequestLogin::RequestLogin(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:ProtocolClientToServer.RequestLogin)
}
RequestLogin::RequestLogin(const RequestLogin& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  RequestLogin* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.m_accountid_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.m_accountid_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.m_accountid_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_m_accountid().empty()) {
    _this->_impl_.m_accountid_.Set(from._internal_m_accountid(), 
      _this->GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:ProtocolClientToServer.RequestLogin)
}

inline void RequestLogin::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.m_accountid_){}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.m_accountid_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.m_accountid_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

RequestLogin::~RequestLogin() {
  // @@protoc_insertion_point(destructor:ProtocolClientToServer.RequestLogin)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void RequestLogin::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.m_accountid_.Destroy();
}

void RequestLogin::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void RequestLogin::Clear() {
// @@protoc_insertion_point(message_clear_start:ProtocolClientToServer.RequestLogin)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.m_accountid_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* RequestLogin::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string m_accountID = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_m_accountid();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "ProtocolClientToServer.RequestLogin.m_accountID"));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* RequestLogin::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ProtocolClientToServer.RequestLogin)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string m_accountID = 1;
  if (!this->_internal_m_accountid().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_m_accountid().data(), static_cast<int>(this->_internal_m_accountid().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "ProtocolClientToServer.RequestLogin.m_accountID");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_m_accountid(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ProtocolClientToServer.RequestLogin)
  return target;
}

size_t RequestLogin::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ProtocolClientToServer.RequestLogin)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string m_accountID = 1;
  if (!this->_internal_m_accountid().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_m_accountid());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData RequestLogin::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    RequestLogin::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*RequestLogin::GetClassData() const { return &_class_data_; }


void RequestLogin::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<RequestLogin*>(&to_msg);
  auto& from = static_cast<const RequestLogin&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:ProtocolClientToServer.RequestLogin)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_m_accountid().empty()) {
    _this->_internal_set_m_accountid(from._internal_m_accountid());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void RequestLogin::CopyFrom(const RequestLogin& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ProtocolClientToServer.RequestLogin)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RequestLogin::IsInitialized() const {
  return true;
}

void RequestLogin::InternalSwap(RequestLogin* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.m_accountid_, lhs_arena,
      &other->_impl_.m_accountid_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata RequestLogin::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_ProtocolClientToServer_2eproto_getter, &descriptor_table_ProtocolClientToServer_2eproto_once,
      file_level_metadata_ProtocolClientToServer_2eproto[0]);
}

// ===================================================================

class RequestCreateAccount::_Internal {
 public:
};

RequestCreateAccount::RequestCreateAccount(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:ProtocolClientToServer.RequestCreateAccount)
}
RequestCreateAccount::RequestCreateAccount(const RequestCreateAccount& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  RequestCreateAccount* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.m_accountid_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.m_accountid_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.m_accountid_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_m_accountid().empty()) {
    _this->_impl_.m_accountid_.Set(from._internal_m_accountid(), 
      _this->GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:ProtocolClientToServer.RequestCreateAccount)
}

inline void RequestCreateAccount::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.m_accountid_){}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.m_accountid_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.m_accountid_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

RequestCreateAccount::~RequestCreateAccount() {
  // @@protoc_insertion_point(destructor:ProtocolClientToServer.RequestCreateAccount)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void RequestCreateAccount::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.m_accountid_.Destroy();
}

void RequestCreateAccount::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void RequestCreateAccount::Clear() {
// @@protoc_insertion_point(message_clear_start:ProtocolClientToServer.RequestCreateAccount)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.m_accountid_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* RequestCreateAccount::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string m_accountID = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_m_accountid();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "ProtocolClientToServer.RequestCreateAccount.m_accountID"));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* RequestCreateAccount::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ProtocolClientToServer.RequestCreateAccount)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string m_accountID = 1;
  if (!this->_internal_m_accountid().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_m_accountid().data(), static_cast<int>(this->_internal_m_accountid().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "ProtocolClientToServer.RequestCreateAccount.m_accountID");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_m_accountid(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ProtocolClientToServer.RequestCreateAccount)
  return target;
}

size_t RequestCreateAccount::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ProtocolClientToServer.RequestCreateAccount)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string m_accountID = 1;
  if (!this->_internal_m_accountid().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_m_accountid());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData RequestCreateAccount::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    RequestCreateAccount::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*RequestCreateAccount::GetClassData() const { return &_class_data_; }


void RequestCreateAccount::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<RequestCreateAccount*>(&to_msg);
  auto& from = static_cast<const RequestCreateAccount&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:ProtocolClientToServer.RequestCreateAccount)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_m_accountid().empty()) {
    _this->_internal_set_m_accountid(from._internal_m_accountid());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void RequestCreateAccount::CopyFrom(const RequestCreateAccount& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ProtocolClientToServer.RequestCreateAccount)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RequestCreateAccount::IsInitialized() const {
  return true;
}

void RequestCreateAccount::InternalSwap(RequestCreateAccount* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.m_accountid_, lhs_arena,
      &other->_impl_.m_accountid_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata RequestCreateAccount::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_ProtocolClientToServer_2eproto_getter, &descriptor_table_ProtocolClientToServer_2eproto_once,
      file_level_metadata_ProtocolClientToServer_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace ProtocolClientToServer
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::ProtocolClientToServer::RequestLogin*
Arena::CreateMaybeMessage< ::ProtocolClientToServer::RequestLogin >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ProtocolClientToServer::RequestLogin >(arena);
}
template<> PROTOBUF_NOINLINE ::ProtocolClientToServer::RequestCreateAccount*
Arena::CreateMaybeMessage< ::ProtocolClientToServer::RequestCreateAccount >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ProtocolClientToServer::RequestCreateAccount >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
