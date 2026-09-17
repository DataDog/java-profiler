---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 06:26:36 EDT

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 9 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 11-32 cores)</summary>

```
1789640511 11
1789640516 11
1789640521 11
1789640526 11
1789640531 11
1789640536 11
1789640541 11
1789640546 11
1789640551 11
1789640556 11
1789640561 11
1789640566 11
1789640571 11
1789640576 32
1789640581 32
1789640586 32
1789640591 17
1789640596 17
1789640601 17
1789640606 17
```
</details>

---

