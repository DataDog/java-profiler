---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 04:53:58 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1794390429 47
1794390434 47
1794390439 47
1794390444 48
1794390449 48
1794390454 48
1794390459 48
1794390464 48
1794390469 48
1794390474 48
1794390479 48
1794390484 48
1794390489 48
1794390494 48
1794390499 48
1794390504 48
1794390509 48
1794390514 48
1794390519 48
1794390524 48
```
</details>

---

