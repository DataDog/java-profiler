---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 07:26:17 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 780 |
| Sample Rate | 13.00/sec |
| Health Score | 812% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (3 unique values: 58-75 cores)</summary>

```
1794572477 58
1794572482 60
1794572487 60
1794572492 58
1794572497 58
1794572502 58
1794572507 58
1794572512 58
1794572517 58
1794572522 58
1794572527 58
1794572532 58
1794572537 75
1794572542 75
1794572547 75
1794572552 75
1794572557 75
1794572562 75
1794572567 75
1794572572 75
```
</details>

---

