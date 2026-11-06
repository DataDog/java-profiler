---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-05 19:52:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 10 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (3 unique values: 35-55 cores)</summary>

```
1793926083 53
1793926088 53
1793926093 53
1793926098 53
1793926103 53
1793926108 53
1793926113 53
1793926118 53
1793926123 53
1793926128 53
1793926133 55
1793926138 55
1793926143 55
1793926148 55
1793926153 55
1793926158 55
1793926163 55
1793926168 55
1793926173 55
1793926178 55
```
</details>

---

