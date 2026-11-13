---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 06:03:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 441 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794567525 46
1794567530 46
1794567535 46
1794567540 46
1794567545 46
1794567550 46
1794567555 46
1794567560 46
1794567565 46
1794567570 46
1794567575 46
1794567580 48
1794567585 48
1794567590 48
1794567595 48
1794567600 48
1794567605 48
1794567610 48
1794567615 48
1794567620 48
```
</details>

---

