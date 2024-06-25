# ddprof-statsd

A gradle submodule wrapper for the [DogFood](https://github.com/garrettsickles/DogFood) header-only statsd library.

The wrapper is implemente as a git subtree in the `ddprof-statsd` directory. 
The subtree is locked to `v2.0` tag of the `DogFood` library. If you need to update the `DogFood` library, you can do so by 
```shell
cd <project-root>
git subtree pull --prefix=ddprof-statss/dogfood-statsd subrepo <new tag> --squash
```
