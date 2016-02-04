/**
 *  Copyright 2014-2016 CyberVision, Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "sha1.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "../../kaa_common.h"
#include "../../platform/ext_sha.h"
#include "../../platform/sock.h"



kaa_error_t ext_calculate_sha_hash(const char *data, size_t data_size, kaa_digest digest)
{
    KAA_RETURN_IF_NIL(digest, KAA_ERR_BADPARAM);

    SHA1Context sha;
    SHA1Reset(&sha);
    SHA1Input(&sha, (const unsigned char *) data, data_size);
    SHA1Result(&sha);

    int i;
    for (i = 0; i < 5; ++i) {
        *(int32_t *)(digest + i * 4) = KAA_HTONL(sha.Message_Digest[i]);
    }

    return KAA_ERR_NONE;
}

kaa_error_t ext_copy_sha_hash(kaa_digest_p dst, const kaa_digest_p src)
{
    KAA_RETURN_IF_NIL2(dst, src, KAA_ERR_BADPARAM);
    memcpy(dst, src, SHA_1_DIGEST_LENGTH);
    return KAA_ERR_NONE;
}
