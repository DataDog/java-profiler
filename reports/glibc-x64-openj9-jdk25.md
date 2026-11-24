---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 09:14:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (4 unique values: 60-69 cores)</summary>

```
1795529345 69
1795529350 69
1795529355 69
1795529360 61
1795529365 61
1795529370 62
1795529375 62
1795529380 60
1795529385 60
1795529390 60
1795529395 60
1795529400 60
1795529405 60
1795529410 60
1795529415 60
1795529420 60
1795529425 60
1795529430 60
1795529435 60
1795529440 60
```
</details>

---

