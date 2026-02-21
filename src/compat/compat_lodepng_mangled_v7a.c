// compat_lodepng_mangled_v7a.c
// Provide the original C++-mangled LodePNG 20131115 symbol names as plain C exports,
// so dynsym matches the original liblwplocal.so (armeabi-v7a).
// These wrappers forward to the actual C implementations compiled from src/lodepng/lodepng.c.
//
// NOTE: The symbol names below are *intentionally* Itanium C++ ABI mangled strings.
#include "ef2/lodepng.h"
#include <stddef.h>

#if defined(__GNUC__) || defined(__clang__)
  #define EF2_EXPORT_USED __attribute__((visibility("default"))) __attribute__((used))
#else
  #define EF2_EXPORT_USED
#endif

// Forward declarations for a few non-public helpers that exist in lodepng.c but are not in the header.
unsigned getValueRequiredBits(unsigned short value);
unsigned lodepng_read32bitInt(const unsigned char* buffer);
void     lodepng_info_swap(LodePNGInfo* a, LodePNGInfo* b);
size_t   lodepng_get_raw_size_lct(unsigned w, unsigned h, LodePNGColorType colortype, unsigned bitdepth);

// --- Wrappers (mangled exports) ---
EF2_EXPORT_USED unsigned _Z13lodepng_crc32PKhj(const unsigned char* data, size_t length) {
  return lodepng_crc32(data, length);
}

EF2_EXPORT_USED unsigned _Z14lodepng_decodePPhPjS1_P12LodePNGStatePKhj(unsigned char** out, unsigned* w, unsigned* h, LodePNGState* state, const unsigned char* in, size_t insize) {
  return lodepng_decode(out, w, h, state, in, insize);
}

EF2_EXPORT_USED unsigned _Z14lodepng_encodePPhPjPKhjjP12LodePNGState(unsigned char** out, size_t* outsize, const unsigned char* image, unsigned w, unsigned h, LodePNGState* state) {
  return lodepng_encode(out, outsize, image, w, h, state);
}

EF2_EXPORT_USED unsigned _Z15lodepng_convertPhPKhP16LodePNGColorModePKS2_jjj(unsigned char* out, const unsigned char* in, LodePNGColorMode* mode_out, const LodePNGColorMode* mode_in, unsigned w, unsigned h, unsigned bits) {
  return lodepng_convert(out, in, mode_out, mode_in, w, h, bits);
}

EF2_EXPORT_USED unsigned _Z15lodepng_deflatePPhPjPKhjPK23LodePNGCompressSettings(unsigned char** out, size_t* outsize, const unsigned char* in, size_t insize, const LodePNGCompressSettings* settings) {
  return lodepng_deflate(out, outsize, in, insize, settings);
}

EF2_EXPORT_USED unsigned _Z15lodepng_get_bppPK16LodePNGColorMode(const LodePNGColorMode* mode) {
  return lodepng_get_bpp(mode);
}

EF2_EXPORT_USED unsigned _Z15lodepng_inflatePPhPjPKhjPK25LodePNGDecompressSettings(unsigned char** out, size_t* outsize, const unsigned char* in, size_t insize, const LodePNGDecompressSettings* settings) {
  return lodepng_inflate(out, outsize, in, insize, settings);
}

EF2_EXPORT_USED unsigned _Z15lodepng_inspectPjS_P12LodePNGStatePKhj(unsigned* w, unsigned* h, LodePNGState* state, const unsigned char* in, size_t insize) {
  return lodepng_inspect(w, h, state, in, insize);
}

EF2_EXPORT_USED unsigned _Z16lodepng_add_textP11LodePNGInfoPKcS2_(LodePNGInfo* info, const char* key, const char* str) {
  return lodepng_add_text(info, key, str);
}

EF2_EXPORT_USED unsigned _Z16lodepng_decode24PPhPjS1_PKhj(unsigned char** out, unsigned* w, unsigned* h, const unsigned char* in, size_t insize) {
  return lodepng_decode24(out, w, h, in, insize);
}

EF2_EXPORT_USED unsigned _Z16lodepng_decode32PPhPjS1_PKhj(unsigned char** out, unsigned* w, unsigned* h, const unsigned char* in, size_t insize) {
  return lodepng_decode32(out, w, h, in, insize);
}

EF2_EXPORT_USED unsigned _Z16lodepng_encode24PPhPjPKhjj(unsigned char** out, size_t* outsize, const unsigned char* image, unsigned w, unsigned h) {
  return lodepng_encode24(out, outsize, image, w, h);
}

EF2_EXPORT_USED unsigned _Z16lodepng_encode32PPhPjPKhjj(unsigned char** out, size_t* outsize, const unsigned char* image, unsigned w, unsigned h) {
  return lodepng_encode32(out, outsize, image, w, h);
}

EF2_EXPORT_USED unsigned _Z17lodepng_add_itextP11LodePNGInfoPKcS2_S2_S2_(LodePNGInfo* info, const char* key, const char* langtag, const char* transkey, const char* str) {
  return lodepng_add_itext(info, key, langtag, transkey, str);
}

EF2_EXPORT_USED unsigned _Z17lodepng_info_copyP11LodePNGInfoPKS_(LodePNGInfo* dest, const LodePNGInfo* src) {
  return lodepng_info_copy(dest, src);
}
EF2_EXPORT_USED void _Z17lodepng_info_initP11LodePNGInfo(LodePNGInfo* info) {
  lodepng_info_init(info);
}

EF2_EXPORT_USED void _Z17lodepng_info_swapP11LodePNGInfoS0_(LodePNGInfo* a, LodePNGInfo* b) {
  lodepng_info_swap(a, b);
}

EF2_EXPORT_USED unsigned _Z17lodepng_load_filePPhPjPKc(unsigned char** out, size_t* outsize, const char* filename) {
  return lodepng_load_file(out, outsize, filename);
}

EF2_EXPORT_USED unsigned _Z17lodepng_save_filePKhjPKc(const unsigned char* buffer, size_t buffersize, const char* filename) {
  return lodepng_save_file(buffer, buffersize, filename);
}

EF2_EXPORT_USED unsigned char* _Z18lodepng_chunk_dataPh(unsigned char* chunk) {
  return lodepng_chunk_data(chunk);
}

EF2_EXPORT_USED unsigned char* _Z18lodepng_chunk_nextPh(unsigned char* chunk) {
  return lodepng_chunk_next(chunk);
}

EF2_EXPORT_USED void _Z18lodepng_chunk_typePcPKh(char type[5], const unsigned char* chunk) {
  lodepng_chunk_type(type, chunk);
}

EF2_EXPORT_USED void _Z18lodepng_clear_textP11LodePNGInfo(LodePNGInfo* info) {
  lodepng_clear_text(info);
}

EF2_EXPORT_USED const char* _Z18lodepng_error_textj(unsigned code) {
  return lodepng_error_text(code);
}

EF2_EXPORT_USED void _Z18lodepng_state_copyP12LodePNGStatePKS_(LodePNGState* dest, const LodePNGState* src) {
  lodepng_state_copy(dest, src);
}

EF2_EXPORT_USED void _Z18lodepng_state_initP12LodePNGState(LodePNGState* state) {
  lodepng_state_init(state);
}

EF2_EXPORT_USED void _Z19lodepng_clear_itextP11LodePNGInfo(LodePNGInfo* info) {
  lodepng_clear_itext(info);
}

EF2_EXPORT_USED unsigned _Z19lodepng_decode_filePPhPjS1_PKc16LodePNGColorTypej(unsigned char** out, unsigned* w, unsigned* h, const char* filename, LodePNGColorType colortype, unsigned bitdepth) {
  return lodepng_decode_file(out, w, h, filename, colortype, bitdepth);
}

EF2_EXPORT_USED unsigned _Z19lodepng_encode_filePKcPKhjj16LodePNGColorTypej(const char* filename, const unsigned char* image, unsigned w, unsigned h, LodePNGColorType colortype, unsigned bitdepth) {
  return lodepng_encode_file(filename, image, w, h, colortype, bitdepth);
}

EF2_EXPORT_USED unsigned _Z19lodepng_palette_addP16LodePNGColorModehhhh(LodePNGColorMode* mode, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
  return lodepng_palette_add(mode, r, g, b, a);
}

EF2_EXPORT_USED unsigned _Z20getValueRequiredBitst(unsigned short value) {
  return getValueRequiredBits(value);
}

EF2_EXPORT_USED unsigned _Z20lodepng_chunk_appendPPhPjPKh(unsigned char** out, size_t* outsize, const unsigned char* chunk) {
  return lodepng_chunk_append(out, outsize, chunk);
}

EF2_EXPORT_USED unsigned _Z20lodepng_chunk_createPPhPjjPKcPKh(unsigned char** out, size_t* outsize, unsigned length, const char* type, const unsigned char* data) {
  return lodepng_chunk_create(out, outsize, length, type, data);
}

EF2_EXPORT_USED unsigned _Z20lodepng_chunk_lengthPKh(const unsigned char* chunk) {
  return lodepng_chunk_length(chunk);
}

EF2_EXPORT_USED unsigned _Z20lodepng_get_channelsPK16LodePNGColorMode(const LodePNGColorMode* mode) {
  return lodepng_get_channels(mode);
}

EF2_EXPORT_USED size_t _Z20lodepng_get_raw_sizejjPK16LodePNGColorMode(unsigned w, unsigned h, const LodePNGColorMode* mode) {
  return lodepng_get_raw_size(w, h, mode);
}

EF2_EXPORT_USED void _Z20lodepng_info_cleanupP11LodePNGInfo(LodePNGInfo* info) {
  lodepng_info_cleanup(info);
}

EF2_EXPORT_USED unsigned _Z20lodepng_read32bitIntPKh(const unsigned char* buffer) {
  return lodepng_read32bitInt(buffer);
}

EF2_EXPORT_USED unsigned char _Z21lodepng_chunk_privatePKh(const unsigned char* chunk) {
  return lodepng_chunk_private(chunk);
}

EF2_EXPORT_USED unsigned _Z21lodepng_decode24_filePPhPjS1_PKc(unsigned char** out, unsigned* w, unsigned* h, const char* filename) {
  return lodepng_decode24_file(out, w, h, filename);
}

EF2_EXPORT_USED unsigned _Z21lodepng_decode32_filePPhPjS1_PKc(unsigned char** out, unsigned* w, unsigned* h, const char* filename) {
  return lodepng_decode32_file(out, w, h, filename);
}

EF2_EXPORT_USED unsigned _Z21lodepng_decode_memoryPPhPjS1_PKhj16LodePNGColorTypej(unsigned char** out, unsigned* w, unsigned* h, const unsigned char* in, size_t insize, LodePNGColorType colortype, unsigned bitdepth) {
  return lodepng_decode_memory(out, w, h, in, insize, colortype, bitdepth);
}

EF2_EXPORT_USED unsigned _Z21lodepng_encode24_filePKcPKhjj(const char* filename, const unsigned char* image, unsigned w, unsigned h) {
  return lodepng_encode24_file(filename, image, w, h);
}

EF2_EXPORT_USED unsigned _Z21lodepng_encode32_filePKcPKhjj(const char* filename, const unsigned char* image, unsigned w, unsigned h) {
  return lodepng_encode32_file(filename, image, w, h);
}

EF2_EXPORT_USED unsigned _Z21lodepng_encode_memoryPPhPjPKhjj16LodePNGColorTypej(unsigned char** out, size_t* outsize, const unsigned char* image, unsigned w, unsigned h, LodePNGColorType colortype, unsigned bitdepth) {
  return lodepng_encode_memory(out, outsize, image, w, h, colortype, bitdepth);
}

EF2_EXPORT_USED unsigned _Z21lodepng_is_alpha_typePK16LodePNGColorMode(const LodePNGColorMode* mode) {
  return lodepng_is_alpha_type(mode);
}

EF2_EXPORT_USED void _Z21lodepng_palette_clearP16LodePNGColorMode(LodePNGColorMode* mode) {
  lodepng_palette_clear(mode);
}

EF2_EXPORT_USED void _Z21lodepng_state_cleanupP12LodePNGState(LodePNGState* state) {
  lodepng_state_cleanup(state);
}

EF2_EXPORT_USED unsigned _Z21lodepng_zlib_compressPPhPjPKhjPK23LodePNGCompressSettings(unsigned char** out, size_t* outsize, const unsigned char* in, size_t insize, const LodePNGCompressSettings* settings) {
  return lodepng_zlib_compress(out, outsize, in, insize, settings);
}

EF2_EXPORT_USED unsigned _Z22lodepng_can_have_alphaPK16LodePNGColorMode(const LodePNGColorMode* mode) {
  return lodepng_can_have_alpha(mode);
}

EF2_EXPORT_USED unsigned char _Z23lodepng_chunk_ancillaryPKh(const unsigned char* chunk) {
  return lodepng_chunk_ancillary(chunk);
}

EF2_EXPORT_USED unsigned _Z23lodepng_chunk_check_crcPKh(const unsigned char* chunk) {
  return lodepng_chunk_check_crc(chunk);
}

EF2_EXPORT_USED unsigned _Z23lodepng_color_mode_copyP16LodePNGColorModePKS_(LodePNGColorMode* dest, const LodePNGColorMode* src) {
  return lodepng_color_mode_copy(dest, src);
}

EF2_EXPORT_USED void _Z23lodepng_color_mode_initP16LodePNGColorMode(LodePNGColorMode* mode) {
  lodepng_color_mode_init(mode);
}

EF2_EXPORT_USED unsigned _Z23lodepng_is_palette_typePK16LodePNGColorMode(const LodePNGColorMode* mode) {
  return lodepng_is_palette_type(mode);
}

EF2_EXPORT_USED unsigned _Z23lodepng_zlib_decompressPPhPjPKhjPK25LodePNGDecompressSettings(unsigned char** out, size_t* outsize, const unsigned char* in, size_t insize, const LodePNGDecompressSettings* settings) {
  return lodepng_zlib_decompress(out, outsize, in, insize, settings);
}

EF2_EXPORT_USED const unsigned char* _Z24lodepng_chunk_data_constPKh(const unsigned char* chunk) {
  return lodepng_chunk_data_const(chunk);
}

EF2_EXPORT_USED const unsigned char* _Z24lodepng_chunk_next_constPKh(const unsigned char* chunk) {
  return lodepng_chunk_next_const(chunk);
}

EF2_EXPORT_USED unsigned char _Z24lodepng_chunk_safetocopyPKh(const unsigned char* chunk) {
  return lodepng_chunk_safetocopy(chunk);
}

EF2_EXPORT_USED size_t _Z24lodepng_get_raw_size_lctjj16LodePNGColorTypej(unsigned w, unsigned h, LodePNGColorType colortype, unsigned bitdepth) {
  return lodepng_get_raw_size_lct(w, h, colortype, bitdepth);
}

EF2_EXPORT_USED unsigned _Z25lodepng_auto_choose_colorP16LodePNGColorModePKhjjPKS_18LodePNGAutoConvert(LodePNGColorMode* mode_out, const unsigned char* image, unsigned w, unsigned h, const LodePNGColorMode* mode_in, LodePNGAutoConvert auto_convert) {
  return lodepng_auto_choose_color(mode_out, image, w, h, mode_in, auto_convert);
}

EF2_EXPORT_USED unsigned char _Z25lodepng_chunk_type_equalsPKhPKc(const unsigned char* chunk, const char* type) {
  return lodepng_chunk_type_equals(chunk, type);
}

EF2_EXPORT_USED unsigned _Z25lodepng_has_palette_alphaPK16LodePNGColorMode(const LodePNGColorMode* mode) {
  return lodepng_has_palette_alpha(mode);
}

EF2_EXPORT_USED unsigned _Z25lodepng_is_greyscale_typePK16LodePNGColorMode(const LodePNGColorMode* mode) {
  return lodepng_is_greyscale_type(mode);
}

EF2_EXPORT_USED void _Z26lodepng_chunk_generate_crcPh(unsigned char* chunk) {
  lodepng_chunk_generate_crc(chunk);
}

EF2_EXPORT_USED void _Z26lodepng_color_mode_cleanupP16LodePNGColorMode(LodePNGColorMode* mode) {
  lodepng_color_mode_cleanup(mode);
}

EF2_EXPORT_USED unsigned _Z28lodepng_huffman_code_lengthsPjPKjjj(unsigned* lengths, const unsigned* frequencies, size_t numcodes, unsigned maxbitlen) {
  return lodepng_huffman_code_lengths(lengths, frequencies, numcodes, maxbitlen);
}
EF2_EXPORT_USED void _Z29lodepng_decoder_settings_initP22LodePNGDecoderSettings(LodePNGDecoderSettings* settings) {
  lodepng_decoder_settings_init(settings);
}

EF2_EXPORT_USED void _Z29lodepng_encoder_settings_initP22LodePNGEncoderSettings(LodePNGEncoderSettings* settings) {
  lodepng_encoder_settings_init(settings);
}

EF2_EXPORT_USED void _Z30lodepng_compress_settings_initP23LodePNGCompressSettings(LodePNGCompressSettings* settings) {
  lodepng_compress_settings_init(settings);
}

EF2_EXPORT_USED void _Z32lodepng_decompress_settings_initP25LodePNGDecompressSettings(LodePNGDecompressSettings* settings) {
  lodepng_decompress_settings_init(settings);
}
