#ifndef AESCRYPT_H
#define AESCRYPT_H

#include <stdint.h>
#include <QString>

class AesCrypt
{
public:
    enum AesCryptMode {
        $1 = 1,
        $2 = 2,
        SU = 3
    };
    AesCrypt(const QString &text, const AesCryptMode &mode);
    int check_format();
    QString decrypt();
    QString text() const;
    void setText(const QString &text);
    AesCryptMode mode() const;
    void setMode(const AesCryptMode &mode);

private:
    QString text_;
    AesCryptMode mode_;
    QString decrypt_$1();
    QString decrypt_$2();
    QString decrypt_SU();
    int encode_to_char(QString &encode);
    uint8_t aes_rotl(uint8_t ch, int c);
    void aes_ascii_unvisible(uint8_t *str, size_t str_len);
    void aes_generate_rand_pwd_key(const uint8_t *str, uint8_t *aes_key);
    uint32_t aes_enh_sys_to_long(const uint8_t *plain);
    void aes_plain_to_bin(const uint8_t * plain, uint8_t * bin);
    void wbox_decrypt(uint8_t *encryption_key, uint8_t *out);
    void aes_get_cbc_key(char *key, int len, char *key_out);

};

#endif // AESCRYPT_H
