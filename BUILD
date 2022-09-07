cc_binary(
  name = "reflect",
  deps = ["@com_google_absl//absl/strings"],
  srcs = ["reflect.cc"],
)

cc_binary(
    name="seq",
    srcs = ["seq.c"],
    deps = ["@alsa-lib",],
    linkopts = ["-ldl"],
    # linkshared=True,
)

cc_binary(
    name="sender",
    srcs = ["sender.c"],
    deps = ["@alsa-lib",],
    linkopts = ["-ldl"],
)
