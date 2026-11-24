---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-24 13:05:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 382 |
| Sample Rate | 6.37/sec |
| Health Score | 398% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 40 |
| Sample Rate | 0.67/sec |
| Health Score | 42% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 17-33 cores)</summary>

```
1795543290 17
1795543295 17
1795543300 17
1795543305 33
1795543310 33
1795543315 33
1795543320 33
1795543325 33
1795543330 33
1795543335 33
1795543340 33
1795543345 33
1795543350 33
1795543355 33
1795543360 33
1795543365 33
1795543370 33
1795543375 33
1795543380 33
1795543386 33
```
</details>

---

