---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 06:22:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 10 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 11 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1770117423 29
1770117428 29
1770117433 27
1770117438 27
1770117443 32
1770117448 32
1770117453 32
1770117458 32
1770117463 32
1770117468 32
1770117473 32
1770117478 32
1770117483 32
1770117488 32
1770117493 32
1770117498 32
1770117503 32
1770117508 32
1770117513 32
1770117518 32
```
</details>

---

