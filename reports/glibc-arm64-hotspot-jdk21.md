---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:18:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 25-33 cores)</summary>

```
1795641275 25
1795641280 25
1795641285 25
1795641290 25
1795641295 25
1795641300 25
1795641305 25
1795641310 25
1795641315 25
1795641320 29
1795641325 29
1795641330 29
1795641335 29
1795641340 29
1795641345 29
1795641350 29
1795641355 29
1795641360 29
1795641365 33
1795641370 33
```
</details>

---

