/*****************************************************************************
 * FILE NAME    : JSONOut.c
 * DATE         : December 02 2020
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2020 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "JSONOut.h"
#include "MemoryManager.h"
#include "json.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/

/*****************************************************************************!
 * Local Data
 *****************************************************************************/

/*****************************************************************************!
 * Function : JSONOutCreate
 *****************************************************************************/
JSONOut*
JSONOutCreate
(string InTag, JSONOutType InType)
{
  JSONOut*                              jsonout;

  jsonout = (JSONOut*)GetMemory(sizeof(JSONOut));
  memset(jsonout, 0x00, sizeof(JSONOut));
  if ( InTag ) {
    jsonout->tag = StringCopy(InTag);
  }
  jsonout->type = InType;

  return jsonout;
}

/*****************************************************************************!
 * Function : JSONOutCreateInt
 *****************************************************************************/
JSONOut*
JSONOutCreateInt
(string InTag, uint32_t InInt)
{
  JSONOut*                              jsonout;

  jsonout = JSONOutCreate(InTag, JSONOutTypeInt);
  jsonout->valueInt = InInt;
  return jsonout;
}

/*****************************************************************************!
 * Function : JSONOutCreateLongLong
 *****************************************************************************/
JSONOut*
JSONOutCreateLongLong
(string InTag, uint64_t InLongLong)
{
  JSONOut*                              jsonout;

  jsonout = JSONOutCreate(InTag, JSONOutTypeLongLong);
  jsonout->valueLongLong = InLongLong;
  return jsonout;
}

/*****************************************************************************!
 * Function : JSONOutCreateString
 *****************************************************************************/
JSONOut*
JSONOutCreateString
(string InTag, string InString)
{
  JSONOut*                              jsonout;

  jsonout = JSONOutCreate(InTag, JSONOutTypeString);
  if ( InString ) {
    jsonout->valueString = StringCopy(InString);
  } else {
    jsonout->valueString = StringCopy("");
  }
  return jsonout;
  
}

/*****************************************************************************!
 * Function : JSONOutCreateBool
 *****************************************************************************/
JSONOut*
JSONOutCreateBool
(string InTag, int InBool)
{
  JSONOut*                              jsonout;

  jsonout = JSONOutCreate(InTag, JSONOutTypeBool);
  jsonout->valueBool = InBool;
  return jsonout;
}

/*****************************************************************************!
 * Function : JSONOutCreateFloat
 *****************************************************************************/
JSONOut*
JSONOutCreateFloat
(string InTag, double InFloat)
{
  JSONOut*                              jsonout;

  jsonout = JSONOutCreate(InTag, JSONOutTypeFloat);
  jsonout->valueFloat = InFloat;
  return jsonout;
}

/*****************************************************************************!
 * Function : JSONOutCreateObject
 *****************************************************************************/
JSONOut*
JSONOutCreateObject
(string InTag)
{
  JSONOut*                              jsonout;

  jsonout = JSONOutCreate(InTag, JSONOutTypeObject);

  jsonout->valueObject = JSONOutObjectCreate();
  return jsonout;
}

/*****************************************************************************!
 * Function : JSONOutCreateArray
 *****************************************************************************/
JSONOut*
JSONOutCreateArray
(string InTag)
{
  JSONOut*                              jsonout;

  jsonout = JSONOutCreate(InTag, JSONOutTypeArray);

  jsonout->valueArray = JSONOutArrayCreate();
  return jsonout;
}

/*****************************************************************************!
 * Function : JSONOutObjectAddObject
 *****************************************************************************/
void
JSONOutObjectAddObject
(JSONOut* InObject, JSONOut* InNewObject)
{
  if ( NULL == InObject || NULL == InNewObject ) {
    return;
  }
  if ( InObject->type != JSONOutTypeObject ) {
    return;
  }
  JSONOutObjectAppend(InObject->valueObject, InNewObject);
}

/*****************************************************************************!
 * Function : JSONOutObjectAddObjects
 *****************************************************************************/
void
JSONOutObjectAddObjects
(JSONOut* InObject, ...)
{
  JSONOut*                              object;
  va_list                               ap;
  
  if ( NULL == InObject ) {
    return;
  }
  if ( InObject->type != JSONOutTypeObject ) {
    return;
  }
  va_start(ap, InObject);
  object = va_arg(ap, JSONOut*);
  while (object) {
    JSONOutObjectAddObject(InObject, object);
    object = va_arg(ap, JSONOut*);
  }

  va_end(ap);
}

/*****************************************************************************!
 * Function : JSONOutArrayAddObject
 *****************************************************************************/
void
JSONOutArrayAddObject
(JSONOut* InArray, JSONOut* InNewObject)
{
  if ( NULL == InArray || NULL == InNewObject ) {
    return;
  }
  if ( InArray->type != JSONOutTypeArray ) {
    return;
  }
  JSONOutArrayAppend(InArray->valueArray, InNewObject);
}

/*****************************************************************************!
 * Function : JSONOutDestroy
 *****************************************************************************/
void
JSONOutDestroy
(JSONOut* InObject)
{
  if ( NULL == InObject ) {
    return;
  }

  if ( InObject->tag ) {
    FreeMemory(InObject->tag);
  }

  switch (InObject->type) {
    case JSONOutTypeNone : {
      break;
    }
      
    case JSONOutTypeInt : {
      break;
    }
      
    case JSONOutTypeLongLong : {
      break;
    }
      
    case JSONOutTypeFloat : {
      break;
    }
      
    case JSONOutTypeString : {
      FreeMemory(InObject->valueString);
      break;
    }
      
    case JSONOutTypeBool : {
      break;
    }
      
    case JSONOutTypeArray : {
      JSONOutArrayDestroy(InObject->valueArray);
      break;
    }
      
    case JSONOutTypeObject : {
      JSONOutObjectDestroy(InObject->valueObject);
      break;
    }      
  }
  FreeMemory(InObject);
}

/*****************************************************************************!
 * Function : JSONOutObjectCreate
 *****************************************************************************/
JSONOutObject*
JSONOutObjectCreate
(void)
{
  JSONOutObject*                        object;

  object = (JSONOutObject*)GetMemory(sizeof(JSONOutObject));
  memset(object, 0x00, sizeof(JSONOutObject));
  return object;
}

/*****************************************************************************!
 * Function : JSONOutObjectAppend
 *****************************************************************************/
void
JSONOutObjectAppend
(JSONOutObject* InObject, JSONOut* InNewObject)
{
  uint32_t                              i;
  JSONOut**                             objects;
  uint32_t                              n;
  if ( NULL == InObject || NULL == InNewObject ) {
    return;
  }

  n = InObject->count + 1;
  objects = (JSONOut**)GetMemory(sizeof(JSONOut*) * n);
  for ( i = 0; i < InObject->count ; i++ ) {
    objects[i] = InObject->objects[i];
  }
  if ( InObject->count > 0 ) {
    FreeMemory(InObject->objects);
  }
  objects[InObject->count] = InNewObject;
  
  InObject->objects = objects;
  InObject->count = n;
}

/*****************************************************************************!
 * Function : JSONOutObjectDestroy
 *****************************************************************************/
void
JSONOutObjectDestroy
(JSONOutObject* InObject)
{
  int                                   i;
  if ( NULL == InObject ) {
    return;
  }
  if ( InObject->count ) {
    for (i = 0; i < (int)InObject->count; i++) {
      JSONOutDestroy(InObject->objects[i]);
    }
    FreeMemory(InObject->objects);
  }
  FreeMemory(InObject);
}

/*****************************************************************************!
 * Function : JSONOutFromString
 *****************************************************************************/
JSONOut*
JSONOutFromString
(string InString)
{
  JSONOut*                              returnJSON;
  json_value*                           json;
  char                                  errorLine[json_error_max + 1];
  json_settings                         settings = {0, 0, NULL, NULL, NULL, 0};

  json = json_parse_ex(&settings, InString, (size_t)strlen(InString), errorLine);
  if ( NULL == json ) {
    fprintf(stderr, "%s\n", errorLine);
    return NULL;
  }

  returnJSON = JSONOutFromJSONValue(json, NULL);
  json_value_free(json);
  return returnJSON;
}
  
/*****************************************************************************!
 * Function : JSONOutToString
 *****************************************************************************/
string
JSONOutToString
(JSONOut* InObject, uint32_t InIndent, uint32_t InIndentChild)
{
  string                                s2;
  int                                   i;
  char                                  intString[32];
  char                                  floatString[16];
  string                                indentString;
  string                                s;
  if ( NULL == InObject ) {
    return NULL;
  }
  if ( InIndent > 0 ) {
    indentString = StringFill(' ', (int)InIndent);
  } else {
    indentString = StringCopy("");
  }

  s = StringCopy(indentString);
  if ( InObject->tag ) {
    s = StringConcatTo(s, "\"");
    s = StringConcatTo(s, InObject->tag);
    s = StringConcatTo(s, "\" : ");
  }

  switch (InObject->type) {
    case JSONOutTypeNone : {
      break;
    }
      
    case JSONOutTypeInt : {
      sprintf(intString, "%d", InObject->valueInt);
      s = StringConcatTo(s, intString);
      break;
    }

    case JSONOutTypeLongLong : {
      sprintf(intString, "%lld", (long long)InObject->valueLongLong);
      s = StringConcatTo(s, intString);
      break;
    }
      
    case JSONOutTypeFloat : {
      sprintf(floatString, "%f", InObject->valueFloat);
      s = StringConcatTo(s, floatString);
      break;
    }
      
    case JSONOutTypeString : {
      s = StringConcatTo(s, "\"");
      s = StringConcatTo(s, InObject->valueString);
      s = StringConcatTo(s, "\"");
      break;
    }
      
    case JSONOutTypeBool : {
      s = StringConcatTo(s, InObject->valueBool ? "true" : "false");
      break;
    }
      
    case JSONOutTypeArray : {
      s = StringConcatTo(s, "[\n");
      for ( i = 0 ; i < (int)InObject->valueArray->count ; i++ ) {
        s2 = JSONOutToString(InObject->valueArray->objects[i], InIndent + InIndentChild,  InIndentChild);
        // s = StringConcatTo(s, "{ ");
        s = StringConcatTo(s, s2);
        FreeMemory(s2);
        // s = StringConcatTo(s, " }");
        if ( i + 1 < (int)InObject->valueArray->count ) {
          s = StringConcatTo(s, ",");
        }
        s = StringConcatTo(s,"\n");
      }
      s = StringConcatTo(s, indentString);
      s = StringConcatTo(s, "]");
      break;
    }
      
    case JSONOutTypeObject : {
      s = StringConcatTo(s, "{\n");
      for ( i = 0 ; i < (int)InObject->valueObject->count ; i++ ) {
        s2 = JSONOutToString(InObject->valueObject->objects[i], InIndent + InIndentChild, InIndentChild);
        s = StringConcatTo(s, s2);
        FreeMemory(s2);
        if ( i + 1 < (int)InObject->valueObject->count ) {
          s = StringConcatTo(s, ",");
        }
        s = StringConcatTo(s,"\n");
      }
      s = StringConcatTo(s, indentString);
      s = StringConcatTo(s, "}");
      break;
    }
  }
  FreeMemory(indentString);
  return s;
}

/*****************************************************************************!
 * Function : JSONOutArrayCreate
 *****************************************************************************/
JSONOutArray*
JSONOutArrayCreate
(void)
{
  JSONOutArray*                        object;

  object = (JSONOutArray*)GetMemory(sizeof(JSONOutArray));
  memset(object, 0x00, sizeof(JSONOutArray));
  return object;
}

/*****************************************************************************!
 * Function : JSONOutArrayAppend
 *****************************************************************************/
void
JSONOutArrayAppend
(JSONOutArray* InArray, JSONOut* InNewArray)
{
  uint32_t                              i;
  JSONOut**                             objects;
  uint32_t                              n;
  if ( NULL == InArray || NULL == InNewArray ) {
    return;
  }

  n = InArray->count + 1;
  objects = (JSONOut**)GetMemory(sizeof(JSONOut*) * n);
  for ( i = 0; i < InArray->count ; i++ ) {
    objects[i] = InArray->objects[i];
  }
  if ( InArray->count > 0 ) {
    FreeMemory(InArray->objects);
  }
  objects[InArray->count] = InNewArray;
  
  InArray->objects = objects;
  InArray->count = n;
}

/*****************************************************************************!
 * Function : JSONOutArrayDestroy
 *****************************************************************************/
void
JSONOutArrayDestroy
(JSONOutArray* InArray)
{
  int                                   i;
  if ( NULL == InArray ) {
    return;
  }
  if ( InArray->count ) {
    for (i = 0; i < (int)InArray->count; i++) {
      JSONOutDestroy(InArray->objects[i]);
    }
    FreeMemory(InArray->objects);
  }
  FreeMemory(InArray);
}

/*****************************************************************************!
 * Function : JSONOutSetName
 *****************************************************************************/
void
JSONOutSetName
(JSONOut* InJSON, string InName)
{
  if ( NULL == InJSON || NULL == InName ) {
    return;
  }

  if ( InJSON->tag ) {
    FreeMemory(InJSON->tag);
  }

  InJSON->tag = StringCopy(InName);
}

/*****************************************************************************!
 * Function : JSONOutDump
 *****************************************************************************/
void
JSONOutDump
(JSONOut* InJSONOut, int InIndent)
{
  JSONOutDumpToFile(InJSONOut, InIndent, stdout);
}

/*****************************************************************************!
 * Function : JSONOutDumpFile
 *****************************************************************************/
void
JSONOutDumpFile
(JSONOut* InJSONOut, int InIndent, string InFilename)
{
  FILE* f = fopen(InFilename, "ab");
  if ( NULL == f ) {
    return;
  }
  JSONOutDumpToFile(InJSONOut, InIndent, f);
  fclose(f);
}

/*****************************************************************************!
 * Function : JSONOutDumpToFile
 *****************************************************************************/
void
JSONOutDumpToFile
(JSONOut* InJSONOut, int InIndent, FILE* InFile)
{
  int                                   i;
  string                                indentString;

  if ( InIndent > 0 ) {
    indentString = StringFill(' ', InIndent);
  } else {
    indentString = "";
  }

  fprintf(InFile, "%sJSONOut\n", indentString);
  fprintf(InFile, "%s    Tag : %s\n", indentString, InJSONOut->tag ? InJSONOut->tag : "NULL");
  fprintf(InFile, "%s   Type : %d (%s)\n", indentString, InJSONOut->type, JSONOutTypeToString(InJSONOut->type));
  switch (InJSONOut->type) {
    case JSONOutTypeInt : {
      fprintf(InFile, "%s  Value : %d\n", indentString, InJSONOut->valueInt);
      break;
    }
    case JSONOutTypeLongLong : {
      fprintf(InFile, "%s  Value : %lld\n", indentString, (long long)InJSONOut->valueLongLong);
      break;
    }
    case JSONOutTypeFloat : {
      fprintf(InFile, "%s  Value : %f\n", indentString, InJSONOut->valueFloat);
      break;
    }
    case JSONOutTypeString : {
      fprintf(InFile, "%s  Value : \"%s\"\n", indentString, InJSONOut->valueString);
      break;
    }
    case JSONOutTypeBool : {
      fprintf(InFile, "%s  Value : %s\n", indentString, InJSONOut->valueBool ? "true" : "false");
      break;
    }
    case JSONOutTypeArray : {
      for ( i = 0 ; i < (int)InJSONOut->valueArray->count; i++ ) {
        JSONOutDumpToFile(InJSONOut->valueArray->objects[i], InIndent + 2, InFile);
      }
      fprintf(InFile, "%s  Value : Array\n", indentString);
      break;
    }
    case JSONOutTypeObject : {
      for ( i = 0 ; i < (int)InJSONOut->valueObject->count; i++ ) {
        JSONOutDumpToFile(InJSONOut->valueObject->objects[i], InIndent + 2, InFile);
      }
      fprintf(InFile, "%s  Value : Object\n", indentString);
      break;
    }
    default :
      break;
  }
}

/*****************************************************************************!
 * Function : JSONOutFromJSONValue
 *****************************************************************************/
JSONOut*
JSONOutFromJSONValue
(json_value* InJSON, string InTag)
{
  int                                   i;
  JSONOut*                              returnJSON;

  if ( InJSON == NULL ) {
    return NULL;
  }

  switch (InJSON->type) {
    case json_object : {
      returnJSON = JSONOutCreateObject(InTag);
      for ( i = 0 ; i < (int)InJSON->u.object.length ; i++ ) {
        json_object_entry*              value;
        JSONOut*                        j;
        value = &(InJSON->u.object.values[i]);
        j = JSONOutFromJSONValue(value->value, value->name);
        JSONOutObjectAddObject(returnJSON, j);
      }
      return returnJSON;
    }
    case json_array : {
      returnJSON = JSONOutCreateArray(InTag);
      for ( i = 0 ; i < (int)InJSON->u.array.length ; i++ ) {
        json_value*                     value;
        JSONOut*                        j;
        value = InJSON->u.array.values[i];
        j = JSONOutFromJSONValue(value, NULL);
        JSONOutArrayAddObject(returnJSON, j);
      }
      return returnJSON;      
    }
    case json_integer : {
      return JSONOutCreateInt(InTag, (unsigned int)InJSON->u.integer);
    }
    case json_double : {
      return JSONOutCreateFloat(InTag, InJSON->u.dbl);
    }
    case json_string : {
      return JSONOutCreateString(InTag, InJSON->u.string.ptr);      
    }
    case json_boolean : {
      return JSONOutCreateBool(InTag, InJSON->u.boolean);      
    }
    default : {
      break;
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : JSONOutFind
 *****************************************************************************/
JSONOut*
JSONOutFind
(JSONOut* InJSONOut, string InTag)
{
  int                                   i;
  JSONOut*                              obj;
  if ( NULL == InJSONOut || NULL == InTag ) {
    return NULL;
  }

  if ( InJSONOut->type != JSONOutTypeObject ) {
    return NULL;
  }
  for ( i = 0 ; i < (int)InJSONOut->valueObject->count; i++ ) {
    obj = InJSONOut->valueObject->objects[i];
    if ( StringEqual(obj->tag, InTag) ) {
      return obj;
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : JSONOutTypeToString
 *****************************************************************************/
string
JSONOutTypeToString
(JSONOutType InType)
{
  switch (InType) {
    case JSONOutTypeNone : {
      return "None";
    }
      
    case JSONOutTypeInt : {
      return "Int";
    }
      
    case JSONOutTypeLongLong : {
      return "long long";
    }
      
    case JSONOutTypeFloat : {
      return "float";
    }
      
    case JSONOutTypeString : {
      return "string";
    }
      
    case JSONOutTypeBool : {
      return "bool";
    }
      
    case JSONOutTypeArray : {
      return "array";
    }
      
    case JSONOutTypeObject : {
      return "object";
    }

    default :
      break;
  }
  return "Unknown";
}

/*****************************************************************************!
 * Function : JSONOutFindString
 *****************************************************************************/
string
JSONOutFindString
(JSONOut* InJSON, string InTag)
{
  JSONOut*                              j;
  if ( NULL == InJSON || NULL == InTag ) {
    return NULL;
  }

  j = JSONOutFind(InJSON, InTag);
  if ( NULL == j ) {
    return NULL;
  }

  if ( j->type != JSONOutTypeString ) {
    return NULL;
  }

  return StringCopy(j->valueString);
}


/*****************************************************************************!
 * Function : JSONOutGetBool
 *****************************************************************************/
int
JSONOutGetBool
(JSONOut* InJSON, string InName)
{
  JSONOut*                              j;
  int                                   i;
  if ( NULL == InJSON || NULL == InName ) {
    return -1;
  }

  if ( InJSON->type  != JSONOutTypeObject ) {
    return -1;
  }

  for ( i = 0 ; i < (int)InJSON->valueObject->count ; i++ ) {
    j = InJSON->valueObject->objects[i];

    if ( ! StringEqual(j->tag, InName ) ) {
      continue;
    }
    if ( j->type == JSONOutTypeBool ) {
      return j->valueBool;
    }

    if ( j->type == JSONOutTypeString ) {
      if ( StringEqualNoCase(j->valueString, "true") ) {
        return 1;
      }
      if ( StringEqualNoCase(j->valueString, "false") ) {
        return 0;
      }
    }
  }
  return -1;
}

/*****************************************************************************!
 * Function : JSONOutToBool
 *****************************************************************************/
int
JSONOutToBool
(JSONOut* InJSON)
{
  if ( InJSON == NULL ) {
    return -1;
  }
  
  if ( InJSON->type == JSONOutTypeBool ) {
    return InJSON->valueBool;
  }

  if ( InJSON->type != JSONOutTypeString ) {
    return -1;
  }

  if ( StringEqualNoCase(InJSON->valueString, "true" ) ){
    return 1;
  }

  if ( StringEqualNoCase(InJSON->valueString, "false" ) ) {
    return 0;
  }

  return -1;
}
  
/*****************************************************************************!
 * Function : JSONArrayFromString
 *****************************************************************************/
JSONOut*
JSONArrayFromString
(string InString)
{
  json_value*                           json;
  JSONOut*                              returnJSON;
  char                                  errorLine[json_error_max + 1];
  json_settings                         settings = {0, 0, NULL, NULL, NULL, 0};
  
  if ( InString == NULL ) {
    return NULL;
  }

  json = json_parse_ex(&settings, InString, (size_t)strlen(InString), errorLine);
  if ( NULL == json ) {
    fprintf(stderr, "%s\n", errorLine);
    return NULL;
  }
  
  returnJSON = JSONOutFromJSONValue(json, NULL);
  json_value_free(json);
  return returnJSON;
}

/*****************************************************************************!
 * Function : JSONOutObjectContainsTag
 *****************************************************************************/
bool
JSONOutObjectContainsTag
(JSONOut* InJSON, string InTag)
{
  JSONOut*                              j;

  j = JSONOutFind(InJSON, InTag);
  if ( NULL == j ) {
    return false;
  }
  return true;
}
