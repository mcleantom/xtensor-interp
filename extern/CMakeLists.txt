include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
)

FetchContent_Declare(
  xtl
  GIT_REPOSITORY https://github.com/xtensor-stack/xtl
  GIT_TAG        fea39142693fbbc2ef19d75012bc6b46ef0a5f8c # release-0.7.5
)

FetchContent_Declare(
  xtensor
  GIT_REPOSITORY https://github.com/xtensor-stack/xtensor
  GIT_TAG        545dd7aa78104052bb8e45c3175efff313d477dc # release-0.7.5
)


FetchContent_MakeAvailable(googletest xtl xtensor)