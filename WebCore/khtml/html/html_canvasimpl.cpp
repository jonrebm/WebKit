/*
 * Copyright (C) 2004 Apple Computer, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "config.h"
#include "html/html_canvasimpl.h"
#include "html/html_documentimpl.h"

#include <kdebug.h>

#include "rendering/render_canvasimage.h"
#include "rendering/render_flow.h"
#include "css/cssstyleselector.h"
#include "cssproperties.h"
#include "cssvalues.h"
#include "css/csshelper.h"
#include "xml/dom2_eventsimpl.h"

#include <qstring.h>
#include <qpoint.h>
#include <qregion.h>
#include <qptrstack.h>
#include <qpointarray.h>

using namespace DOM;
using namespace HTMLNames;
using namespace khtml;

// -------------------------------------------------------------------------

HTMLCanvasElementImpl::HTMLCanvasElementImpl(DocumentImpl *doc)
    : HTMLImageElementImpl(canvasTag, doc)
{
}

HTMLCanvasElementImpl::~HTMLCanvasElementImpl()
{
}

bool HTMLCanvasElementImpl::mapToEntry(const QualifiedName& attrName, MappedAttributeEntry& result) const
{
    if (attrName != srcAttr) // Ignore the src attribute
        return HTMLImageElementImpl::mapToEntry(attrName, result);
    return false;
}

void HTMLCanvasElementImpl::parseMappedAttribute(MappedAttributeImpl *attr)
{
    if (attr->name() != srcAttr) // Canvas ignores the src attribute
        HTMLImageElementImpl::parseMappedAttribute(attr);
}

RenderObject *HTMLCanvasElementImpl::createRenderer(RenderArena *arena, RenderStyle *style)
{
     return new (arena) RenderCanvasImage(this);
}

void HTMLCanvasElementImpl::attach()
{
    // Don't want to call image's attach().
    HTMLElementImpl::attach();
}

void HTMLCanvasElementImpl::detach()
{
    // Don't want to call image's detach().
    HTMLElementImpl::detach();
}

bool HTMLCanvasElementImpl::isURLAttribute(AttributeImpl *attr) const
{
    return ((attr->name() == usemapAttr && attr->value().domString()[0] != '#'));
}
