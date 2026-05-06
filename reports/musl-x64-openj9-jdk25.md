---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-06 14:10:47 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 55 |
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
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (5 unique values: 46-66 cores)</summary>

```
1778090765 66
1778090770 66
1778090775 66
1778090780 66
1778090785 66
1778090790 46
1778090795 46
1778090800 46
1778090805 46
1778090810 48
1778090815 48
1778090820 48
1778090825 48
1778090830 48
1778090835 48
1778090840 48
1778090845 50
1778090850 50
1778090855 50
1778090860 50
```
</details>

---

