---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-10 20:17:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 21 |
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
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 12 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 19-21 cores)</summary>

```
1786407088 19
1786407093 19
1786407098 19
1786407103 19
1786407108 19
1786407113 19
1786407118 19
1786407123 19
1786407128 19
1786407133 19
1786407138 21
1786407143 21
1786407148 21
1786407153 21
1786407158 21
1786407163 21
1786407168 21
1786407173 21
1786407178 21
1786407183 21
```
</details>

---

