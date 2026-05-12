---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-12 06:45:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 8 |
| Allocations | 426 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 8 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 25-44 cores)</summary>

```
1778582447 25
1778582452 25
1778582457 25
1778582462 25
1778582467 25
1778582472 25
1778582477 25
1778582482 25
1778582487 25
1778582492 25
1778582497 25
1778582502 25
1778582507 25
1778582512 25
1778582517 25
1778582522 25
1778582527 25
1778582532 25
1778582537 44
1778582542 44
```
</details>

---

