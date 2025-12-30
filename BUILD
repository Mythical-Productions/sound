cc_binary(
  name = "reflect",
  deps = ["@abseil-cpp//absl/strings"],
  srcs = ["reflect.cc"],
)

cc_binary(
    name="seq",
    srcs = ["seq.c"],
    deps = ["@alsa_lib",],
    linkopts = ["-ldl"],
    # linkshared=True,
)

cc_binary(
    name="sender",
    srcs = ["sender.c"],
    deps = ["@alsa_lib",],
    linkopts = ["-ldl"],
)
