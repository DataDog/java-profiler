---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 06:16:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 10 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (4 unique values: 73-91 cores)</summary>

```
1793355114 75
1793355119 75
1793355124 75
1793355129 73
1793355134 73
1793355139 73
1793355144 89
1793355149 89
1793355154 89
1793355159 89
1793355164 89
1793355169 89
1793355174 89
1793355179 89
1793355184 89
1793355189 89
1793355194 89
1793355199 89
1793355204 91
1793355209 91
```
</details>

---

