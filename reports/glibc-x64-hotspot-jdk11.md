---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 12:24:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (4 unique values: 83-89 cores)</summary>

```
1794590369 85
1794590374 85
1794590379 85
1794590384 85
1794590389 85
1794590394 85
1794590399 85
1794590404 85
1794590409 85
1794590414 85
1794590419 85
1794590424 85
1794590429 85
1794590434 85
1794590439 83
1794590444 83
1794590449 83
1794590454 83
1794590459 87
1794590464 87
```
</details>

---

