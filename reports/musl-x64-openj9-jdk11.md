---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-30 00:57:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (3 unique values: 51-54 cores)</summary>

```
1788065536 54
1788065541 54
1788065546 54
1788065551 54
1788065556 54
1788065561 54
1788065566 54
1788065571 54
1788065576 54
1788065581 54
1788065586 54
1788065591 54
1788065596 54
1788065601 54
1788065606 54
1788065611 54
1788065616 54
1788065621 54
1788065626 54
1788065631 51
```
</details>

---

