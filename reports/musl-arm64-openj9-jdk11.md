---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-29 07:38:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 971 |
| Sample Rate | 16.18/sec |
| Health Score | 1011% |
| Threads | 9 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777462473 64
1777462478 64
1777462483 64
1777462488 64
1777462493 64
1777462498 64
1777462503 64
1777462508 64
1777462513 64
1777462518 64
1777462523 64
1777462528 64
1777462533 64
1777462538 64
1777462543 64
1777462548 64
1777462553 64
1777462558 64
1777462563 64
1777462568 64
```
</details>

---

