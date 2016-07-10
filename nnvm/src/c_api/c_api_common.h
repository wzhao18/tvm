/*!
 *  Copyright (c) 2016 by Contributors
 * \file c_api_error.h
 * \brief Common fields of all C APIs
 */
#ifndef NNVM_C_API_C_API_COMMON_H_
#define NNVM_C_API_C_API_COMMON_H_

#include <dmlc/base.h>
#include <dmlc/logging.h>
#include <dmlc/thread_local.h>
#include <nnvm/c_api.h>
#include <vector>
#include <string>

/*! \brief  macro to guard beginning and end section of all functions */
#define API_BEGIN() try {
/*! \brief every function starts with API_BEGIN();
     and finishes with API_END() or API_END_HANDLE_ERROR */
#define API_END() } catch(dmlc::Error &_except_) { return NNAPIHandleException(_except_); } return 0;  // NOLINT(*)
/*!
 * \brief every function starts with API_BEGIN();
 *   and finishes with API_END() or API_END_HANDLE_ERROR
 *   The finally clause contains procedure to cleanup states when an error happens.
 */
#define API_END_HANDLE_ERROR(Finalize) } catch(dmlc::Error &_except_) { Finalize; return NNAPIHandleException(_except_); } return 0; // NOLINT(*)


/*! \brief entry to to easily hold returning information */
struct NNAPIThreadLocalEntry {
  /*! \brief result holder for returning string */
  std::string ret_str;
  /*! \brief result holder for returning strings */
  std::vector<std::string> ret_vec_str;
  /*! \brief result holder for returning string pointers */
  std::vector<const char *> ret_vec_charp;
  /*! \brief result holder for returning handles */
  std::vector<void *> ret_handles;
};

/*! \brief Thread local store that can be used to hold return values. */
typedef dmlc::ThreadLocalStore<NNAPIThreadLocalEntry> NNAPIThreadLocalStore;

/*!
 * \brief Set the last error message needed by C API
 * \param msg The error message to set.
 */
void NNAPISetLastError(const char* msg);
/*!
 * \brief handle exception throwed out
 * \param e the exception
 * \return the return value of API after exception is handled
 */
inline int NNAPIHandleException(const dmlc::Error &e) {
  NNAPISetLastError(e.what());
  return -1;
}

#endif  // NNVM_C_API_C_API_COMMON_H_
