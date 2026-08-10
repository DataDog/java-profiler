---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-10 09:32:24 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 11 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (2 unique values: 62-65 cores)</summary>

```
1786368428 62
1786368433 62
1786368438 62
1786368443 65
1786368448 65
1786368453 65
1786368458 65
1786368463 65
1786368468 65
1786368473 65
1786368478 65
1786368483 65
1786368488 65
1786368493 65
1786368498 65
1786368503 65
1786368508 65
1786368513 65
1786368518 65
1786368524 65
```
</details>

---

