#ifndef JSONPARSEUTIL_GLOBAL_H
#define JSONPARSEUTIL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(JSONPARSEUTIL_LIBRARY)
#  define JSONPARSEUTILSHARED_EXPORT Q_DECL_EXPORT
#else
#  define JSONPARSEUTILSHARED_EXPORT Q_DECL_IMPORT
#endif

#include "allocator.h"
#include "assertions.h"
#include "autolink.h"
#include "config.h"
#include "features.h"
#include "forwards.h"
#include "json_batchallocator.h"
#include "reader.h"
#include "value.h"
#include "version.h"
#include "writer.h"


#endif // JSONPARSEUTIL_GLOBAL_H
