---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 09:18:49 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 281 |
| Sample Rate | 4.68/sec |
| Health Score | 292% |
| Threads | 12 |
| Allocations | 163 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 21-26 cores)</summary>

```
1793801555 26
1793801560 26
1793801565 26
1793801570 26
1793801575 26
1793801580 26
1793801585 26
1793801590 26
1793801595 26
1793801600 26
1793801605 26
1793801610 26
1793801615 26
1793801620 26
1793801625 26
1793801630 26
1793801635 26
1793801640 26
1793801645 26
1793801651 21
```
</details>

---

