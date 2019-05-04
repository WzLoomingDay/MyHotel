#ifndef GETSETMETHOD_H
#define GETSETMETHOD_H

#define PropertyBuilderByName(type,name)\
    inline void set##name(const type &v)\
    {\
        name = v;\
    }\
    inline type& get##name()\
    {\
        return name;\
    }\

#endif // GETSETMETHOD_H
