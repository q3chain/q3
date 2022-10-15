// Copyright (c) 2014-2019 Coin Sciences Ltd
// q3chain code distributed under the GPLv3 license, see COPYING file.

#ifndef q3chainVERSION_H
#define	q3chainVERSION_H

#define q3chain_VERSION_MAJOR     1
#define q3chain_VERSION_MINOR     0
#define q3chain_VERSION_REVISION  0
#define q3chain_VERSION_STAGE     2
#define q3chain_VERSION_BUILD     2

#define q3chain_PROTOCOL_VERSION 10008
#define q3chain_PROTOCOL_SUPPORTED "10004 - 10008, 20001"


#ifndef STRINGIZE
#define STRINGIZE(X) DO_STRINGIZE(X)
#endif

#ifndef DO_STRINGIZE
#define DO_STRINGIZE(X) #X
#endif

#define q3chain_BUILD_DESC_WITH_SUFFIX(maj, min, rev, build, suffix) \
    DO_STRINGIZE(maj) "." DO_STRINGIZE(min) "." DO_STRINGIZE(rev) "." DO_STRINGIZE(build) "-" DO_STRINGIZE(suffix)

#define q3chain_BUILD_DESC_FROM_UNKNOWN(maj, min, rev, build) \
    DO_STRINGIZE(maj) "." DO_STRINGIZE(min) "." DO_STRINGIZE(rev) "." DO_STRINGIZE(build)


#define q3chain_BUILD_DESC "1.0 beta 2"
#define q3chain_BUILD_DESC_NUMERIC 10000202


#ifndef q3chain_BUILD_DESC
#ifdef BUILD_SUFFIX
#define q3chain_BUILD_DESC q3chain_BUILD_DESC_WITH_SUFFIX(q3chain_VERSION_MAJOR, q3chain_VERSION_MINOR, q3chain_VERSION_REVISION, q3chain_VERSION_BUILD, BUILD_SUFFIX)
#else
#define q3chain_BUILD_DESC q3chain_BUILD_DESC_FROM_UNKNOWN(q3chain_VERSION_MAJOR, q3chain_VERSION_MINOR, q3chain_VERSION_REVISION, q3chain_VERSION_BUILD)
#endif
#endif

#define q3chain_FULL_DESC(build, protocol) \
    "build " build " protocol " DO_STRINGIZE(protocol)


#ifndef q3chain_FULL_VERSION
#define q3chain_FULL_VERSION q3chain_FULL_DESC(q3chain_BUILD_DESC, q3chain_PROTOCOL_VERSION)
#endif


#define q3chain_VERSION_CODE_PROTOCOL_THIS              0
#define q3chain_VERSION_CODE_PROTOCOL_MIN               1
#define q3chain_VERSION_CODE_PROTOCOL_MIN_DOWNGRADE     2
#define q3chain_VERSION_CODE_PROTOCOL_MIN_NO_DOWNGRADE  3
#define q3chain_VERSION_CODE_PROTOCOL_FOR_RELEVANCE     4
#define q3chain_VERSION_CODE_BUILD                     16
#define q3chain_VERSION_CODE_MIN_VALID               1000

#endif	/* q3chainVERSION_H */

