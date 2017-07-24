#ifndef NO_CRYPTO
#ifndef EREBOS_CRYPTO_H
#define EREBOS_CRYPTO_H

#include <string>
#include "ftypes.h"

namespace erebos {
	/*!
	 * @brief contains cryptography functions as AES and SHA
	 */
	namespace crypto {
		/*!
		 * @brief hashes the given string
		 * @param input: the string to digest
		 * @return hash of given string, empty on error
		 */
		ERAPI std::string digest_SHA256(data_t input);
		/*!
		 * @brief hashes the given block of data
		 * @param input: the data to digest
		 * @return hash of given data, empty on error
		 */
		inline std::string digest_SHA256(std::string input) {
			return digest_SHA256(data_t(input));
		}
		/*!
		 * @brief hashes the given string
		 * @param input: the string to digest
		 * @return hash of given string, empty on error
		 */
		ERAPI std::string digest_MD5(data_t input);
		/*!
		 * @brief hashes the given block of data
		 * @param input: the data to digest
		 * @return hash of given data, empty on error
		 */
		inline std::string digest_MD5(std::string input) {
			return digest_MD5(data_t(input));
		}
		/*!
		 * @brief AES encrypts the given block of data
		 * @param input: the data to encrypt
		 * @param key: the passphrase to use
		 * @param IV: the IV to use (optional)
		 * @return encrypted data
		 */
		ERAPI data_t encrypt_AES256(data_t input, data_t key, data_t IV = data_t());
		/*!
		 * @brief AES decrypts the given block of data
		 * @param input: the data to decrypt
		 * @param key: the passphrase to use
		 * @param IV: the IV to use (optional)
		 * @return decrypted data
		 */
		ERAPI data_t decrypt_AES256(data_t input, data_t key, data_t IV = data_t());

	}

}


#endif //_CRYPTO_H
#endif // NO_CRYPTO
