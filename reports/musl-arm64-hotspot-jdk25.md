---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 05:29:42 EST

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
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 41 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 11 |
| Allocations | 114 |

<details>
<summary>CPU Timeline (2 unique values: 42-43 cores)</summary>

```
1794392597 42
1794392602 42
1794392607 42
1794392612 42
1794392617 42
1794392622 42
1794392627 42
1794392632 43
1794392637 43
1794392642 43
1794392647 43
1794392652 43
1794392657 43
1794392662 43
1794392667 43
1794392672 43
1794392677 43
1794392682 43
1794392687 43
1794392692 43
```
</details>

---

