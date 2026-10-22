---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 13:25:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 9 |
| Allocations | 429 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 11 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (3 unique values: 89-96 cores)</summary>

```
1792689606 96
1792689611 96
1792689616 91
1792689621 91
1792689626 91
1792689631 91
1792689636 91
1792689641 91
1792689646 91
1792689651 91
1792689656 91
1792689661 91
1792689666 91
1792689671 91
1792689676 91
1792689681 91
1792689686 91
1792689691 91
1792689696 91
1792689701 91
```
</details>

---

