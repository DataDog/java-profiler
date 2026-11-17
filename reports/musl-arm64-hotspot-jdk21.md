---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ❌ FAIL

**Date:** 2026-11-17 14:55:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 15-15 cores)</summary>

```
1794945005 15
1794945010 15
1794945015 15
1794945020 15
1794945025 15
1794945030 15
1794945035 15
1794945040 15
1794945045 15
1794945050 15
1794945055 15
1794945060 15
1794945065 15
1794945070 15
1794945075 15
1794945080 15
1794945085 15
1794945090 15
1794945095 15
1794945100 15
```
</details>

---

