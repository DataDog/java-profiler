---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 04:45:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (2 unique values: 77-81 cores)</summary>

```
1789979974 77
1789979979 77
1789979984 77
1789979989 77
1789979994 77
1789979999 77
1789980004 77
1789980009 77
1789980014 77
1789980019 81
1789980024 81
1789980030 81
1789980035 81
1789980040 81
1789980045 81
1789980050 81
1789980055 81
1789980060 81
1789980065 81
1789980070 81
```
</details>

---

