---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:45:30 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 10 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 795 |
| Sample Rate | 13.25/sec |
| Health Score | 828% |
| Threads | 9 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (3 unique values: 81-86 cores)</summary>

```
1794497496 84
1794497501 84
1794497506 84
1794497511 84
1794497516 84
1794497521 84
1794497526 84
1794497531 84
1794497536 84
1794497541 84
1794497546 84
1794497552 84
1794497557 86
1794497562 86
1794497567 86
1794497572 86
1794497577 86
1794497582 81
1794497587 81
1794497592 81
```
</details>

---

