#ifndef POPULUSSC_TEXTURE_CACHE_H
#define POPULUSSC_TEXTURE_CACHE_H

/******************************************************************************
**
**   File:        TextureCache.h
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

#include "pgl.h"
#include "Texture.h"

namespace psc
{

class StaticBitmap;
class DisplayManager;

class TextureCache
{
public:
    explicit TextureCache(const DisplayManager&);

    /**
     * Loads a texture from the given StaticBitmap
     * If the StaticBitmap is already loaded as a texture the loaded texture is returned instead
     * returns NULL on error
     */
    Texture* load(const StaticBitmap& bmp);

private:
    enum
    {
        MAX_TEXTURES = 40 // TODO: limits.h
    };
    const DisplayManager& m_displayManager;
    Texture m_textures[MAX_TEXTURES];
};

}

#endif // POPULUSSC_TEXTURE_CACHE_H
