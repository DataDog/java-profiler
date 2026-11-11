---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 09:02:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 15 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1794405449 34
1794405454 34
1794405459 34
1794405464 34
1794405469 34
1794405474 34
1794405479 34
1794405484 34
1794405489 34
1794405494 34
1794405499 34
1794405504 34
1794405509 34
1794405514 34
1794405519 34
1794405524 32
1794405529 32
1794405534 32
1794405539 32
1794405544 32
```
</details>

---

