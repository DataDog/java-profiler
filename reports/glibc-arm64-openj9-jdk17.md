---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-30 08:18:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1793362353 44
1793362358 48
1793362363 48
1793362368 48
1793362373 48
1793362378 48
1793362383 48
1793362389 48
1793362394 48
1793362399 43
1793362404 43
1793362409 43
1793362414 43
1793362419 43
1793362424 43
1793362429 43
1793362434 43
1793362439 43
1793362444 43
1793362449 43
```
</details>

---

