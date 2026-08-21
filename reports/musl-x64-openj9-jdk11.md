---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-21 17:14:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 960 |
| Sample Rate | 16.00/sec |
| Health Score | 1000% |
| Threads | 11 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (3 unique values: 74-81 cores)</summary>

```
1787346424 81
1787346429 81
1787346434 81
1787346439 81
1787346444 81
1787346449 81
1787346454 81
1787346459 81
1787346464 81
1787346469 81
1787346474 81
1787346479 81
1787346484 81
1787346489 81
1787346494 81
1787346499 81
1787346504 81
1787346509 81
1787346514 81
1787346519 81
```
</details>

---

