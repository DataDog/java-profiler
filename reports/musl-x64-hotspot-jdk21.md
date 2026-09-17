---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 17:26:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 63-67 cores)</summary>

```
1789680070 67
1789680075 67
1789680080 67
1789680085 67
1789680090 67
1789680095 67
1789680100 67
1789680105 67
1789680110 67
1789680115 67
1789680120 67
1789680126 67
1789680131 67
1789680136 67
1789680141 67
1789680146 67
1789680151 67
1789680156 67
1789680161 65
1789680166 65
```
</details>

---

