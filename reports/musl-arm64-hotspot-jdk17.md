---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-19 05:47:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 8 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 14 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1789811045 48
1789811050 48
1789811055 43
1789811060 43
1789811065 41
1789811070 41
1789811075 41
1789811080 41
1789811085 41
1789811090 41
1789811095 41
1789811100 41
1789811105 41
1789811110 41
1789811115 41
1789811120 41
1789811125 43
1789811130 43
1789811135 43
1789811140 43
```
</details>

---

