---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 08:25:41 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 376 |
| Sample Rate | 6.27/sec |
| Health Score | 392% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 10 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (3 unique values: 25-47 cores)</summary>

```
1795094421 25
1795094426 25
1795094431 25
1795094436 25
1795094441 30
1795094446 30
1795094451 30
1795094456 30
1795094461 30
1795094466 30
1795094471 30
1795094476 30
1795094481 30
1795094486 30
1795094491 47
1795094496 47
1795094501 47
1795094506 47
1795094511 47
1795094516 47
```
</details>

---

