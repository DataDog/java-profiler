---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-07 12:48:06 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (4 unique values: 33-48 cores)</summary>

```
1791391394 48
1791391399 48
1791391404 48
1791391409 43
1791391414 43
1791391419 43
1791391424 43
1791391429 43
1791391434 43
1791391439 43
1791391444 43
1791391449 43
1791391454 43
1791391459 43
1791391464 43
1791391469 43
1791391474 43
1791391479 38
1791391484 38
1791391489 38
```
</details>

---

