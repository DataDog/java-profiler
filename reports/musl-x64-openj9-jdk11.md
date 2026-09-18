---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 01:02:04 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 8 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 57-79 cores)</summary>

```
1789707383 59
1789707388 59
1789707393 59
1789707398 59
1789707403 57
1789707408 57
1789707413 57
1789707418 57
1789707423 57
1789707428 57
1789707433 59
1789707438 59
1789707443 59
1789707448 59
1789707453 59
1789707458 59
1789707463 79
1789707468 79
1789707473 79
1789707478 79
```
</details>

---

