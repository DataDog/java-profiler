---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-19 05:47:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 9 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (3 unique values: 27-81 cores)</summary>

```
1789811000 79
1789811005 81
1789811010 81
1789811015 79
1789811020 79
1789811025 79
1789811030 79
1789811035 79
1789811040 79
1789811045 79
1789811050 79
1789811055 79
1789811060 79
1789811065 79
1789811070 81
1789811075 81
1789811080 81
1789811085 81
1789811090 81
1789811095 81
```
</details>

---

