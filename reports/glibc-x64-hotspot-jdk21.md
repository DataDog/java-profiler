---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-13 11:08:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 839 |
| Sample Rate | 13.98/sec |
| Health Score | 874% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (4 unique values: 75-88 cores)</summary>

```
1778684514 75
1778684519 82
1778684524 82
1778684529 82
1778684534 82
1778684539 84
1778684544 84
1778684549 84
1778684554 84
1778684559 84
1778684564 84
1778684569 84
1778684574 84
1778684579 84
1778684584 84
1778684589 84
1778684594 84
1778684599 88
1778684604 88
1778684609 88
```
</details>

---

