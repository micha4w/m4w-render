#include "JSON.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

namespace m4w {
    JSONType JSONObject::Type() { return JSONType::Object; }

    JSONObject::JSONObject () {
        m_Type = JSONType::Object;
    }

    m4w::Pointer<JSONObject> JSONObject::GetObject (std::string key) {
        if ( !this->Contains(key) ) {
            std::cout << "[ERROR] Field " << key << " not inside Object!\n";
            return nullptr;
        }

        m4w::Pointer<JSONThing> thing = m_Values[key];

        if ( thing->m_Type == JSONObject::Type() ) return (m4w::Pointer<JSONObject>) thing;
        
        std::cout << "[ERROR] Field " << key << " not of Type Object!\n";
        return nullptr;
    }

    Pointer<JSONArray> JSONObject::GetArray (std::string key) {
        if ( !this->Contains(key) ) {
            std::cout << "[ERROR] Field " << key << " not inside Object!\n";
            return nullptr;
        }

    Pointer<JSONThing> thing = m_Values[key];

        if ( thing->m_Type == JSONArray::Type() ) return (Pointer<JSONArray>) thing;
        
        std::cout << "[ERROR] Field " << key << " not of Type Array!\n";
        return nullptr;
    }

    Pointer<JSONString> JSONObject::GetString (std::string key) {
        if ( !this->Contains(key) ) {
            std::cout << "[ERROR] Field " << key << " not inside Object!\n";
            return nullptr;
        }

        Pointer<JSONThing> thing = m_Values[key];

        if ( thing->m_Type == JSONString::Type() ) return (Pointer<JSONString>) thing;
        
        std::cout << "[ERROR] Field " << key << " not of Type String!\n";
        return nullptr;
    }

    Pointer<JSONNumber> JSONObject::GetNumber (std::string key) {
        if ( !this->Contains(key) ) {
            std::cout << "[ERROR] Field " << key << " not inside Object!\n";
            return nullptr;
        }

    Pointer<JSONThing> thing = m_Values[key];

        if ( thing->m_Type == JSONNumber::Type() ) return (Pointer<JSONNumber>) thing;
        
        std::cout << "[ERROR] Field " << key << " not of Type Number!\n";
        return nullptr;
    }

    Pointer<JSONBoolean> JSONObject::GetBoolean (std::string key) {
        if ( !this->Contains(key) ) {
            std::cout << "[ERROR] Field " << key << " not inside Object!\n";
            return nullptr;
        }

        Pointer<JSONThing> thing = m_Values[key];

        if ( thing->m_Type == JSONBoolean::Type() ) return (Pointer<JSONBoolean>) thing;
        
        std::cout << "[ERROR] Field " << key << " not of Type Boolean!\n";
        return nullptr;
    }

    bool JSONObject::Contains (std::string key) {
        return m_Values.find(key) != m_Values.end();
    }

    JSONType JSONArray::Type() { return JSONType::Array; }

    JSONArray::JSONArray () {
        m_Type = JSONType::Array;
    }

    JSONType JSONArray::ContentType() {
        if ( m_Values.size() == 0 ) return JSONType::Null;

        return m_Values[0]->m_Type;
    }
        
    Pointer<JSONObject> JSONArray::GetObject (unsigned int pos) {
        if ( pos >= m_Values.size() ) { std::cout << "[Warning] Array isnt big enough for index '" << pos << "'!\n"; return nullptr; }
        return (Pointer<JSONObject>) m_Values[pos];
    }

    Pointer<JSONArray> JSONArray::GetArray (unsigned int pos) {
        if ( pos >= m_Values.size() ) { std::cout << "[Warning] Array isnt big enough for index '" << pos << "'!\n"; return nullptr; }
        return (Pointer<JSONArray>) m_Values[pos];
    }

    Pointer<JSONString> JSONArray::GetString (unsigned int pos) {
        if ( pos >= m_Values.size() ) { std::cout << "[Warning] Array isnt big enough for index '" << pos << "'!\n"; return nullptr; }
        return (Pointer<JSONString>) m_Values[pos];
    }

    Pointer<JSONNumber> JSONArray::GetNumber (unsigned int pos) {
        if ( pos >= m_Values.size() ) { std::cout << "[Warning] Array isnt big enough for index '" << pos << "'!\n"; return nullptr; }
        return (Pointer<JSONNumber>) m_Values[pos];
    }

    Pointer<JSONBoolean> JSONArray::GetBoolean (unsigned int pos) {
        if ( pos >= m_Values.size() ) { std::cout << "[Warning] Array isnt big enough for index '" << pos << "'!\n"; return nullptr; }
        return (Pointer<JSONBoolean>) m_Values[pos];
    }


    JSONType JSONString::Type() { return JSONType::String; }

    JSONString::JSONString () {
        m_Type = JSONType::String;
    }


    JSONType JSONBoolean::Type() { return JSONType::Boolean; }

    JSONBoolean::JSONBoolean () {
        m_Type = JSONType::Boolean;
    }


    JSONType JSONNumber::Type() { return JSONType::Number; }

    JSONNumber::JSONNumber () {
        m_Type = JSONType::Number;
    }


    JSONType JSONNull::Type() { return JSONType::Null; }

    JSONNull::JSONNull () {
        m_Type = JSONType::Null;
    }

    Pointer<JSONThing> Read(std::ifstream& input) {

        char next;
        while ( !input.eof() ) {

            input.get(next);

            if ( next == ' ' ) continue;
            if ( next == '\n' ) continue;

            else if ( next == '"' ) {
                // Start reading JSONString
                Pointer<JSONString> string = new JSONString();

                input.get(next);
                while ( next != '"' ) {
                    string->m_Value += next;
                    input.get(next);
                }

                //std::cout << string->m_Value << "\n";

                return string;

            } else if ( next == '{' ) {
                // Start reading JSONObject
                Pointer<JSONObject> object = new JSONObject();

                while ( true ) {
                    Pointer<JSONString> name = (Pointer<JSONString>) Read(input);
                    if ( !name ) break;

                    Pointer<JSONThing> thing = Read(input);
                    object->m_Values[name->m_Value] = thing;
                }

                return object;

            } else if ( next == '}' ) {
                // End reading JSONobject
                return nullptr;

            } else if ( next == '[' ) {
                // Start reading JSONArray
                Pointer<JSONArray> array = new JSONArray();
                
                while ( Pointer<JSONThing> part = Read(input) ) {
                    array->m_Values.push_back(part);
                }

                return array;

            } else if ( next == ']' ) {
                // End reading JSONArray
                return nullptr;

            } else if ( std::isalpha(next) ) {
                // Check if JSONBoolean or JSONNull
                
                std::string temp;
                
                do {
                    temp += next;
                    input.get(next);
                } while ( std::isalpha(next) );

                if ( temp.compare("true") == 0 ) {
                    Pointer<JSONBoolean> boolean = new JSONBoolean();
                    boolean->m_Value = true;
                    return boolean;
                    
                } else if ( temp.compare("false") == 0 ) {
                    Pointer<JSONBoolean> boolean = new JSONBoolean();
                    boolean->m_Value = false;
                    return boolean;
                
                } else {
                    return new JSONNull();
                }

            } else if ( std::isdigit(next) || next == '.' || next == '-' || next == '+' ) {
                // Start reading JSONNumber
                std::string temp;
                do {
                    temp += next;
                    input.get(next);
                } while ( std::isdigit(next) || next == '.' || next == 'e' || next == 'E' || next == '-' || next == '+' );

                Pointer<JSONNumber> number = new JSONNumber();
                number->m_Value = std::stof( temp );
                return number;
            }
        }

        return nullptr;
    }

    Pointer<JSONObject> ReadFile(const char* path) {
        std::ifstream input(path);
        return (Pointer<JSONObject>) Read(input);    
    }
}