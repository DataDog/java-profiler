---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 07:19:38 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (7 unique values: 71-89 cores)</summary>

```
1795004183 78
1795004188 78
1795004193 76
1795004198 76
1795004203 76
1795004208 73
1795004213 73
1795004218 71
1795004223 71
1795004228 80
1795004233 80
1795004238 84
1795004243 84
1795004248 84
1795004253 84
1795004258 84
1795004263 84
1795004268 84
1795004273 84
1795004278 84
```
</details>

---

