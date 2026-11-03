---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 11:00:43 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 11 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (2 unique values: 58-60 cores)</summary>

```
1793721192 58
1793721197 58
1793721202 60
1793721207 60
1793721212 60
1793721217 60
1793721222 58
1793721227 58
1793721232 58
1793721237 58
1793721242 58
1793721247 58
1793721252 58
1793721257 58
1793721262 58
1793721267 58
1793721272 58
1793721277 58
1793721282 58
1793721287 58
```
</details>

---

