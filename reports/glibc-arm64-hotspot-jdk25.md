---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-31 05:50:53 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 12 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (4 unique values: 28-43 cores)</summary>

```
1788169430 28
1788169435 28
1788169440 28
1788169445 28
1788169450 28
1788169455 28
1788169460 28
1788169465 28
1788169470 30
1788169475 30
1788169481 30
1788169486 30
1788169491 30
1788169496 30
1788169501 30
1788169506 30
1788169511 39
1788169516 39
1788169521 43
1788169526 43
```
</details>

---

