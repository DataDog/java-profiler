---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 11:09:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 12.90/sec |
| Health Score | 806% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (4 unique values: 78-81 cores)</summary>

```
1790262028 80
1790262033 80
1790262038 80
1790262043 80
1790262048 80
1790262053 78
1790262058 78
1790262063 78
1790262068 78
1790262073 78
1790262078 78
1790262083 78
1790262088 78
1790262093 78
1790262098 79
1790262103 79
1790262108 81
1790262113 81
1790262118 81
1790262123 81
```
</details>

---

