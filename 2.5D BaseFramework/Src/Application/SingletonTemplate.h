#pragma once

template<class T>
class Singleton
{
public:
	static inline T& GetInstance()
	{
		static T instance;
		return instance;
	}

protected:
	Singleton() {}//外部でのインスタンス作成は禁止
	virtual ~Singleton() {}

private:
};