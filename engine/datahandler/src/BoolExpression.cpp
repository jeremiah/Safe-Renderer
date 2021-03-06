/******************************************************************************
**
**   File:        BoolExpression.cpp
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

#include <BoolExpression.h>

#include <Assertion.h>

namespace psc
{

BoolExpression::BoolExpression()
    : m_pTerm(NULL)
    , m_pContext(NULL)
{
}

BoolExpression::~BoolExpression()
{
    dispose();
}

void BoolExpression::setup(const ExpressionTermType* pTerm, DataContext* pContext)
{
    dispose();

    ASSERT(NULL != pTerm);

    m_pTerm = pTerm;
    m_pContext = pContext;
    Expression::subscribe(pTerm, m_pContext, NULL);
}

void BoolExpression::dispose()
{
    if (m_pTerm)
    {
        Expression::unsubscribe(m_pTerm, m_pContext, NULL);
        m_pTerm = NULL;
    }
}

DataStatus BoolExpression::getValue(bool& value) const
{
    DataStatus status = getBool(m_pTerm, m_pContext, m_value);

    if (DataStatus::VALID == status)
    {
        value = m_value;
    }

    return status;
}

void BoolExpression::update()
{
}

} // namespace psc
