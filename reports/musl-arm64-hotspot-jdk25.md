---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 06:11:56 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 12 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 10 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (2 unique values: 41-43 cores)</summary>

```
1789639635 43
1789639640 43
1789639645 43
1789639650 43
1789639655 43
1789639660 43
1789639665 43
1789639670 43
1789639675 43
1789639680 41
1789639685 41
1789639690 41
1789639695 41
1789639700 41
1789639705 41
1789639710 41
1789639715 41
1789639720 41
1789639725 41
1789639730 41
```
</details>

---

