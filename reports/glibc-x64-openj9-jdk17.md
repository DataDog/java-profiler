---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 09:24:14 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 11 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (3 unique values: 38-68 cores)</summary>

```
1795184333 38
1795184338 38
1795184343 38
1795184348 38
1795184353 38
1795184358 66
1795184363 66
1795184368 66
1795184373 66
1795184378 66
1795184383 66
1795184388 66
1795184393 66
1795184398 68
1795184403 68
1795184408 68
1795184413 68
1795184418 68
1795184423 68
1795184428 68
```
</details>

---

