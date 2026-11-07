---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-07 00:04:51 EST

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 9 |
| Allocations | 422 |

<details>
<summary>CPU Timeline (2 unique values: 13-15 cores)</summary>

```
1794027677 13
1794027682 13
1794027687 13
1794027692 13
1794027697 13
1794027702 13
1794027707 13
1794027712 15
1794027717 15
1794027722 15
1794027727 15
1794027732 15
1794027737 15
1794027742 15
1794027747 15
1794027752 15
1794027757 15
1794027762 15
1794027767 15
1794027772 15
```
</details>

---

