---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 11:34:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
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
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 267 |
| Sample Rate | 4.45/sec |
| Health Score | 278% |
| Threads | 11 |
| Allocations | 115 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1794587408 64
1794587413 64
1794587418 64
1794587423 64
1794587428 64
1794587433 64
1794587438 64
1794587443 64
1794587448 64
1794587453 64
1794587458 64
1794587463 64
1794587468 64
1794587473 64
1794587478 64
1794587483 64
1794587488 64
1794587493 64
1794587498 64
1794587503 64
```
</details>

---

