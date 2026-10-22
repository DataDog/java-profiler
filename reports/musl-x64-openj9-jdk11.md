---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 01:13:29 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (3 unique values: 73-77 cores)</summary>

```
1792645473 75
1792645478 75
1792645483 73
1792645488 73
1792645493 73
1792645498 73
1792645503 73
1792645508 73
1792645513 73
1792645518 73
1792645523 75
1792645528 75
1792645533 75
1792645538 75
1792645543 75
1792645548 75
1792645553 75
1792645558 75
1792645563 75
1792645568 75
```
</details>

---

