---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 13:14:50 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (3 unique values: 29-55 cores)</summary>

```
1790096978 31
1790096983 31
1790096988 31
1790096993 29
1790096998 29
1790097003 29
1790097008 29
1790097013 31
1790097018 31
1790097023 31
1790097028 31
1790097033 31
1790097038 31
1790097043 31
1790097048 31
1790097053 31
1790097058 31
1790097063 31
1790097068 31
1790097073 31
```
</details>

---

