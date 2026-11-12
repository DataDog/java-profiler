---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-12 07:55:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 335 |
| Sample Rate | 5.58/sec |
| Health Score | 349% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 154 |
| Sample Rate | 2.57/sec |
| Health Score | 161% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1794487780 32
1794487785 32
1794487790 32
1794487795 32
1794487800 32
1794487805 32
1794487810 32
1794487815 32
1794487820 32
1794487825 32
1794487830 32
1794487835 32
1794487840 32
1794487845 32
1794487850 23
1794487855 23
1794487860 23
1794487865 23
1794487870 23
1794487875 23
```
</details>

---

