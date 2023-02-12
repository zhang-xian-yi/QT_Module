#ifndef OPENGLWINDOWUI_GLOBAL_H
#define OPENGLWINDOWUI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(OPENGLWINDOWUI_LIBRARY)
#  define OPENGLWINDOWUI_EXPORT Q_DECL_EXPORT
#else
#  define OPENGLWINDOWUI_EXPORT Q_DECL_IMPORT
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

#endif // OPENGLWINDOWUI_GLOBAL_H
