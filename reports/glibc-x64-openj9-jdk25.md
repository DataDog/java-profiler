---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-05 13:29:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 341 |
| Sample Rate | 5.68/sec |
| Health Score | 355% |
| Threads | 10 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 785 |
| Sample Rate | 13.08/sec |
| Health Score | 817% |
| Threads | 13 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (3 unique values: 53-60 cores)</summary>

```
1772734958 60
1772734963 60
1772734968 60
1772734973 60
1772734979 60
1772734984 57
1772734989 57
1772734994 57
1772734999 57
1772735004 57
1772735009 57
1772735014 53
1772735019 53
1772735024 57
1772735029 57
1772735034 57
1772735039 57
1772735044 57
1772735049 57
1772735054 57
```
</details>

---

