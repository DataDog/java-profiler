---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-04 09:27:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 10 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1006 |
| Sample Rate | 16.77/sec |
| Health Score | 1048% |
| Threads | 13 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (5 unique values: 58-73 cores)</summary>

```
1770214904 73
1770214909 73
1770214914 73
1770214919 58
1770214924 58
1770214929 60
1770214934 60
1770214939 60
1770214944 60
1770214949 60
1770214954 62
1770214959 62
1770214964 62
1770214969 62
1770214974 62
1770214979 62
1770214984 62
1770214989 64
1770214994 64
1770214999 64
```
</details>

---

