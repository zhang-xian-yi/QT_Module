#ifndef JSONPARSEUTIL_GLOBAL_H
#define JSONPARSEUTIL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(JSONPARSEUTIL_LIBRARY)
#  define JSONPARSEUTILSHARED_EXPORT Q_DECL_EXPORT
#else
#  define JSONPARSEUTILSHARED_EXPORT Q_DECL_IMPORT
#endif

#include "json/allocator.h"
#include "json/assertions.h"
#include "json/autolink.h"
#include "json/config.h"
#include "json/features.h"
#include "json/forwards.h"
#include "json/json_batchallocator.h"
#include "json/reader.h"
#include "json/value.h"
#include "json/version.h"
#include "json/writer.h"


#endif // JSONPARSEUTIL_GLOBAL_H
