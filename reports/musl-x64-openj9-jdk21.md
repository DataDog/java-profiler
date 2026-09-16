---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-16 12:13:03 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (6 unique values: 50-77 cores)</summary>

```
1789574769 50
1789574774 50
1789574779 50
1789574784 50
1789574789 73
1789574794 73
1789574799 73
1789574804 73
1789574809 73
1789574814 77
1789574819 77
1789574824 77
1789574829 77
1789574834 75
1789574839 75
1789574844 75
1789574849 75
1789574854 75
1789574859 75
1789574864 58
```
</details>

---

