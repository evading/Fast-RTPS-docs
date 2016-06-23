// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*************************************************************************
 * @file Data1mbTypes.cpp
 * This header file contains the implementation of the serialization functions.
 *
 * This file was generated by the tool fastcdrgen.
 */


#include <fastcdr/FastBuffer.h>
#include <fastcdr/Cdr.h>

#include "Data1mbType.h"

Data1mbType::Data1mbType() {
	setName("Data1mb");
	m_typeSize = (uint32_t)Data1mb::getMaxCdrSerializedSize();
	m_isGetKeyDefined = Data1mb::isKeyDefined();
	m_keyBuffer = (unsigned char*)malloc(Data1mb::getKeyMaxCdrSerializedSize()>16 ? Data1mb::getKeyMaxCdrSerializedSize() : 16);
}

Data1mbType::~Data1mbType() {
	if(m_keyBuffer!=nullptr)
		free(m_keyBuffer);
}

bool Data1mbType::serialize(void *data, SerializedPayload_t *payload) {
	Data1mb *p_type = (Data1mb*) data;
	eprosima::fastcdr::FastBuffer fastbuffer((char*) payload->data, payload->max_size); // Object that manages the raw buffer.
	eprosima::fastcdr::Cdr ser(fastbuffer); 	// Object that serializes the data.
    payload->encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;
	p_type->serialize(ser); 	// Serialize the object:
    payload->length = (uint32_t)ser.getSerializedDataLength(); 	//Get the serialized length
	return true;
}

bool Data1mbType::deserialize(SerializedPayload_t* payload, void* data) {
	Data1mb* p_type = (Data1mb*) data; 	//Convert DATA to pointer of your type
	eprosima::fastcdr::FastBuffer fastbuffer((char*)payload->data, payload->length); 	// Object that manages the raw buffer.
	eprosima::fastcdr::Cdr deser(fastbuffer, payload->encapsulation == CDR_BE ? eprosima::fastcdr::Cdr::BIG_ENDIANNESS : eprosima::fastcdr::Cdr::LITTLE_ENDIANNESS); 	// Object that deserializes the data.
	p_type->deserialize(deser);	//Deserialize the object:
	return true;
}

void* Data1mbType::createData() {
	return (void*)new Data1mb();
}

void Data1mbType::deleteData(void* data) {
	delete((Data1mb*)data);
}

bool Data1mbType::getKey(void *data, InstanceHandle_t* handle) {
	if(!m_isGetKeyDefined)
		return false;
	Data1mb* p_type = (Data1mb*) data;
	eprosima::fastcdr::FastBuffer fastbuffer((char*)m_keyBuffer,Data1mb::getKeyMaxCdrSerializedSize()); 	// Object that manages the raw buffer.
	eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS); 	// Object that serializes the data.
	p_type->serializeKey(ser);
	if(Data1mb::getKeyMaxCdrSerializedSize()>16)	{
		m_md5.init();
		m_md5.update(m_keyBuffer,(unsigned int)ser.getSerializedDataLength());
		m_md5.finalize();
		for(uint8_t i = 0;i<16;++i)    	{
        	handle->value[i] = m_md5.digest[i];
    	}
    }
    else    {
    	for(uint8_t i = 0;i<16;++i)    	{
        	handle->value[i] = m_keyBuffer[i];
    	}
    }
	return true;
}

