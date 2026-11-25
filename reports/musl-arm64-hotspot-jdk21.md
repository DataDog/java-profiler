---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:07:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 37 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 23-24 cores)</summary>

```
1795618897 23
1795618902 23
1795618907 23
1795618912 23
1795618917 23
1795618922 23
1795618927 23
1795618932 23
1795618937 23
1795618942 23
1795618948 23
1795618953 23
1795618958 23
1795618963 24
1795618968 24
1795618973 23
1795618978 23
1795618983 23
1795618988 23
1795618993 23
```
</details>

---

