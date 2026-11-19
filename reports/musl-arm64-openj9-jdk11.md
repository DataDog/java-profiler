---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 18:09:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 12 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795129571 50
1795129576 50
1795129581 50
1795129586 50
1795129591 50
1795129596 50
1795129601 50
1795129606 50
1795129611 50
1795129616 50
1795129621 50
1795129626 50
1795129631 50
1795129636 50
1795129641 50
1795129646 50
1795129651 50
1795129656 50
1795129661 50
1795129666 50
```
</details>

---

