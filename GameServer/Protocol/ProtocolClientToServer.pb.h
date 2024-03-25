// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtocolClientToServer.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_ProtocolClientToServer_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_ProtocolClientToServer_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "ProtocolClientToServerEnum.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_ProtocolClientToServer_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_ProtocolClientToServer_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ProtocolClientToServer_2eproto;
namespace ProtocolClientToServer {
class RequestLogin;
struct RequestLoginDefaultTypeInternal;
extern RequestLoginDefaultTypeInternal _RequestLogin_default_instance_;
}  // namespace ProtocolClientToServer
PROTOBUF_NAMESPACE_OPEN
template<> ::ProtocolClientToServer::RequestLogin* Arena::CreateMaybeMessage<::ProtocolClientToServer::RequestLogin>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace ProtocolClientToServer {

// ===================================================================

class RequestLogin final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:ProtocolClientToServer.RequestLogin) */ {
 public:
  inline RequestLogin() : RequestLogin(nullptr) {}
  ~RequestLogin() override;
  explicit PROTOBUF_CONSTEXPR RequestLogin(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  RequestLogin(const RequestLogin& from);
  RequestLogin(RequestLogin&& from) noexcept
    : RequestLogin() {
    *this = ::std::move(from);
  }

  inline RequestLogin& operator=(const RequestLogin& from) {
    CopyFrom(from);
    return *this;
  }
  inline RequestLogin& operator=(RequestLogin&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const RequestLogin& default_instance() {
    return *internal_default_instance();
  }
  static inline const RequestLogin* internal_default_instance() {
    return reinterpret_cast<const RequestLogin*>(
               &_RequestLogin_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(RequestLogin& a, RequestLogin& b) {
    a.Swap(&b);
  }
  inline void Swap(RequestLogin* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(RequestLogin* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  RequestLogin* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<RequestLogin>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const RequestLogin& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const RequestLogin& from) {
    RequestLogin::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(RequestLogin* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "ProtocolClientToServer.RequestLogin";
  }
  protected:
  explicit RequestLogin(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMAccountIDFieldNumber = 1,
  };
  // string m_accountID = 1;
  void clear_m_accountid();
  const std::string& m_accountid() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_m_accountid(ArgT0&& arg0, ArgT... args);
  std::string* mutable_m_accountid();
  PROTOBUF_NODISCARD std::string* release_m_accountid();
  void set_allocated_m_accountid(std::string* m_accountid);
  private:
  const std::string& _internal_m_accountid() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_m_accountid(const std::string& value);
  std::string* _internal_mutable_m_accountid();
  public:

  // @@protoc_insertion_point(class_scope:ProtocolClientToServer.RequestLogin)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr m_accountid_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_ProtocolClientToServer_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// RequestLogin

// string m_accountID = 1;
inline void RequestLogin::clear_m_accountid() {
  _impl_.m_accountid_.ClearToEmpty();
}
inline const std::string& RequestLogin::m_accountid() const {
  // @@protoc_insertion_point(field_get:ProtocolClientToServer.RequestLogin.m_accountID)
  return _internal_m_accountid();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void RequestLogin::set_m_accountid(ArgT0&& arg0, ArgT... args) {
 
 _impl_.m_accountid_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:ProtocolClientToServer.RequestLogin.m_accountID)
}
inline std::string* RequestLogin::mutable_m_accountid() {
  std::string* _s = _internal_mutable_m_accountid();
  // @@protoc_insertion_point(field_mutable:ProtocolClientToServer.RequestLogin.m_accountID)
  return _s;
}
inline const std::string& RequestLogin::_internal_m_accountid() const {
  return _impl_.m_accountid_.Get();
}
inline void RequestLogin::_internal_set_m_accountid(const std::string& value) {
  
  _impl_.m_accountid_.Set(value, GetArenaForAllocation());
}
inline std::string* RequestLogin::_internal_mutable_m_accountid() {
  
  return _impl_.m_accountid_.Mutable(GetArenaForAllocation());
}
inline std::string* RequestLogin::release_m_accountid() {
  // @@protoc_insertion_point(field_release:ProtocolClientToServer.RequestLogin.m_accountID)
  return _impl_.m_accountid_.Release();
}
inline void RequestLogin::set_allocated_m_accountid(std::string* m_accountid) {
  if (m_accountid != nullptr) {
    
  } else {
    
  }
  _impl_.m_accountid_.SetAllocated(m_accountid, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.m_accountid_.IsDefault()) {
    _impl_.m_accountid_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:ProtocolClientToServer.RequestLogin.m_accountID)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace ProtocolClientToServer

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_ProtocolClientToServer_2eproto
