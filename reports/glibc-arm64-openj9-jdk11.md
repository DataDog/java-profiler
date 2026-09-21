---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-21 07:21:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 14 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 42-48 cores)</summary>

```
1789989483 45
1789989488 45
1789989493 45
1789989498 45
1789989503 45
1789989508 45
1789989513 45
1789989518 45
1789989523 45
1789989528 45
1789989533 45
1789989538 45
1789989543 45
1789989548 45
1789989553 45
1789989558 45
1789989563 45
1789989568 45
1789989573 45
1789989578 45
```
</details>

---

