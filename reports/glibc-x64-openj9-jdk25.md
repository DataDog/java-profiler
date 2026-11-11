---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 16:04:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (4 unique values: 63-86 cores)</summary>

```
1794430832 86
1794430837 86
1794430842 86
1794430847 86
1794430852 86
1794430857 76
1794430862 76
1794430867 76
1794430872 76
1794430877 76
1794430882 76
1794430887 76
1794430892 76
1794430897 83
1794430902 83
1794430907 83
1794430912 83
1794430917 63
1794430922 63
1794430927 63
```
</details>

---

