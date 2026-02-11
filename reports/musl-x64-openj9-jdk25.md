---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-11 11:04:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 11 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 789 |
| Sample Rate | 13.15/sec |
| Health Score | 822% |
| Threads | 13 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1770825552 64
1770825557 64
1770825562 64
1770825567 64
1770825572 64
1770825577 64
1770825582 64
1770825587 64
1770825592 64
1770825597 64
1770825602 64
1770825607 64
1770825612 62
1770825617 62
1770825622 62
1770825627 62
1770825632 62
1770825637 62
1770825642 62
1770825647 62
```
</details>

---

