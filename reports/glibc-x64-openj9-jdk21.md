---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ❌ FAIL

**Date:** 2026-08-25 08:42:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 81-81 cores)</summary>

```
1787661410 81
1787661415 81
1787661420 81
1787661425 81
1787661430 81
1787661435 81
1787661440 81
1787661445 81
1787661450 81
1787661455 81
1787661460 81
1787661465 81
1787661470 81
1787661475 81
1787661480 81
1787661485 81
1787661490 81
1787661495 81
1787661500 81
1787661505 81
```
</details>

---

