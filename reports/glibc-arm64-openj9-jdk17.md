---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 00:07:57 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 199 |
| Sample Rate | 3.32/sec |
| Health Score | 207% |
| Threads | 9 |
| Allocations | 164 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 10 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793768528 32
1793768533 32
1793768538 32
1793768543 32
1793768548 32
1793768553 32
1793768558 32
1793768563 32
1793768568 32
1793768573 32
1793768578 32
1793768583 32
1793768588 32
1793768593 32
1793768598 32
1793768603 32
1793768608 32
1793768613 32
1793768618 32
1793768623 32
```
</details>

---

