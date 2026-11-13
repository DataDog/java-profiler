---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 06:03:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794567534 48
1794567539 48
1794567544 48
1794567550 48
1794567555 48
1794567560 48
1794567565 48
1794567570 48
1794567575 48
1794567580 48
1794567585 48
1794567590 48
1794567595 48
1794567600 48
1794567605 48
1794567610 48
1794567615 48
1794567620 48
1794567625 43
1794567630 43
```
</details>

---

