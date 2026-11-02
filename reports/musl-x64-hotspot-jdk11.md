---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 11:04:43 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 9 |
| Allocations | 606 |

<details>
<summary>CPU Timeline (3 unique values: 43-47 cores)</summary>

```
1793635104 45
1793635109 45
1793635114 45
1793635119 45
1793635124 45
1793635129 43
1793635134 43
1793635139 43
1793635144 43
1793635149 45
1793635154 45
1793635159 47
1793635164 47
1793635169 47
1793635174 45
1793635180 45
1793635185 45
1793635190 45
1793635195 45
1793635200 45
```
</details>

---

