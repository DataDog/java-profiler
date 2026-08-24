---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-24 17:08:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 11 |
| Allocations | 431 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787605376 43
1787605381 43
1787605386 43
1787605391 43
1787605396 43
1787605401 43
1787605406 43
1787605411 43
1787605416 43
1787605421 48
1787605426 48
1787605431 48
1787605436 48
1787605441 48
1787605446 48
1787605451 48
1787605456 48
1787605461 48
1787605466 48
1787605471 48
```
</details>

---

