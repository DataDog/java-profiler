---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-12 04:18:22 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 10 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (2 unique values: 50-52 cores)</summary>

```
1786522404 50
1786522409 50
1786522414 50
1786522419 50
1786522424 50
1786522429 50
1786522434 52
1786522439 52
1786522444 52
1786522449 52
1786522454 52
1786522459 52
1786522464 52
1786522469 52
1786522474 52
1786522479 52
1786522484 52
1786522489 52
1786522494 52
1786522499 52
```
</details>

---

