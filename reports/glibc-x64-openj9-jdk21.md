---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-12 05:20:31 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 44-49 cores)</summary>

```
1786526131 44
1786526136 44
1786526141 49
1786526146 49
1786526151 49
1786526156 49
1786526161 49
1786526166 49
1786526171 49
1786526176 49
1786526181 49
1786526186 49
1786526191 47
1786526196 47
1786526201 47
1786526206 47
1786526211 47
1786526216 47
1786526221 47
1786526226 47
```
</details>

---

