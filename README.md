# rapidcheck_codedive

## How to build?

    git clone https://github.com/pmalek/rapidcheck_codedive.git
    mkdir build && cd build && cmake ../rapidcheck_codedive && make && ctest

It is possible to tweak [RapidCheck](https://github.com/emil-e/rapidcheck) parameters by running `ctest` with `RC_PARAMS` like so:

    RC_PARAMS="max_success=10000" ctest
