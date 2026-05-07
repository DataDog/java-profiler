---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 12:39:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
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
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778171723 64
1778171728 64
1778171733 64
1778171738 64
1778171743 64
1778171748 64
1778171753 64
1778171758 64
1778171763 64
1778171768 64
1778171773 64
1778171778 64
1778171783 64
1778171788 64
1778171793 64
1778171798 64
1778171803 64
1778171808 64
1778171813 64
1778171818 64
```
</details>

---

