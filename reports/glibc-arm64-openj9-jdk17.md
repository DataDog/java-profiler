---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-19 11:16:47 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 226 |
| Sample Rate | 3.77/sec |
| Health Score | 236% |
| Threads | 11 |
| Allocations | 150 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1787152391 30
1787152396 30
1787152401 30
1787152406 30
1787152411 30
1787152416 30
1787152421 30
1787152426 30
1787152431 30
1787152436 30
1787152441 30
1787152446 30
1787152451 30
1787152456 30
1787152461 30
1787152466 32
1787152471 32
1787152476 32
1787152481 32
1787152486 32
```
</details>

---

