---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-12 20:17:00 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 13 |
| Allocations | 81 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786580002 48
1786580007 48
1786580012 48
1786580017 48
1786580022 48
1786580027 48
1786580032 48
1786580037 48
1786580042 48
1786580047 48
1786580052 43
1786580057 43
1786580062 43
1786580067 43
1786580072 43
1786580077 43
1786580082 43
1786580087 43
1786580092 43
1786580097 43
```
</details>

---

