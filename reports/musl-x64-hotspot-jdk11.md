---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-01-30 06:15:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 879 |
| Sample Rate | 14.65/sec |
| Health Score | 916% |
| Threads | 9 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1769771389 32
1769771394 32
1769771399 32
1769771404 32
1769771409 32
1769771414 32
1769771419 32
1769771424 32
1769771429 32
1769771434 32
1769771439 32
1769771444 32
1769771449 32
1769771454 30
1769771459 30
1769771464 30
1769771469 30
1769771474 30
1769771479 30
1769771484 27
```
</details>

---

