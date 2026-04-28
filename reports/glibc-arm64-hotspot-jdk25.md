---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-28 11:22:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 9 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777389442 64
1777389447 64
1777389452 64
1777389457 64
1777389462 64
1777389467 64
1777389472 64
1777389477 64
1777389482 64
1777389487 64
1777389492 64
1777389497 64
1777389502 64
1777389507 64
1777389512 64
1777389517 64
1777389522 64
1777389527 64
1777389532 64
1777389537 64
```
</details>

---

