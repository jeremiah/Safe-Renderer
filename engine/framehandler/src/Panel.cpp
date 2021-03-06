/******************************************************************************
**
**   File:        Panel.cpp
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

#include "Panel.h"
#include "WidgetPool.h"

#include <Assertion.h>

#include <DDHType.h>
#include <PanelType.h>
#include <FieldsType.h>

#include <new>

namespace psc
{

Panel::Panel(const PanelType* pDdh)
    : Widget()
    , m_pDdh(pDdh)
{
}

bool Panel::setup(WidgetPool& widgetPool,
                  const Database& db,
                  DataContext* pContext,
                  PSCErrorCollector& error)
{
    bool success = setArea(m_pDdh->GetArea()) && setupVisibilityExpr(pContext);

    if (success)
    {
        const FieldsType* pFields = m_pDdh->GetFields();
        if (NULL != pFields)
        {
            const U16 numFields = pFields->GetFieldCount();
            for (U16 i = 0U; i < numFields; ++i)
            {
                const FieldType* pFieldType = pFields->GetField(i);
                Field* pField = Field::create(widgetPool, db, pFieldType, pContext, error);
                if (NULL == pField || !addChild(pField))
                {
                    success = false;
                    break;
                }
            }
        }
    }
    else
    {
        error = PSC_DB_INCONSISTENT;
    }

    return success;
}

Panel* Panel::create(WidgetPool& widgetPool,
                     const Database& db,
                     const PanelType* pDdhPanel,
                     DataContext* pContext,
                     PSCErrorCollector& error)
{

    ASSERT(NULL != pDdhPanel);

    PSCError tmpError = PSC_NO_ERROR;
    void* pRawMemory = widgetPool.panelPool().allocate(tmpError);
    error = tmpError;

    Panel* pPanel = new(pRawMemory)Panel(pDdhPanel);
    if (NULL != pPanel)
    {
        if (!pPanel->setup(widgetPool, db, pContext, error))
        {
            pPanel->~Panel();
            error = widgetPool.panelPool().deallocate(pRawMemory);
            pPanel = NULL;
        }
    }

    return pPanel;
}

bool Panel::setupVisibilityExpr(DataContext* pContext)
{
    bool res = false;
    const ExpressionTermType* pType = m_pDdh->GetVisible();
    if (NULL != pType)
    {
        m_visibilityExpr.setup(pType, pContext);
        setVisibilityExpression(&m_visibilityExpr);
        res = true;
    }
    return res;
}

void Panel::onUpdate(const U32 /* monotonicTimeMs */)
{}

void Panel::onDraw(Canvas& /* canvas */, const Area& /* area */)
{}

bool Panel::onVerify(Canvas&, const Area&)
{
    return true;
}

} // namespace psc
