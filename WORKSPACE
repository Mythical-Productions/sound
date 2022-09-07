load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
  name = "com_google_absl",
  urls = ["https://github.com/abseil/abseil-cpp/archive/731689ffc2ad7bb95cc86b5b6160dbe7858f27a0.zip"],
  strip_prefix = "abseil-cpp-731689ffc2ad7bb95cc86b5b6160dbe7858f27a0",
)

http_archive(
  name = "rules_cc",
  urls = ["https://github.com/bazelbuild/rules_cc/archive/262ebec3c2296296526740db4aefce68c80de7fa.zip"],
  strip_prefix = "rules_cc-262ebec3c2296296526740db4aefce68c80de7fa",
)
http_archive(
  name = "com_google_googletest",
  urls = ["https://github.com/google/googletest/archive/b53547bf01ee6d5c547bc539a498c49bc6027169.zip"],
  strip_prefix = "googletest-b53547bf01ee6d5c547bc539a498c49bc6027169",
)

http_archive(
    name = "com_github_google_benchmark",
    urls = ["https://github.com/google/benchmark/archive/dc901ff9090e2b931433790cc44afc3af3b09ab2.zip"],
    strip_prefix = "benchmark-dc901ff9090e2b931433790cc44afc3af3b09ab2",
)

http_archive(
    name = "bazel_skylib",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.2.1/bazel-skylib-1.2.1.tar.gz",
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.2.1/bazel-skylib-1.2.1.tar.gz",
    ],
    sha256 = "f7be3474d42aae265405a592bb7da8e171919d74c16f082a5457840f06054728",
)
load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")
bazel_skylib_workspace()


http_archive(
    name="alsa-lib",
    build_file="//alsa-lib:BUILD.alsa-lib",
    sha256 = "ad582993d52cdb5fb159a0beab60a6ac57eab0cc1bdf85dc4db6d6197f02333f",
    #strip_prefix = "alsa-lib-1.2.6.1",
    urls=["https://www.alsa-project.org/files/pub/lib/alsa-lib-1.2.6.1.tar.bz2",],
)

http_archive(
    name = "rules_foreign_cc",
    # TODO: Get the latest sha256 value from a bazel debug message or the latest
    #       release on the releases page: https://github.com/bazelbuild/rules_foreign_cc/releases
    #
    # sha256 = "...",
    strip_prefix = "rules_foreign_cc-c57b55f2f6207c0c44c2b4a51dc235955d4f47b2",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/c57b55f2f6207c0c44c2b4a51dc235955d4f47b2.tar.gz",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")
rules_foreign_cc_dependencies()
