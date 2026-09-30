---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-30 00:57:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 418 |
| Sample Rate | 6.97/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 11 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1790744033 81
1790744038 81
1790744043 81
1790744048 81
1790744053 81
1790744058 81
1790744063 81
1790744068 81
1790744073 81
1790744078 79
1790744083 79
1790744088 79
1790744093 79
1790744098 79
1790744103 79
1790744108 79
1790744113 79
1790744118 79
1790744123 79
1790744128 79
```
</details>

---

