#ifndef __CRYPTO_H__
#define __CRYPTO_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "sha256.h"
#include "md5.h"
#include "des.h"

/**
 * function sha2str use to convert hash sha256 to string.
 * @param hash              hash sha256/md5
 * @param result            result convert
 * @return                  the function return length of string.
*/
int sha2str(BYTE *hash, char result[]);
/**
 * function md52str use to convert hash sha256 to string.
 * @param hash              hash sha256/md5
 * @param result            result convert
 * @return                  the function return length of string.
*/
int md52str(BYTE *hash, char result[]);
/**
 * function sha2des use to convert hash sha256 to string.
 * @param hash              hash sha
 * @param result            result convert des
 * @return                  the function return length of string.
*/
int sha2des(BYTE *hash, char result[]);
/**
 * function sha2str use to convert hash sha256 to string.
 * @param hash              hash des
 * @param result            result convert
 * @return                  the function return length of string.
*/
int des2str(BYTE *hash, char result[]);
#endif