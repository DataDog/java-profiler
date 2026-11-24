---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 09:14:31 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 330 |
| Sample Rate | 5.50/sec |
| Health Score | 344% |
| Threads | 10 |
| Allocations | 185 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 48-64 cores)</summary>

```
1795529413 48
1795529419 48
1795529424 48
1795529429 48
1795529434 48
1795529439 64
1795529444 64
1795529449 64
1795529454 64
1795529459 64
1795529464 64
1795529469 64
1795529474 64
1795529479 64
1795529484 64
1795529489 64
1795529494 64
1795529499 64
1795529504 64
1795529509 64
```
</details>

---

