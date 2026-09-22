---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 12:28:35 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 837 |
| Sample Rate | 13.95/sec |
| Health Score | 872% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 73-75 cores)</summary>

```
1790094069 73
1790094074 73
1790094079 73
1790094084 73
1790094089 73
1790094094 73
1790094099 73
1790094104 73
1790094109 73
1790094114 73
1790094119 73
1790094124 75
1790094129 75
1790094134 75
1790094139 75
1790094144 75
1790094149 75
1790094154 75
1790094159 75
1790094164 75
```
</details>

---

