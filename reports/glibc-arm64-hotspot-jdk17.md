---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 10:07:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 14 |
| Allocations | 101 |

<details>
<summary>CPU Timeline (3 unique values: 43-60 cores)</summary>

```
1795618948 47
1795618953 47
1795618958 47
1795618963 47
1795618968 47
1795618973 47
1795618978 47
1795618983 47
1795618988 47
1795618993 43
1795618998 43
1795619003 43
1795619008 43
1795619013 43
1795619018 43
1795619023 43
1795619028 43
1795619033 43
1795619038 43
1795619043 43
```
</details>

---

