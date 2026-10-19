---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-19 01:06:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (4 unique values: 65-81 cores)</summary>

```
1792386069 65
1792386074 65
1792386079 65
1792386084 65
1792386089 65
1792386094 65
1792386099 65
1792386104 68
1792386109 68
1792386114 68
1792386119 68
1792386124 68
1792386129 73
1792386134 73
1792386139 73
1792386144 73
1792386149 73
1792386154 73
1792386159 73
1792386164 73
```
</details>

---

