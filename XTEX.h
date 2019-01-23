#pragma once

#include <queue>
#include <algorithm>
#include <functional>

#include <GL/glew.h>

#include "TEX.h"
#include "Aspects.hpp"



class X_TEX
{
	mutable TwoStatesManager m_loading;
	mutable TwoStatesManager m_binding;

	TEX m_tex;

public:

	friend void swap(X_TEX& t1, X_TEX& t2);

	X_TEX() = default;
	~X_TEX() = default;

	X_TEX(const X_TEX&) = delete;
	X_TEX& operator=(const X_TEX&) = delete;

	X_TEX(X_TEX&& xtex) : 
		m_loading(xtex.m_loading),
		m_binding(xtex.m_binding),
		m_tex(std::move(xtex.m_tex))
	{
	}
	X_TEX& operator=(X_TEX&& T);
	
	operator GLuint() const
	{
		return (m_binding.checkOn(static_cast<std::function<GLuint(const TEX&)>>(&TEX::operator GLuint)))(m_tex);
	}

	void loadBMP_custom(const char* const filepath) // TODO: a két függvényt regexpes estszétválasztással összevonni egybe 
	{
		return (m_loading.turnOn(static_cast<std::function<void(TEX&, const char* const)>>(&TEX::loadBMP_custom)))(m_tex, filepath);
	} // TODO: write our own Texture loader that unbinds target.
	void loadDDS(const char* const filepath)
	{
		return (m_loading.turnOn(static_cast<std::function<void(TEX&, const char* const)>>(&TEX::loadDDS)))(m_tex, filepath);
	} // TODO: write our own Texture loader that unbinds target.
	void unLoad()
	{
		//auto func = m_bindin
		return (m_loading.turnOff(static_cast<std::function<void(TEX&)>>(&TEX::unLoad)))(m_tex);
		m_tex.unLoad();
	}

	void bind() const
	{
		auto func = m_binding.turnOn(static_cast<std::function<void(const TEX&)>>(&TEX::bind));
		return (m_loading.checkOn(func))(m_tex);
	}
	void unBind() const
	{
		return (m_binding.turnOff(static_cast<std::function<void(const TEX&)>>(&TEX::unBind)))(m_tex);
	}

};

