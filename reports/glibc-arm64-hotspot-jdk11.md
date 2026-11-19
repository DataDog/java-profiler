---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 05:46:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 13 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 9-29 cores)</summary>

```
1795084988 9
1795084993 9
1795084998 9
1795085003 9
1795085008 9
1795085013 9
1795085018 9
1795085023 9
1795085028 9
1795085033 9
1795085038 9
1795085043 9
1795085048 9
1795085053 9
1795085058 9
1795085063 9
1795085068 9
1795085073 9
1795085078 9
1795085083 29
```
</details>

---

