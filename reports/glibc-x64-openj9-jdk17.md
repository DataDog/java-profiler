---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 11:09:34 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 11 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (3 unique values: 70-96 cores)</summary>

```
1790262028 70
1790262033 72
1790262038 72
1790262043 72
1790262048 72
1790262053 70
1790262058 70
1790262063 70
1790262068 70
1790262073 70
1790262078 70
1790262083 70
1790262088 70
1790262093 70
1790262098 70
1790262103 72
1790262108 72
1790262113 72
1790262118 72
1790262123 72
```
</details>

---

