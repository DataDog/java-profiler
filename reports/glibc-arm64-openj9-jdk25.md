---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 10:53:45 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794498426 64
1794498431 64
1794498436 64
1794498441 64
1794498446 64
1794498451 64
1794498456 64
1794498461 64
1794498466 64
1794498471 64
1794498476 64
1794498481 64
1794498486 64
1794498491 64
1794498496 64
1794498501 64
1794498506 64
1794498511 64
1794498516 51
1794498521 51
```
</details>

---

