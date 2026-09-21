---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 04:45:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1789979989 49
1789979994 49
1789979999 49
1789980004 49
1789980009 49
1789980014 49
1789980019 49
1789980024 49
1789980029 49
1789980035 49
1789980040 49
1789980045 49
1789980050 49
1789980055 49
1789980060 49
1789980065 49
1789980070 49
1789980075 49
1789980080 49
1789980085 64
```
</details>

---

