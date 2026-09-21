---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 05:49:06 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 45-76 cores)</summary>

```
1789983840 76
1789983845 76
1789983850 76
1789983855 76
1789983860 76
1789983865 55
1789983870 55
1789983875 55
1789983880 55
1789983885 55
1789983890 55
1789983895 55
1789983900 55
1789983905 55
1789983910 55
1789983915 55
1789983920 55
1789983925 55
1789983930 55
1789983935 55
```
</details>

---

