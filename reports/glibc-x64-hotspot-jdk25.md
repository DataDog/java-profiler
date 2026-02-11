---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-11 11:04:57 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 10 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 994 |
| Sample Rate | 16.57/sec |
| Health Score | 1036% |
| Threads | 12 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1770825561 32
1770825566 32
1770825571 32
1770825576 32
1770825581 32
1770825586 32
1770825591 32
1770825596 31
1770825601 31
1770825606 31
1770825611 32
1770825616 32
1770825621 32
1770825626 32
1770825631 32
1770825636 32
1770825641 31
1770825646 31
1770825651 31
1770825656 31
```
</details>

---

