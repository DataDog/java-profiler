---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 04:08:50 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 37-42 cores)</summary>

```
1795424523 42
1795424528 42
1795424533 37
1795424538 37
1795424543 37
1795424548 37
1795424553 37
1795424558 37
1795424563 37
1795424568 37
1795424573 37
1795424578 37
1795424583 37
1795424588 37
1795424593 37
1795424598 37
1795424603 42
1795424608 42
1795424613 42
1795424618 42
```
</details>

---

