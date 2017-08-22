#pragma once

template <typename T>
class Singleton
{
public:
	static T* getInstance() { return s_Instance; }
	static void initialize() { s_Instance = new T(); }
	static void shutdown() { delete s_Instance; s_Instance = nullptr; }
private:
	static T* s_Instance;
};

template <typename T>
T* Singleton<T>::s_Instance = nullptr;