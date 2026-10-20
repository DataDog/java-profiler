---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ❌ FAIL

**Date:** 2026-10-20 10:11:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (4 unique values: 90-96 cores)</summary>

```
1792505070 94
1792505075 94
1792505080 92
1792505085 92
1792505090 92
1792505095 92
1792505100 94
1792505105 94
1792505110 94
1792505115 94
1792505120 94
1792505125 94
1792505130 94
1792505135 96
1792505140 96
1792505145 96
1792505150 96
1792505155 96
1792505160 96
1792505165 90
```
</details>

---

