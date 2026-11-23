---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 04:08:48 EST

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 14 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 16-21 cores)</summary>

```
1795424571 16
1795424576 16
1795424581 16
1795424586 16
1795424591 16
1795424596 16
1795424601 16
1795424606 16
1795424611 21
1795424616 21
1795424621 21
1795424626 21
1795424631 21
1795424636 21
1795424641 21
1795424646 21
1795424651 21
1795424656 21
1795424661 21
1795424666 21
```
</details>

---

