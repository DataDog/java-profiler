---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-12 06:45:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 434 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 11 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (3 unique values: 77-88 cores)</summary>

```
1778582452 79
1778582457 79
1778582462 79
1778582467 77
1778582472 77
1778582477 77
1778582482 77
1778582487 77
1778582492 77
1778582497 77
1778582502 77
1778582507 79
1778582512 79
1778582517 79
1778582522 79
1778582527 79
1778582532 79
1778582537 79
1778582542 79
1778582547 79
```
</details>

---

