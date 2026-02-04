---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-04 09:27:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 11 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 12 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1770214899 29
1770214904 29
1770214909 32
1770214914 32
1770214919 32
1770214924 32
1770214929 32
1770214934 32
1770214939 32
1770214944 32
1770214949 32
1770214954 32
1770214959 32
1770214964 32
1770214969 32
1770214974 32
1770214979 32
1770214984 32
1770214989 32
1770214994 32
```
</details>

---

