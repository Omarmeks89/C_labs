#pragma once

#ifndef ERR_CODES_H
#define ERR_CODES_H

#ifdef __cplusplus
extern "C"
#endif

enum status {
    SUCCESS = 0,
    NOITER,
    NOTABS,
    GOTOVF,
    NULADR,
    INVDIM,
    NALLOC,
    NEQUAL,
    NODATA,                     /* target array is empty, have no elements/ */
};

#endif /* ERR_CODES_H */
