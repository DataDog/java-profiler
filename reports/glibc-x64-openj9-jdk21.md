---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-27 13:58:50 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (4 unique values: 75-85 cores)</summary>

```
1793123657 77
1793123662 77
1793123667 77
1793123672 75
1793123677 75
1793123682 75
1793123687 77
1793123692 77
1793123697 79
1793123702 79
1793123707 85
1793123712 85
1793123717 85
1793123722 85
1793123727 85
1793123732 85
1793123737 85
1793123742 85
1793123747 85
1793123752 85
```
</details>

---

