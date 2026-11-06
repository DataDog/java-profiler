---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-06 16:43:55 EST

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
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1794001117 96
1794001122 96
1794001127 96
1794001132 96
1794001137 96
1794001142 96
1794001147 96
1794001152 94
1794001157 94
1794001162 94
1794001167 94
1794001172 94
1794001177 94
1794001182 94
1794001187 94
1794001192 94
1794001197 94
1794001202 94
1794001207 94
1794001212 94
```
</details>

---

