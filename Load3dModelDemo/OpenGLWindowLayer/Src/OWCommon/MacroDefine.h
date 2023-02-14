#pragma once


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
