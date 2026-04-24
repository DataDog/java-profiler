---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-24 12:55:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (4 unique values: 28-32 cores)</summary>

```
1777049459 29
1777049464 29
1777049469 29
1777049474 29
1777049479 29
1777049484 29
1777049489 29
1777049494 29
1777049500 29
1777049505 29
1777049510 32
1777049515 32
1777049520 32
1777049525 30
1777049530 30
1777049535 30
1777049540 30
1777049545 30
1777049550 30
1777049555 30
```
</details>

---

