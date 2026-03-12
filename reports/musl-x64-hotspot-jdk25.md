---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-12 10:34:46 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 433 |
| Sample Rate | 7.22/sec |
| Health Score | 451% |
| Threads | 11 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 13 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (4 unique values: 44-51 cores)</summary>

```
1773325704 49
1773325709 49
1773325714 49
1773325719 44
1773325724 44
1773325729 44
1773325734 44
1773325739 44
1773325744 44
1773325749 48
1773325754 48
1773325759 48
1773325764 48
1773325769 48
1773325774 48
1773325779 51
1773325784 51
1773325789 51
1773325794 51
1773325799 51
```
</details>

---

