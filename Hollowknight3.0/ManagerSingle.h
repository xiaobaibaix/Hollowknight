#pragma once

template <typename T>
class ManagerSingle {
public:

	static T* instence() {
		if (!m_instence)
			m_instence = new T;
		return m_instence;
	}

protected:
	ManagerSingle() = default;
	virtual~ManagerSingle() = default;

private:

	ManagerSingle(const T& m) = delete;
	T& operator=(const T& m) = delete;



private:
	static T* m_instence;

};

template <typename T>
T* ManagerSingle<T>::m_instence = nullptr;