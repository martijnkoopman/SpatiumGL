/*
 * Program: Spatium Graphics Library
 *
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#ifndef SPATIUMGL_RENDERWINDOW_H
#define SPATIUMGL_RENDERWINDOW_H

#include "spatiumglexport.hpp"
#include "Vector.hpp"
#include "PivotInteractor.hpp"
#include "RenderWindowInteractor.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"

namespace spatiumgl
{

class SPATIUMGL_EXPORT RenderWindow
{
public:
	// Constructor
	RenderWindow(bool debug=false)
		: m_interactor(new PivotInteractor(this))
		, m_camera(nullptr)
		, m_renderer(nullptr)
		, m_framebufferSize{ 0, 0 }
		, m_debug(debug)
	{}

	// Destructor
	virtual ~RenderWindow()
	{
		delete m_interactor;
	}

	virtual bool init() = 0;
	virtual bool createWindow(int width, int height) = 0;
	virtual void destroyWindow() = 0;
	virtual void terminate() const = 0;
	virtual void show() = 0;

	void setInteractor(RenderWindowInteractor* interactor)
	{
		m_interactor = interactor;
	}

	RenderWindowInteractor* interactor() const
	{
		return m_interactor;
	}

	void setCamera(Camera* camera)
	{
		m_camera = camera;
	}

	Camera* camera() const
	{
		return m_camera;
	}

	void setRenderer(Renderer* renderer)
	{
		m_renderer = renderer;
	}

	Vector2i framebufferSize() const
	{
		return m_framebufferSize;
	}

protected:
	RenderWindowInteractor* m_interactor;
	Renderer* m_renderer;
	Camera* m_camera;
	Vector2i m_framebufferSize;
	bool m_debug;
};

} // namespace spatiumgl

#endif // SPATIUMGL_RENDERWINDOW_H