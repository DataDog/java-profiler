---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:08:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 311 |
| Sample Rate | 5.18/sec |
| Health Score | 324% |
| Threads | 11 |
| Allocations | 161 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 84 |

<details>
<summary>CPU Timeline (2 unique values: 37-43 cores)</summary>

```
1795618908 43
1795618913 43
1795618918 43
1795618923 43
1795618928 43
1795618933 43
1795618938 43
1795618943 43
1795618948 43
1795618953 43
1795618958 43
1795618963 43
1795618968 43
1795618973 43
1795618978 43
1795618983 43
1795618988 43
1795618993 37
1795618998 37
1795619003 37
```
</details>

---

