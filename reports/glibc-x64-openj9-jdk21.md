---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 05:09:42 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (5 unique values: 40-94 cores)</summary>

```
1795082662 71
1795082667 71
1795082672 71
1795082677 71
1795082682 71
1795082687 71
1795082692 71
1795082697 71
1795082702 71
1795082707 71
1795082712 92
1795082717 92
1795082722 92
1795082727 92
1795082732 94
1795082737 94
1795082742 94
1795082747 94
1795082752 66
1795082757 66
```
</details>

---

