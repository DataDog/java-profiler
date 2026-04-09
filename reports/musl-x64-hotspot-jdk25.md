---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-09 11:18:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 11 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (4 unique values: 48-60 cores)</summary>

```
1775747639 56
1775747644 56
1775747649 56
1775747654 56
1775747659 56
1775747664 56
1775747669 56
1775747674 56
1775747679 56
1775747684 56
1775747689 56
1775747694 60
1775747699 60
1775747704 48
1775747709 48
1775747714 48
1775747719 48
1775747724 48
1775747729 48
1775747734 48
```
</details>

---

