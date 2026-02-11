---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-11 11:04:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 3 |
| CPU Cores (end) | 4 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 8 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (3 unique values: 3-7 cores)</summary>

```
1770825557 3
1770825562 3
1770825567 3
1770825572 3
1770825577 3
1770825582 3
1770825587 3
1770825592 3
1770825597 3
1770825602 3
1770825607 7
1770825612 7
1770825617 4
1770825622 4
1770825627 4
1770825632 4
1770825637 4
1770825642 4
1770825647 4
1770825652 4
```
</details>

---

