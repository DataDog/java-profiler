---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-02 12:55:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 379 |
| Sample Rate | 6.32/sec |
| Health Score | 395% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 8 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 12-29 cores)</summary>

```
1770054592 15
1770054597 12
1770054602 12
1770054607 12
1770054612 12
1770054617 12
1770054622 12
1770054627 12
1770054632 12
1770054637 12
1770054642 12
1770054647 12
1770054652 12
1770054657 29
1770054662 29
1770054667 29
1770054672 29
1770054677 29
1770054682 29
1770054687 29
```
</details>

---

