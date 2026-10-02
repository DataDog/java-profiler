---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-02 05:51:52 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (5 unique values: 51-64 cores)</summary>

```
1790934389 64
1790934394 64
1790934399 56
1790934404 56
1790934409 56
1790934414 56
1790934419 56
1790934424 56
1790934429 56
1790934434 56
1790934439 51
1790934444 51
1790934449 51
1790934454 51
1790934459 51
1790934464 51
1790934469 57
1790934474 57
1790934479 57
1790934484 57
```
</details>

---

