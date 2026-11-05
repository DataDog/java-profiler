---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-05 07:42:26 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 10 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (4 unique values: 47-66 cores)</summary>

```
1793882268 53
1793882273 53
1793882278 53
1793882283 47
1793882288 47
1793882293 47
1793882298 47
1793882303 47
1793882308 47
1793882313 64
1793882318 64
1793882323 64
1793882328 64
1793882333 64
1793882338 64
1793882343 66
1793882348 66
1793882353 66
1793882358 66
1793882363 66
```
</details>

---

