---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-09 06:38:28 EDT

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 393 |
| Sample Rate | 6.55/sec |
| Health Score | 409% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1791541865 15
1791541870 15
1791541875 15
1791541880 15
1791541885 15
1791541890 15
1791541895 15
1791541900 15
1791541905 15
1791541910 15
1791541915 17
1791541920 17
1791541925 17
1791541930 17
1791541935 17
1791541940 17
1791541945 17
1791541950 17
1791541955 17
1791541960 17
```
</details>

---

