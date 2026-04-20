---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-20 07:58:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1010 |
| Sample Rate | 16.83/sec |
| Health Score | 1052% |
| Threads | 11 |
| Allocations | 423 |

<details>
<summary>CPU Timeline (2 unique values: 66-70 cores)</summary>

```
1776686029 70
1776686034 70
1776686039 70
1776686044 70
1776686049 70
1776686054 70
1776686059 70
1776686064 66
1776686069 66
1776686074 66
1776686079 66
1776686084 66
1776686089 66
1776686095 66
1776686100 66
1776686105 66
1776686110 66
1776686115 66
1776686120 66
1776686125 66
```
</details>

---

