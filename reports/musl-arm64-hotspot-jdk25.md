---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 09:32:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 12 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1787232408 64
1787232413 64
1787232418 64
1787232423 64
1787232428 64
1787232433 64
1787232438 64
1787232443 64
1787232448 64
1787232453 64
1787232458 64
1787232463 62
1787232468 62
1787232473 62
1787232478 62
1787232483 62
1787232488 62
1787232493 62
1787232498 62
1787232503 62
```
</details>

---

