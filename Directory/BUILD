
cc_library(
    name = 'ldirectory',
    srcs = [
           'Directory.cc'
           ],
    deps =[],
)

cc_binary(  # can't write '(' into the second line
    name = 'dirct_test',
    srcs = [
           'directory_test.cc',
           ],
    deps = [
           ':ldirectory',
           '#log4cpp',
           '#pthread',
           ],
)
