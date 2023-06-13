#pragma once
#define SERIALIZE_CLASS(cls) \
public: \
void serialize(std::ofstream& stream) const { \
	serialize_members(stream, *this); \
} \
void deserialize(std::ifstream& stream) { \
	deserialize_members(stream, *this); \
} \
private: \
template <typename Stream> \
void serialize_members(Stream& stream, const cls& self) const { \
	stream.write((char*)&self, sizeof(cls)); \
} \
template <typename Stream> \
void deserialize_members(Stream& stream, cls& self) { \
	stream.read((char*)&self, sizeof(cls)); \
}