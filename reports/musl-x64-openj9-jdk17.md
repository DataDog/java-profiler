---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 07:40:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (4 unique values: 74-79 cores)</summary>

```
1794918830 77
1794918835 75
1794918840 75
1794918845 75
1794918850 75
1794918855 77
1794918860 77
1794918865 79
1794918870 79
1794918875 79
1794918880 79
1794918885 79
1794918890 79
1794918895 79
1794918900 79
1794918905 79
1794918910 79
1794918915 79
1794918920 79
1794918925 79
```
</details>

---

