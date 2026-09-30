---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-30 00:57:58 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 978 |
| Sample Rate | 16.30/sec |
| Health Score | 1019% |
| Threads | 12 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 62-79 cores)</summary>

```
1790744049 62
1790744054 62
1790744059 62
1790744064 62
1790744069 62
1790744074 62
1790744079 62
1790744084 62
1790744089 62
1790744094 79
1790744099 79
1790744104 79
1790744109 79
1790744114 79
1790744119 79
1790744124 79
1790744129 79
1790744134 79
1790744139 79
1790744144 79
```
</details>

---

