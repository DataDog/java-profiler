---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 11:34:31 EST

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 738 |
| Sample Rate | 12.30/sec |
| Health Score | 769% |
| Threads | 9 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (3 unique values: 22-28 cores)</summary>

```
1794587402 22
1794587407 22
1794587412 24
1794587417 24
1794587422 22
1794587427 22
1794587432 22
1794587437 22
1794587442 22
1794587447 22
1794587452 22
1794587457 22
1794587462 22
1794587467 22
1794587472 22
1794587477 22
1794587482 22
1794587487 22
1794587492 28
1794587497 28
```
</details>

---

