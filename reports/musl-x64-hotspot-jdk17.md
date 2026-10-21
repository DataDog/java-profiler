---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-21 10:05:25 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 818 |
| Sample Rate | 13.63/sec |
| Health Score | 852% |
| Threads | 12 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (4 unique values: 84-94 cores)</summary>

```
1792591219 92
1792591224 92
1792591229 92
1792591234 92
1792591239 92
1792591244 92
1792591249 92
1792591254 94
1792591259 94
1792591264 94
1792591269 94
1792591274 86
1792591279 86
1792591284 86
1792591289 84
1792591294 84
1792591299 84
1792591304 84
1792591309 84
1792591314 86
```
</details>

---

