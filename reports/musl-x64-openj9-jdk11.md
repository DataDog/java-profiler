---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-09 06:07:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 989 |
| Sample Rate | 16.48/sec |
| Health Score | 1030% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 85-90 cores)</summary>

```
1791540099 90
1791540104 90
1791540109 90
1791540114 90
1791540119 90
1791540124 90
1791540129 90
1791540134 90
1791540139 90
1791540144 85
1791540149 85
1791540154 85
1791540159 85
1791540164 85
1791540169 88
1791540175 88
1791540180 88
1791540185 88
1791540190 88
1791540195 88
```
</details>

---

