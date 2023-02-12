#ifndef LOAD3DMODEL_GLOBAL_H
#define LOAD3DMODEL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LOAD3DMODEL_LIBRARY)
#  define LOAD3DMODEL_EXPORT Q_DECL_EXPORT
#else
#  define LOAD3DMODEL_EXPORT Q_DECL_IMPORT
#endif

#define SingletonSelfConstruct(type)  			private:\
                                                type();\
                                                ~type();\
                                                type(type& instance) = delete;\
                                                type& operator=(const type& instance) = delete;\
                                                public:\
                                                static type& GetInstance()\
                                                {\
                                                    static type instance;\
                                                    return instance;\
                                                }

#endif // LOAD3DMODEL_GLOBAL_H
