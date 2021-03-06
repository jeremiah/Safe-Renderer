#ifndef INPUTSTREAMCORRUPTER_H
#define INPUTSTREAMCORRUPTER_H

/******************************************************************************
**
**   File:        InputStreamCorrupter.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include <stdint.h>

#include "PSCError.h"


/**
 * Class is needed to corrupt internal state of InputStream object.
 * It should have exactly the same sequence of fields and field types as they are
 * in InputStream class.
 *
 * Example of usage:
 * psc::InputStream stream(...);
 * InputStreamCorrupter* corrupter = reinterpret_cast<InputStreamCorrupter*>(&stream);
 * corrupter->setPos(someNewPosition);
 * EXPECT_TRUE(stream.isWorkingFine());
 */
class InputStreamCorrupter
{
public:
    InputStreamCorrupter(const void* buffer, uint32_t bufferSize);

    void setBufferSize(uint32_t size);
    void setPos(uint32_t pos);
    void setError(PSCError error);

private:
    const uint8_t* m_buffer;
    uint32_t m_bufferSize;
    uint32_t m_pos;
    PSCError m_error;
};

inline void InputStreamCorrupter::setBufferSize(uint32_t size)
{
    m_bufferSize = size;
}

inline void InputStreamCorrupter::setPos(uint32_t pos)
{
    m_pos = pos;
}

inline void InputStreamCorrupter::setError(PSCError error)
{
    m_error = error;
}

#endif // INPUTSTREAMCORRUPTER_H
