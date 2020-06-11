#define RM_MAJOR_VERSION 1
#define RM_MINOR_VERSION 3
#define RM_PATCH_VERSION 6

#define STR1(x) #x
#define STR2(x) STR1(x)

#define RM_VERSION STR2(RM_MAJOR_VERSION) "." STR2(RM_MINOR_VERSION) "." STR2(RM_PATCH_VERSION)