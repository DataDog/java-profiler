---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 12:09:44 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 12.92/sec |
| Health Score | 807% |
| Threads | 9 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1776701054 96
1776701059 96
1776701064 96
1776701069 96
1776701074 96
1776701079 96
1776701084 96
1776701089 96
1776701094 94
1776701099 94
1776701104 94
1776701109 94
1776701114 94
1776701119 94
1776701124 94
1776701129 94
1776701134 94
1776701139 94
1776701144 94
1776701149 94
```
</details>

---

