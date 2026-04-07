---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-07 12:54:31 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 10 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (6 unique values: 80-95 cores)</summary>

```
1775580516 80
1775580521 80
1775580526 80
1775580531 80
1775580536 84
1775580541 84
1775580546 94
1775580551 94
1775580556 94
1775580561 94
1775580566 94
1775580571 94
1775580576 94
1775580581 94
1775580586 94
1775580591 94
1775580596 94
1775580601 94
1775580606 94
1775580611 93
```
</details>

---

