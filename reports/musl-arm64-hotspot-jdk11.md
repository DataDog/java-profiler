---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:09:25 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 11 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794506617 43
1794506622 43
1794506627 43
1794506632 43
1794506637 43
1794506642 43
1794506647 43
1794506652 43
1794506657 43
1794506662 48
1794506667 48
1794506672 43
1794506677 43
1794506682 43
1794506687 43
1794506692 43
1794506697 43
1794506702 43
1794506708 43
1794506713 43
```
</details>

---

