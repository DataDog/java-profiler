---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-29 08:48:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 85 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1793277859 48
1793277864 48
1793277869 48
1793277874 48
1793277879 48
1793277884 48
1793277889 46
1793277894 46
1793277899 46
1793277904 46
1793277909 46
1793277914 46
1793277919 46
1793277924 46
1793277929 46
1793277934 46
1793277939 46
1793277944 46
1793277949 46
1793277954 46
```
</details>

---

