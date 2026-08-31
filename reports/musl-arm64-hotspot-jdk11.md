---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-31 06:41:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 14 |
| Allocations | 192 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1788172495 28
1788172500 28
1788172505 28
1788172510 28
1788172515 28
1788172520 48
1788172525 48
1788172530 48
1788172535 48
1788172541 48
1788172546 48
1788172551 48
1788172556 48
1788172561 48
1788172566 48
1788172571 48
1788172576 48
1788172581 48
1788172586 48
1788172591 48
```
</details>

---

