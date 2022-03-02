#pragma once

#include <vector>
#include <unordered_map>

#include "Pointer.h"

namespace m4w {
    enum JSONType {
        Object, Array, String, Number, Boolean, Null
    };

    struct JSONThing {
        JSONType m_Type;
    };

    struct JSONObject : JSONThing {
        static JSONType Type();
        std::unordered_map<std::string, m4w::Pointer<JSONThing>> m_Values;
        JSONObject ();

        operator std::unordered_map<std::string, m4w::Pointer<JSONThing>>() const { return m_Values; }

        m4w::Pointer<struct JSONObject> GetObject (std::string key);
        m4w::Pointer<struct JSONArray> GetArray (std::string key);
        m4w::Pointer<struct JSONString> GetString (std::string key);
        m4w::Pointer<struct JSONNumber> GetNumber (std::string key);
        m4w::Pointer<struct JSONBoolean> GetBoolean (std::string key);

        bool Contains (std::string key);
    };

    struct JSONArray : JSONThing {
        static JSONType Type();
        std::vector<m4w::Pointer<JSONThing>> m_Values;
        JSONArray ();

        JSONType ContentType();
        operator std::vector<m4w::Pointer<JSONThing>>() const { return m_Values; }

        m4w::Pointer<struct JSONObject> GetObject (unsigned int pos);
        m4w::Pointer<struct JSONArray> GetArray (unsigned int pos);
        m4w::Pointer<struct JSONString> GetString (unsigned int pos);
        m4w::Pointer<struct JSONNumber> GetNumber (unsigned int pos);
        m4w::Pointer<struct JSONBoolean> GetBoolean (unsigned int pos);
    };

    struct JSONString : JSONThing {
        static JSONType Type();
        std::string m_Value;
        JSONString ();

        operator std::string() const { return m_Value; }
        //operator const char*() const { return m_Value.c_str(); }
    };

    struct JSONBoolean : JSONThing {
        static JSONType Type();
        bool m_Value;
        JSONBoolean ();

        operator bool() const { return m_Value; }
    };

    struct JSONNumber : JSONThing {
        static JSONType Type();
        float m_Value;
        JSONNumber ();

        operator float() const { return m_Value; }
        operator int() const { return (int) m_Value; }
        operator unsigned int() const { return (unsigned int) m_Value; }
        operator long() const { return (long) m_Value; }
    };

    struct JSONNull : JSONThing {
        static JSONType Type();
        JSONNull ();
    };

    Pointer<JSONThing> Read(std::ifstream& input);

    Pointer<JSONObject> ReadFile(const char* path);
}