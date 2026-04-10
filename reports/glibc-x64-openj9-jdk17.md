---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-10 02:47:32 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 386 |
| Sample Rate | 6.43/sec |
| Health Score | 402% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 9 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (2 unique values: 45-49 cores)</summary>

```
1775803434 49
1775803439 49
1775803444 49
1775803449 49
1775803454 49
1775803459 49
1775803464 49
1775803469 49
1775803474 49
1775803479 49
1775803484 49
1775803489 49
1775803494 45
1775803499 45
1775803505 45
1775803510 45
1775803515 45
1775803520 45
1775803525 45
1775803530 45
```
</details>

---

