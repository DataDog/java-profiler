---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 09:24:14 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 9 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (4 unique values: 66-73 cores)</summary>

```
1795184328 68
1795184333 68
1795184338 68
1795184343 68
1795184348 66
1795184353 66
1795184358 66
1795184363 66
1795184368 66
1795184373 68
1795184378 68
1795184383 68
1795184388 68
1795184393 68
1795184398 68
1795184403 68
1795184408 68
1795184413 70
1795184418 70
1795184423 70
```
</details>

---

