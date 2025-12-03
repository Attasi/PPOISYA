# Файлы библиотеки Multiset
set(MULTISET_SOURCES
        Multiset.cpp
        Multiset.h
)

# Заголовочные файлы для включения в основной проект
set(MULTISET_HEADERS
        Multiset.h
)

# Сообщаем родительскому CMakeLists о наличии этой библиотеки
set(MULTISET_SOURCES ${MULTISET_SOURCES} PARENT_SCOPE)
set(MULTISET_HEADERS ${MULTISET_HEADERS} PARENT_SCOPE)