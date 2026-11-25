---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 08:52:57 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 8 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795614542 64
1795614547 64
1795614552 64
1795614557 64
1795614562 64
1795614567 64
1795614572 64
1795614577 64
1795614582 64
1795614587 64
1795614592 64
1795614597 64
1795614602 64
1795614607 64
1795614612 64
1795614617 64
1795614622 64
1795614627 64
1795614632 64
1795614637 64
```
</details>

---

