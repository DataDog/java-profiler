---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 07:04:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 7 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 12 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (4 unique values: 43-64 cores)</summary>

```
1795175966 61
1795175971 61
1795175976 61
1795175981 61
1795175986 61
1795175991 61
1795175996 61
1795176001 61
1795176006 61
1795176011 64
1795176016 64
1795176021 64
1795176026 64
1795176031 44
1795176036 44
1795176041 44
1795176046 44
1795176051 44
1795176056 44
1795176061 44
```
</details>

---

