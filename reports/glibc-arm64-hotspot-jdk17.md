---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-28 14:12:54 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 10 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 45-64 cores)</summary>

```
1790618908 45
1790618913 45
1790618918 45
1790618923 45
1790618928 45
1790618933 45
1790618938 45
1790618943 45
1790618948 45
1790618953 45
1790618958 45
1790618963 64
1790618968 64
1790618973 64
1790618978 64
1790618983 64
1790618988 64
1790618993 64
1790618998 64
1790619003 64
```
</details>

---

