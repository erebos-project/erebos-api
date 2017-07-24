#ifndef NO_CRYPTO
#include "crypto.h"
#include "aes.h"
#include "sha256.h"
#include "md5.h"
#include "framework.h"

using namespace erebos;


std::string erebos::crypto::digest_SHA256(data_t input) {

	SHA256_CTX ctx;
	sha256_init(&ctx);
	sha256_update(&ctx, (BYTE*) input.data, input.size);

	BYTE* buf = new BYTE[SHA256_BLOCK_SIZE];
	if(!buf)
		return "";

	sha256_final(&ctx, buf);

	return byte_to_hex(buf, SHA256_BLOCK_SIZE);
}


std::string erebos::crypto::digest_MD5(data_t input) {

	MD5_CTX ctx;
	md5_init(&ctx);
	md5_update(&ctx, (BYTE*) input.data, input.size);

	BYTE* buf = new BYTE[MD5_BLOCK_SIZE];
	if(!buf)
		return "";
	md5_final(&ctx, buf);

	return byte_to_hex(buf, MD5_BLOCK_SIZE);
}


data_t erebos::crypto::encrypt_AES256(data_t input, data_t key, data_t IV) {

	if(key.size != 32)
		return data_t();

	WORD key_schedule[60];
	aes_key_setup((BYTE*) key.data, key_schedule, 256);

	data_t output;
	output.data = new char[input.size];
	if(!output.data)
		return data_t();

	output.size = input.size;

	aes_encrypt_ctr((BYTE*) input.data, 32, (BYTE*) output.data, key_schedule, 256, (BYTE*) IV.data);

	return output;
}


data_t erebos::crypto::decrypt_AES256(data_t input, data_t key, data_t IV) {

	if(key.size != 256)
		return data_t();

	WORD key_schedule[60];
	aes_key_setup((BYTE*) key.data, key_schedule, 256);

	data_t output;
	output.data = new char[input.size];
	if(!output.data)
		return data_t();

	output.size = input.size;

	aes_decrypt_ctr((BYTE*) input.data, 32, (BYTE*) output.data, key_schedule, 256, (BYTE*) IV.data);

	return output;
}

#endif // NO_CRYPTO
