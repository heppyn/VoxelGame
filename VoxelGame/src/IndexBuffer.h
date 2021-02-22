#pragma once
class IndexBuffer
{
private:
	unsigned int m_rendererID;
	unsigned int m_count;

public:
	// TODO: support smaller data types
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	unsigned int Count() const { return m_count; }
};

