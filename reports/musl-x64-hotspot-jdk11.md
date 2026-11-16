---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 12:37:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 796 |
| Sample Rate | 13.27/sec |
| Health Score | 829% |
| Threads | 9 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (3 unique values: 83-85 cores)</summary>

```
1794850062 83
1794850068 83
1794850073 83
1794850078 83
1794850083 83
1794850088 83
1794850093 83
1794850098 85
1794850103 85
1794850108 85
1794850113 85
1794850118 85
1794850123 85
1794850128 85
1794850133 85
1794850138 85
1794850143 85
1794850148 85
1794850153 85
1794850158 85
```
</details>

---

