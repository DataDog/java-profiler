---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 12:37:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 44-52 cores)</summary>

```
1794850093 52
1794850098 52
1794850103 52
1794850108 52
1794850113 52
1794850118 52
1794850123 44
1794850128 44
1794850133 44
1794850138 44
1794850143 44
1794850148 44
1794850153 44
1794850158 44
1794850163 44
1794850168 44
1794850173 44
1794850178 44
1794850183 46
1794850188 46
```
</details>

---

