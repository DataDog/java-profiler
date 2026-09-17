---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 06:26:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (3 unique values: 13-44 cores)</summary>

```
1789640533 13
1789640538 13
1789640543 13
1789640548 13
1789640553 13
1789640558 44
1789640563 44
1789640568 44
1789640573 44
1789640578 13
1789640583 13
1789640588 13
1789640593 13
1789640598 13
1789640603 13
1789640608 13
1789640613 13
1789640618 13
1789640623 13
1789640628 13
```
</details>

---

