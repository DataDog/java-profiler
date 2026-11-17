---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 11:50:08 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (5 unique values: 85-92 cores)</summary>

```
1794933912 92
1794933917 92
1794933922 92
1794933927 92
1794933932 92
1794933937 90
1794933942 90
1794933947 90
1794933952 90
1794933957 92
1794933962 92
1794933967 92
1794933972 90
1794933977 90
1794933982 86
1794933987 86
1794933992 88
1794933997 88
1794934002 88
1794934007 88
```
</details>

---

