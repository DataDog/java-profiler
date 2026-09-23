---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-23 11:28:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 875 |
| Sample Rate | 14.58/sec |
| Health Score | 911% |
| Threads | 12 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (5 unique values: 67-72 cores)</summary>

```
1790176963 72
1790176968 72
1790176973 72
1790176978 72
1790176983 71
1790176988 71
1790176993 71
1790176998 71
1790177003 71
1790177008 71
1790177013 67
1790177018 67
1790177023 67
1790177028 67
1790177033 67
1790177038 68
1790177043 68
1790177048 68
1790177053 68
1790177058 70
```
</details>

---

