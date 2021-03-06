#ifndef POPULUSSC_BITMAPFIELD_H
#define POPULUSSC_BITMAPFIELD_H

/******************************************************************************
**
**   File:        BitmapField.h
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

#include "Field.h"

#include <BoolExpression.h>
#include <BitmapExpression.h>

namespace psc
{

struct StaticBitmapFieldType;
struct ExpressionTermType;
class Database;
class DataContext;
class WidgetPool;

/**
 * Class provides functionality to draw Bitmap on some canvas.
 *
 * @reqid SW_ENG_076, SW_ENG_077
 */
class BitmapField P_FINAL : public Field
{
public:
    /**
     * Method creates a @c BitmapField object with given @c widgetPool according
     * to configuration @c ddh.
     *
     * @param[in]  widgetPool pool which provides allocation an @c BitmapField object.
     * @param[in]  db         object provides work with database.
     * @param[in]  pDdh       @c psc::StaticBitmapFieldType ddh configuration.
     * @param[in]  pContext   data context, which shall be used for evaluation.
     * @param[out] error      error state which is set by @c widgetPool.
     *
     * @return pointer to @c BitmapField object if initialization of object was successful,
     *         @c NULL otherwise.
     */
    static BitmapField* create(WidgetPool& widgetPool,
                               const Database& db,
                               const StaticBitmapFieldType* pDdh,
                               DataContext* pContext,
                               PSCErrorCollector& error);

private:
    /**
     * Create an object.
     *
     * @param[in] db   object provides work with database.
     * @param[in] pDdh @c psc::StaticBitmapFieldType ddh configuration.
     */
    BitmapField(const Database& db, const StaticBitmapFieldType* const pDdh);

    /**
     * Method initialize object.
     *
     * @param[in]  pContext data context, which shall be used for evaluation.
     * @param[out] error    error state will be equal to @c PSC_NO_ERROR if
     *                      operation succeeded, other @c PSCError values otherwise.
     *
     * @return @c true if object initialization succeeded, @c false otherwise.
     */
    bool setup(DataContext* pContext, PSCErrorCollector& error);

    /**
     * Method updates internal variables (evaluates value of bitmap ID).
     * If new value differs from the older one, the invalidated flag
     * will be risen (see @c psc::Widget::invalidate method).
     *
     * @param[in] monotonicTimeMs current monotonic system time in milliseconds.
     */
    virtual void onUpdate(const U32 monotonicTimeMs) P_OVERRIDE;

    /**
     * Method draws itself on @c canvas if visible flag (see @c psc::Widget::isVisible)
     * was risen up.
     *
     * @param[in] canvas canvas to draw widget.
     * @param[in] area area in absolute coordinates.
     */
    virtual void onDraw(Canvas& canvas, const Area& area) P_OVERRIDE;

    /**
     * Method does nothing. It is a stub method
     *
     * @return @c true.
     */
    virtual bool onVerify(Canvas&, const Area&) P_OVERRIDE;

    /**
     * Method returns type of the widget.
     *
     * @return @c WIDGET_TYPE_BITMAP_FIELD value.
     */
    virtual Widget::WidgetType getType() const P_OVERRIDE;

    bool setupVisibilityExpr(DataContext* pContext);
    bool setupBitmapExr(DataContext* pContext);

    const StaticBitmapFieldType* m_pDdh;
    const Database& m_db;
    BoolExpression m_visibilityExpr;
    BitmapExpression m_bitmapExpr;
    BitmapId m_bitmapId;
};

inline Widget::WidgetType BitmapField::getType() const
{
    return WIDGET_TYPE_BITMAP_FIELD;
}

} // namespace psc

#endif // POPULUSSC_BITMAPFIELD_H
