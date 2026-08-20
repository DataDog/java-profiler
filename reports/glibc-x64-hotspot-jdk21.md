---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-20 08:51:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 804 |
| Sample Rate | 13.40/sec |
| Health Score | 838% |
| Threads | 10 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1787229957 81
1787229962 81
1787229967 79
1787229972 79
1787229977 79
1787229982 79
1787229987 79
1787229992 79
1787229997 79
1787230002 79
1787230007 79
1787230012 79
1787230017 79
1787230022 79
1787230027 79
1787230032 79
1787230037 79
1787230042 79
1787230047 79
1787230052 79
```
</details>

---

