
cc_library(
    name = 'lthread',
    srcs =[
        'Thread.cc'
    ],
)

cc_binary(
    name = 'thread_test', 
    srcs =[
        'thread_test.cc'
    ],
    deps = [
        ':lthread',
        '#log4cpp',
        '#pthread',
    ],
)
