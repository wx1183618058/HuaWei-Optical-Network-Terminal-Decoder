#ifndef CFGFILE_H
#define CFGFILE_H

#include "xmlfile.h"

class CfgFile : public XmlFile
{
public:
    CfgFile() = default;
    CfgFile(const QString &in_file) : XmlFile(in_file), in_file_(in_file) {}
    int decrypt(const QString &out_file);
    int encrypt(const QString &out_file);
    int is_cfg();
    void rename(const QString &newname);

protected:
    uint32_t get_crc(const QString &in_file, int offset);

private:
    QString in_file_;
};

#endif // CFGFILE_H
