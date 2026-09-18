---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 05:26:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (6 unique values: 23-37 cores)</summary>

```
1789723347 23
1789723352 23
1789723357 23
1789723362 23
1789723367 23
1789723372 23
1789723377 33
1789723382 33
1789723387 31
1789723392 31
1789723397 31
1789723402 31
1789723407 34
1789723412 34
1789723417 34
1789723422 34
1789723427 34
1789723432 34
1789723437 34
1789723442 34
```
</details>

---

