---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 18:09:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 38-55 cores)</summary>

```
1795129531 55
1795129536 38
1795129541 38
1795129546 38
1795129551 38
1795129556 38
1795129561 38
1795129566 38
1795129571 38
1795129576 38
1795129581 38
1795129586 38
1795129591 38
1795129596 38
1795129601 38
1795129606 38
1795129611 38
1795129616 55
1795129621 55
1795129626 55
```
</details>

---

