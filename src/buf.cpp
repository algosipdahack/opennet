#include "buf.h"

Buf::Buf(pbyte data, size_t size)
{
  data_ = data;
  size_ = size;
}

bool Buf::valid()
{
  return data_ != nullptr;
}

void Buf::clear()
{
  data_ = nullptr;
  size_ = 0;
}