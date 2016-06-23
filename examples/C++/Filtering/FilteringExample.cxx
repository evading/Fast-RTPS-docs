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

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace { char dummy; }
#endif

#include "FilteringExample.h"

#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

FilteringExample::FilteringExample()
{
    m_sampleNumber = 0;
}

FilteringExample::~FilteringExample()
{
}

FilteringExample::FilteringExample(const FilteringExample &x)
{
    m_sampleNumber = x.m_sampleNumber;
}

FilteringExample::FilteringExample(FilteringExample &&x)
{
    m_sampleNumber = x.m_sampleNumber;
}

FilteringExample& FilteringExample::operator=(const FilteringExample &x)
{
    m_sampleNumber = x.m_sampleNumber;
    
    return *this;
}

FilteringExample& FilteringExample::operator=(FilteringExample &&x)
{
    m_sampleNumber = x.m_sampleNumber;
    
    return *this;
}

size_t FilteringExample::getMaxCdrSerializedSize(size_t current_alignment)
{
    size_t initial_alignment = current_alignment;
            
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    return current_alignment - initial_alignment;
}

void FilteringExample::serialize(eprosima::fastcdr::Cdr &scdr) const
{
    scdr << m_sampleNumber;

}

void FilteringExample::deserialize(eprosima::fastcdr::Cdr &dcdr)
{
    dcdr >> m_sampleNumber;
}

size_t FilteringExample::getKeyMaxCdrSerializedSize(size_t current_alignment)
{
	size_t current_align = current_alignment;
            

    return current_align;
}

bool FilteringExample::isKeyDefined()
{
    return false;
}

void FilteringExample::serializeKey(eprosima::fastcdr::Cdr &scdr) const
{
	 
}
