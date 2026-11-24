---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-24 11:29:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (5 unique values: 82-88 cores)</summary>

```
1795537492 82
1795537497 82
1795537502 84
1795537507 84
1795537512 84
1795537517 84
1795537522 84
1795537527 84
1795537532 84
1795537537 85
1795537542 85
1795537547 85
1795537552 85
1795537557 85
1795537562 85
1795537567 85
1795537572 85
1795537577 85
1795537582 85
1795537587 88
```
</details>

---

