---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-12 20:17:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 11 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (2 unique values: 33-41 cores)</summary>

```
1786580007 33
1786580012 33
1786580017 33
1786580022 33
1786580027 41
1786580032 41
1786580037 41
1786580042 41
1786580047 41
1786580052 41
1786580057 41
1786580062 41
1786580067 41
1786580073 41
1786580078 41
1786580083 41
1786580088 41
1786580093 41
1786580098 41
1786580103 41
```
</details>

---

