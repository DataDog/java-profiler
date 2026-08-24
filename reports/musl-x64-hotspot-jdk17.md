---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-23 21:24:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 848 |
| Sample Rate | 14.13/sec |
| Health Score | 883% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 65-73 cores)</summary>

```
1787534389 65
1787534394 65
1787534399 65
1787534404 65
1787534409 65
1787534414 65
1787534419 65
1787534424 65
1787534429 73
1787534434 73
1787534439 73
1787534444 73
1787534449 73
1787534454 73
1787534459 73
1787534464 73
1787534469 73
1787534474 73
1787534479 73
1787534484 73
```
</details>

---

