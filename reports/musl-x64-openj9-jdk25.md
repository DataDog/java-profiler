---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 10:22:23 EST

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (7 unique values: 77-92 cores)</summary>

```
1794323811 88
1794323816 90
1794323821 90
1794323826 92
1794323831 92
1794323836 92
1794323841 89
1794323846 89
1794323851 89
1794323856 89
1794323861 89
1794323866 89
1794323871 89
1794323876 87
1794323881 87
1794323886 89
1794323891 89
1794323896 80
1794323901 80
1794323906 80
```
</details>

---

