---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:20:50 EST

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 22 |
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
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 5 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 22-34 cores)</summary>

```
1795641355 22
1795641360 22
1795641365 22
1795641370 22
1795641375 22
1795641380 22
1795641385 22
1795641390 22
1795641395 22
1795641400 22
1795641405 22
1795641410 22
1795641415 22
1795641420 22
1795641425 22
1795641430 22
1795641435 22
1795641440 34
1795641445 34
1795641450 34
```
</details>

---

