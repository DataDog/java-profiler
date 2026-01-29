---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-01-29 09:48:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 217 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 15.13/sec |
| Health Score | 946% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (7 unique values: 44-63 cores)</summary>

```
1769697755 53
1769697760 53
1769697765 53
1769697770 53
1769697775 47
1769697780 47
1769697785 47
1769697790 47
1769697795 47
1769697800 44
1769697805 44
1769697810 44
1769697815 46
1769697820 46
1769697825 51
1769697830 51
1769697835 51
1769697840 51
1769697845 51
1769697850 51
```
</details>

---

