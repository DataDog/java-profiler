---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-06 16:43:55 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 77-96 cores)</summary>

```
1794001128 77
1794001133 77
1794001138 77
1794001143 77
1794001148 77
1794001153 94
1794001158 94
1794001163 94
1794001168 94
1794001173 94
1794001178 94
1794001183 94
1794001188 94
1794001193 94
1794001198 94
1794001203 94
1794001208 94
1794001213 94
1794001218 94
1794001223 96
```
</details>

---

