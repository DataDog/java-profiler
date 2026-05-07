---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 13:17:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 12 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (4 unique values: 66-92 cores)</summary>

```
1778173865 92
1778173870 92
1778173875 92
1778173880 92
1778173885 92
1778173890 92
1778173895 92
1778173900 66
1778173905 66
1778173910 66
1778173915 66
1778173920 68
1778173925 68
1778173930 68
1778173935 68
1778173940 68
1778173945 68
1778173950 68
1778173955 68
1778173960 68
```
</details>

---

