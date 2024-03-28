// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtocolServerToClient.proto

#include "ProtocolServerToClient.pb.h"

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

namespace ProtocolServerToClient {
PROTOBUF_CONSTEXPR ResultLogin::ResultLogin(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.m_success_)*/false
  , /*decltype(_impl_.m_playercount_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct ResultLoginDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ResultLoginDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~ResultLoginDefaultTypeInternal() {}
  union {
    ResultLogin _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ResultLoginDefaultTypeInternal _ResultLogin_default_instance_;
PROTOBUF_CONSTEXPR ResultCreateAccount::ResultCreateAccount(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.m_success_)*/false
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct ResultCreateAccountDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ResultCreateAccountDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~ResultCreateAccountDefaultTypeInternal() {}
  union {
    ResultCreateAccount _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ResultCreateAccountDefaultTypeInternal _ResultCreateAccount_default_instance_;
}  // namespace ProtocolServerToClient
static ::_pb::Metadata file_level_metadata_ProtocolServerToClient_2eproto[2];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_ProtocolServerToClient_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_ProtocolServerToClient_2eproto = nullptr;

const uint32_t TableStruct_ProtocolServerToClient_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::ProtocolServerToClient::ResultLogin, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::ProtocolServerToClient::ResultLogin, _impl_.m_success_),
  PROTOBUF_FIELD_OFFSET(::ProtocolServerToClient::ResultLogin, _impl_.m_playercount_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::ProtocolServerToClient::ResultCreateAccount, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::ProtocolServerToClient::ResultCreateAccount, _impl_.m_success_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::ProtocolServerToClient::ResultLogin)},
  { 8, -1, -1, sizeof(::ProtocolServerToClient::ResultCreateAccount)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::ProtocolServerToClient::_ResultLogin_default_instance_._instance,
  &::ProtocolServerToClient::_ResultCreateAccount_default_instance_._instance,
};

const char descriptor_table_protodef_ProtocolServerToClient_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\034ProtocolServerToClient.proto\022\026Protocol"
  "ServerToClient\032 ProtocolServerToClientEn"
  "um.proto\"7\n\013ResultLogin\022\021\n\tm_success\030\001 \001"
  "(\010\022\025\n\rm_playerCount\030\002 \001(\005\"(\n\023ResultCreat"
  "eAccount\022\021\n\tm_success\030\001 \001(\010b\006proto3"
  ;
static const ::_pbi::DescriptorTable* const descriptor_table_ProtocolServerToClient_2eproto_deps[1] = {
  &::descriptor_table_ProtocolServerToClientEnum_2eproto,
};
static ::_pbi::once_flag descriptor_table_ProtocolServerToClient_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_ProtocolServerToClient_2eproto = {
    false, false, 195, descriptor_table_protodef_ProtocolServerToClient_2eproto,
    "ProtocolServerToClient.proto",
    &descriptor_table_ProtocolServerToClient_2eproto_once, descriptor_table_ProtocolServerToClient_2eproto_deps, 1, 2,
    schemas, file_default_instances, TableStruct_ProtocolServerToClient_2eproto::offsets,
    file_level_metadata_ProtocolServerToClient_2eproto, file_level_enum_descriptors_ProtocolServerToClient_2eproto,
    file_level_service_descriptors_ProtocolServerToClient_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_ProtocolServerToClient_2eproto_getter() {
  return &descriptor_table_ProtocolServerToClient_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_ProtocolServerToClient_2eproto(&descriptor_table_ProtocolServerToClient_2eproto);
namespace ProtocolServerToClient {

// ===================================================================

class ResultLogin::_Internal {
 public:
};

ResultLogin::ResultLogin(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:ProtocolServerToClient.ResultLogin)
}
ResultLogin::ResultLogin(const ResultLogin& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  ResultLogin* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.m_success_){}
    , decltype(_impl_.m_playercount_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&_impl_.m_success_, &from._impl_.m_success_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.m_playercount_) -
    reinterpret_cast<char*>(&_impl_.m_success_)) + sizeof(_impl_.m_playercount_));
  // @@protoc_insertion_point(copy_constructor:ProtocolServerToClient.ResultLogin)
}

inline void ResultLogin::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.m_success_){false}
    , decltype(_impl_.m_playercount_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

ResultLogin::~ResultLogin() {
  // @@protoc_insertion_point(destructor:ProtocolServerToClient.ResultLogin)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void ResultLogin::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void ResultLogin::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void ResultLogin::Clear() {
// @@protoc_insertion_point(message_clear_start:ProtocolServerToClient.ResultLogin)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&_impl_.m_success_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.m_playercount_) -
      reinterpret_cast<char*>(&_impl_.m_success_)) + sizeof(_impl_.m_playercount_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ResultLogin::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // bool m_success = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.m_success_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 m_playerCount = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.m_playercount_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
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

uint8_t* ResultLogin::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ProtocolServerToClient.ResultLogin)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // bool m_success = 1;
  if (this->_internal_m_success() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteBoolToArray(1, this->_internal_m_success(), target);
  }

  // int32 m_playerCount = 2;
  if (this->_internal_m_playercount() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(2, this->_internal_m_playercount(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ProtocolServerToClient.ResultLogin)
  return target;
}

size_t ResultLogin::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ProtocolServerToClient.ResultLogin)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bool m_success = 1;
  if (this->_internal_m_success() != 0) {
    total_size += 1 + 1;
  }

  // int32 m_playerCount = 2;
  if (this->_internal_m_playercount() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_m_playercount());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData ResultLogin::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    ResultLogin::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*ResultLogin::GetClassData() const { return &_class_data_; }


void ResultLogin::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<ResultLogin*>(&to_msg);
  auto& from = static_cast<const ResultLogin&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:ProtocolServerToClient.ResultLogin)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_m_success() != 0) {
    _this->_internal_set_m_success(from._internal_m_success());
  }
  if (from._internal_m_playercount() != 0) {
    _this->_internal_set_m_playercount(from._internal_m_playercount());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void ResultLogin::CopyFrom(const ResultLogin& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ProtocolServerToClient.ResultLogin)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ResultLogin::IsInitialized() const {
  return true;
}

void ResultLogin::InternalSwap(ResultLogin* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(ResultLogin, _impl_.m_playercount_)
      + sizeof(ResultLogin::_impl_.m_playercount_)
      - PROTOBUF_FIELD_OFFSET(ResultLogin, _impl_.m_success_)>(
          reinterpret_cast<char*>(&_impl_.m_success_),
          reinterpret_cast<char*>(&other->_impl_.m_success_));
}

::PROTOBUF_NAMESPACE_ID::Metadata ResultLogin::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_ProtocolServerToClient_2eproto_getter, &descriptor_table_ProtocolServerToClient_2eproto_once,
      file_level_metadata_ProtocolServerToClient_2eproto[0]);
}

// ===================================================================

class ResultCreateAccount::_Internal {
 public:
};

ResultCreateAccount::ResultCreateAccount(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:ProtocolServerToClient.ResultCreateAccount)
}
ResultCreateAccount::ResultCreateAccount(const ResultCreateAccount& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  ResultCreateAccount* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.m_success_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _this->_impl_.m_success_ = from._impl_.m_success_;
  // @@protoc_insertion_point(copy_constructor:ProtocolServerToClient.ResultCreateAccount)
}

inline void ResultCreateAccount::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.m_success_){false}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

ResultCreateAccount::~ResultCreateAccount() {
  // @@protoc_insertion_point(destructor:ProtocolServerToClient.ResultCreateAccount)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void ResultCreateAccount::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void ResultCreateAccount::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void ResultCreateAccount::Clear() {
// @@protoc_insertion_point(message_clear_start:ProtocolServerToClient.ResultCreateAccount)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.m_success_ = false;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ResultCreateAccount::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // bool m_success = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.m_success_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
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

uint8_t* ResultCreateAccount::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ProtocolServerToClient.ResultCreateAccount)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // bool m_success = 1;
  if (this->_internal_m_success() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteBoolToArray(1, this->_internal_m_success(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ProtocolServerToClient.ResultCreateAccount)
  return target;
}

size_t ResultCreateAccount::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ProtocolServerToClient.ResultCreateAccount)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bool m_success = 1;
  if (this->_internal_m_success() != 0) {
    total_size += 1 + 1;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData ResultCreateAccount::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    ResultCreateAccount::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*ResultCreateAccount::GetClassData() const { return &_class_data_; }


void ResultCreateAccount::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<ResultCreateAccount*>(&to_msg);
  auto& from = static_cast<const ResultCreateAccount&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:ProtocolServerToClient.ResultCreateAccount)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_m_success() != 0) {
    _this->_internal_set_m_success(from._internal_m_success());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void ResultCreateAccount::CopyFrom(const ResultCreateAccount& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ProtocolServerToClient.ResultCreateAccount)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ResultCreateAccount::IsInitialized() const {
  return true;
}

void ResultCreateAccount::InternalSwap(ResultCreateAccount* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_.m_success_, other->_impl_.m_success_);
}

::PROTOBUF_NAMESPACE_ID::Metadata ResultCreateAccount::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_ProtocolServerToClient_2eproto_getter, &descriptor_table_ProtocolServerToClient_2eproto_once,
      file_level_metadata_ProtocolServerToClient_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace ProtocolServerToClient
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::ProtocolServerToClient::ResultLogin*
Arena::CreateMaybeMessage< ::ProtocolServerToClient::ResultLogin >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ProtocolServerToClient::ResultLogin >(arena);
}
template<> PROTOBUF_NOINLINE ::ProtocolServerToClient::ResultCreateAccount*
Arena::CreateMaybeMessage< ::ProtocolServerToClient::ResultCreateAccount >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ProtocolServerToClient::ResultCreateAccount >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
