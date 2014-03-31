
cc_library(
    name = 'lfile',
    srcs = [
        'File.cc'
    ],
    deps = [],
)

cc_binary(
    name = 'file_test',
    srcs = [
        'file_test.cc'
    ],
    deps = [
        ':lfile',
        '#log4cpp',
        '#pthread',
    ],
)
