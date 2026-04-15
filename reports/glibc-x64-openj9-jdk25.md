---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-15 14:59:47 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (5 unique values: 49-69 cores)</summary>

```
1776279117 55
1776279122 69
1776279127 69
1776279132 49
1776279137 49
1776279142 49
1776279147 49
1776279152 49
1776279157 49
1776279162 49
1776279167 49
1776279172 49
1776279177 49
1776279182 49
1776279187 49
1776279192 49
1776279197 54
1776279202 54
1776279207 54
1776279212 54
```
</details>

---

