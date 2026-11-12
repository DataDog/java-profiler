---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:08:07 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 152 |
| Sample Rate | 2.53/sec |
| Health Score | 158% |
| Threads | 13 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 8 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (3 unique values: 90-96 cores)</summary>

```
1794506558 90
1794506563 90
1794506568 90
1794506573 90
1794506578 90
1794506583 90
1794506588 90
1794506593 90
1794506598 90
1794506603 90
1794506608 90
1794506613 90
1794506618 90
1794506623 90
1794506628 90
1794506633 90
1794506638 94
1794506643 94
1794506648 94
1794506653 94
```
</details>

---

