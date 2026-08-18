---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-18 13:40:55 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 80-88 cores)</summary>

```
1787074512 80
1787074517 80
1787074522 80
1787074527 80
1787074532 80
1787074537 80
1787074542 80
1787074547 80
1787074552 80
1787074558 80
1787074563 80
1787074568 80
1787074573 80
1787074578 80
1787074583 80
1787074588 80
1787074593 80
1787074598 80
1787074603 88
1787074608 88
```
</details>

---

