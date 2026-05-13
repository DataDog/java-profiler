---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-13 09:58:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 12 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778680383 64
1778680388 64
1778680393 64
1778680398 64
1778680403 64
1778680408 64
1778680413 64
1778680418 64
1778680423 64
1778680428 64
1778680433 64
1778680438 64
1778680443 64
1778680448 64
1778680453 64
1778680458 64
1778680463 64
1778680468 64
1778680473 64
1778680478 64
```
</details>

---

