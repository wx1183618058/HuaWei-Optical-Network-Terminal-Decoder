#ifndef XMLFILE_H
#define XMLFILE_H

#include <stdint.h>
#include <QString>

class XmlFile
{
public:
    XmlFile() = default;
    XmlFile(const QString &in_file) : in_file_(in_file) {}
    int decrypt(const QString &out_file);
    int encrypt(const QString &out_file);
    int is_xml();
    void rename(const QString &newname);
    void setIn_file(const QString &in_file);

protected:
    uint32_t get_crc(const QString &in_file, int offset);
    int compress_gz(const QString &in_file, const QString &out_file);
    int extract_gz(const QString &in_file, const QString &out_file);

private:
    QString in_file_;
};

#endif // XMLFILE_H
