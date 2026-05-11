---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-11 11:50:03 EDT

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 974 |
| Sample Rate | 16.23/sec |
| Health Score | 1014% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 82-90 cores)</summary>

```
1778514397 82
1778514402 82
1778514407 82
1778514412 82
1778514417 82
1778514422 82
1778514427 82
1778514432 82
1778514437 82
1778514442 82
1778514447 82
1778514452 86
1778514457 86
1778514462 86
1778514467 86
1778514472 90
1778514477 90
1778514482 90
1778514487 90
1778514492 90
```
</details>

---

