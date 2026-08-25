---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-25 05:49:23 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 11 |
| Allocations | 424 |

<details>
<summary>CPU Timeline (5 unique values: 86-96 cores)</summary>

```
1787651017 86
1787651023 86
1787651028 86
1787651033 86
1787651038 86
1787651043 86
1787651048 86
1787651053 86
1787651058 86
1787651063 88
1787651068 88
1787651073 88
1787651078 88
1787651083 92
1787651088 92
1787651093 94
1787651098 94
1787651103 94
1787651108 94
1787651113 96
```
</details>

---

