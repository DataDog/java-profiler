---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-15 05:47:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 225 |
| Sample Rate | 3.75/sec |
| Health Score | 234% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 30-81 cores)</summary>

```
1786786963 30
1786786968 30
1786786973 30
1786786978 30
1786786983 30
1786786988 30
1786786993 30
1786786998 30
1786787003 30
1786787008 30
1786787013 30
1786787018 30
1786787023 30
1786787028 30
1786787033 30
1786787038 30
1786787043 81
1786787048 81
1786787053 81
1786787058 81
```
</details>

---

