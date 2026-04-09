---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-09 11:18:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 10 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (5 unique values: 50-54 cores)</summary>

```
1775747642 52
1775747647 52
1775747652 54
1775747657 54
1775747662 54
1775747667 54
1775747672 51
1775747677 51
1775747682 51
1775747687 51
1775747692 51
1775747697 51
1775747702 51
1775747707 51
1775747712 51
1775747717 51
1775747722 53
1775747727 53
1775747732 53
1775747737 51
```
</details>

---

