---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:08:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
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
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795618918 64
1795618923 64
1795618928 64
1795618933 64
1795618938 64
1795618943 64
1795618948 64
1795618953 64
1795618958 64
1795618963 64
1795618968 64
1795618973 64
1795618978 64
1795618983 64
1795618988 64
1795618993 64
1795618998 64
1795619003 64
1795619008 64
1795619013 64
```
</details>

---

