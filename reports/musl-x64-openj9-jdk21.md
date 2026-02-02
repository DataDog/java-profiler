---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-02 12:55:23 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 10 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (4 unique values: 35-59 cores)</summary>

```
1770054597 41
1770054602 41
1770054607 41
1770054612 41
1770054617 49
1770054622 49
1770054627 49
1770054632 49
1770054637 49
1770054642 49
1770054647 49
1770054652 49
1770054657 59
1770054662 59
1770054667 59
1770054672 59
1770054677 59
1770054682 59
1770054687 35
1770054692 35
```
</details>

---

