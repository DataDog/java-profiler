---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-31 05:50:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 10 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 32-52 cores)</summary>

```
1788169460 32
1788169465 32
1788169470 32
1788169475 32
1788169480 32
1788169485 32
1788169490 32
1788169495 32
1788169500 32
1788169505 32
1788169510 32
1788169515 32
1788169520 32
1788169525 32
1788169530 32
1788169535 32
1788169540 32
1788169545 32
1788169550 32
1788169555 32
```
</details>

---

