#ifndef S84_CTCODE_TRANSPILER_CTCODE_H
#define S84_CTCODE_TRANSPILER_CTCODE_H

#include "S84.CTCode.System.ctcode.hpp"
#include "S84.CTCode.dbnf.ctcode.hpp"

#include <cstring>
#include <list>
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

#ifndef CTCODE_COMMON_FUNCTIONS_VERSION_1
#define CTCODE_COMMON_FUNCTIONS_VERSION_1
template<typename T>
class OmniPointer
{
public:
    OmniPointer() { value_raw = NULL; }
    OmniPointer(T* value) { value_raw = value; }
    template<typename U>
    OmniPointer(U* value) { value_raw = value; }
    OmniPointer(std::shared_ptr<T> value) { value_raw = NULL; value_shared = value; }
    template<typename U>
    OmniPointer(std::shared_ptr<U> value) { value_raw = NULL; value_shared = value; }
    template<typename U>
    OmniPointer(OmniPointer<U> value) { value_raw = value.value_raw; value_shared = value.value_shared; }

    operator bool()
    {
        if (value_raw) return true;
        return value_shared.get() != NULL;
    }
    T& operator*()
    {
        if (value_raw) return *value_raw;
        return *value_shared;
    }
    T* operator->()
    {
        if (value_raw) return value_raw;
        return value_shared.get();
    }
    T* raw()
    {
        if (value_raw) return value_raw;
        return value_shared.get();
    }

    T* value_raw;
    std::shared_ptr<T> value_shared;
};

template<typename T>
inline std::vector<T*> UnwrapOmniList(std::vector<OmniPointer<T>> input) {
	std::vector<T*> result;
	for (typename std::vector<OmniPointer<T>>::iterator index = input.begin();index != input.end();index++) {
		result.push_back(index->raw());
	}
	return result;
};
template<typename T>
inline void ClearList(std::vector<T>& input) { input.clear(); };
template<typename T>
inline int Size(const std::vector<T>& input) { return input.size(); };
template<typename T>
inline T Element(const std::vector<T>& input, int element) { return input.at(element); };
template<typename T>
inline void Append(std::vector<T>& input, T element) { input.push_back(element); };
template<typename T>
inline void ClearMap(std::unordered_map<std::string, T>& input) { input.clear(); };
template<typename T>
inline void SetKV(std::unordered_map<std::string, T>& input, const std::string& key, T element)
{
    input.erase(key);
    input.insert(std::pair<std::string, T>(key, element));
}
template<typename T>
inline std::vector<std::string> Keys(const std::unordered_map<std::string, T>& input)
{
    std::vector<std::string> result;
    for(typename std::unordered_map<std::string, T>::const_iterator index = input.begin();index != input.end();index++) {
        result.push_back(index->first);
    }
    return result;
}
template<typename T>
inline bool HasKV(const std::unordered_map<std::string, T>& input, const std::string& key)
{
    typename std::unordered_map<std::string, T>::const_iterator beginning = input.find(key);
    return beginning != input.end();
}
template<typename T>
inline T GetKV(const std::unordered_map<std::string, T>& input, const std::string& key) { return input.at(key); }
inline int Length(const std::string& input) { return (int)input.length(); };
inline std::string At(const std::string& input, int index) { return input.substr(index, 1); };
inline int IntAt(const std::string& input, int index) { return (input.at(index) + 256) % 256; };
inline std::string Concat(const std::string& left, const std::string& right) { return left + right; };
#endif

namespace s84 {
namespace ctcode {
namespace transpiler {
namespace ctcode {

class OutputStream;
class Transpiler;

class OutputStream {
public:
    virtual void WriteLine(std::string line) = 0;
};

class Transpiler {
public:
    virtual int Transpile(OmniPointer<s84::ctcode::system::ctcode::System> system, OmniPointer<s84::ctcode::dbnf::ctcode::CTCodeFile> ct_code_file, std::string base_name) = 0;
};

};
};
};
};

#endif
