# Custom Label ABI (v1)

## Description

A **label** is a pair of key and value, each of which is an arbitrary array of bytes.

A **label set** is a set of labels, where all the keys are unique.

This document describes a mechanism for threads to declare a particular label set to be active at a particular time, in such a way that an external program that is able to read the thread's memory while it is interrupted will be able to read the set.

## Supported platforms

The process must be running on Linux on an x86-64 or aarch64 system. 

## Exposed symbols

Two pieces of data must be exposed by the process; they are described in detail below. The component that defines this data must be an ELF binary loaded on startup by the process (that is, either the main executable or a dynamically linked library in the initial set loaded on startup).

If the binary is a dynamically linked library, its filename must match the following regular expression: `libcustomlabels.*\.so$|customlabels\.node$`.

## `custom_labels_abi_version`

The binary must export a dynamic symbol called `custom_labels_abi_version`. It must be have a size of 4 bytes and have the constant value `1`.

## `custom_labels_current_set`

The binary must export a dynamic symbol called `custom_labels_current_set`.

If the binary is the main executable, the object must be accessible from the statically known offset from the thread pointer described in ["ELF Handing For Thread-Local Storage"](https://www.akkadia.org/drepper/tls.pdf) (variant I for aarch64; variant II for x86-64).

**Note**: This should be the default behavior; no special compiler flags are needed.

Otherwise, if the binary is a dynamically linked library, the data this symbol references must be accessible via a relocation of type `R_X86_64_TLSDESC` or `R_AARCH64_TLSDESC`, depending on the architecture.

**Note**: If the library is compiled using gcc, this can be achieved by annotating the
object's definition with `__thread` and building it as follows on x86-64:

``` shell
gcc -ftls-model=global-dynamic -mtls-dialect=gnu2 -fPIC -shared -o libcustomlabels.so customlabels.c
```

or as follows on aarch64:

``` shell
gcc -ftls-model=global-dynamic -mtls-dialect=desc -fPIC -shared -o libcustomlabels.so customlabels.c
```

The object referenced by this symbol must be a pointer to a structure that has the layout of `custom_labels_labelset_t`, defined as follows:

``` c
typedef struct {
        size_t len;
        const unsigned char *buf;
} custom_labels_string_t;

typedef struct {
        custom_labels_string_t key;
        custom_labels_string_t value;
} custom_labels_label_t;

typedef struct {
        custom_labels_label_t *storage;
        size_t count;
        size_t capacity;
} custom_labels_labelset_t;
```

## Interpretation of data

As already stated, `custom_labels_abi_version` has the constant value `1`. If it has any other value, nothing in this document applies. 

While a the thread is suspended, the external program may determine its active label set by reading the data pointed to by `custom_labels_current_set` according to the following principles.

* `custom_labels_string_t`: if `buf` is null, this represents the absence of a value. Otherwise, `buf` points to an array of bytes of size `len`.
* `custom_labels_label_t`: if `key.buf` represents the absence of a value (that is, if `key.buf` is null), this object is ignored. `val.buf` must never be null. Otherwise, this represents a label whose key is `key` and whose value is `value`.
* `custom_labels_labelset_t`: `storage` points to an array of possible labels of length `count`. As described above, an element of `storage` whose key is absent is ignored. An element is also ignored if its key is identical to an element that appears earlier in the array. Thus `custom_labels_labelset_t` represents a label set where uniqueness of keys is guaranteed by taking the first label for any given key. The value of `capacity` is used internally by the library and has no meaning to profilers.

**Note**: Label sets are indeed mathematical _sets_; that is, they are unordered. Thus order of the objects in `tls_t::storage` has no meaning except for disambiguation of keys as described above.
