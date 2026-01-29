---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-29 07:01:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 23.53/sec |
| Health Score | 1471% |
| Threads | 10 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 879 |
| Sample Rate | 29.30/sec |
| Health Score | 1831% |
| Threads | 12 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 8-12 cores)</summary>

```
1769687520 8
1769687525 8
1769687530 8
1769687535 8
1769687540 8
1769687545 8
1769687550 8
1769687555 8
1769687560 12
1769687565 12
1769687570 12
1769687575 12
1769687580 12
1769687585 12
1769687590 12
1769687595 12
1769687600 12
1769687605 12
1769687610 12
1769687615 12
```
</details>

---

