---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-10 06:26:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (5 unique values: 48-91 cores)</summary>

```
1786357290 81
1786357295 81
1786357300 81
1786357305 81
1786357310 83
1786357315 83
1786357320 83
1786357325 83
1786357330 83
1786357335 83
1786357340 91
1786357345 91
1786357350 91
1786357355 91
1786357360 91
1786357365 91
1786357370 91
1786357375 91
1786357380 48
1786357385 48
```
</details>

---

