---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 18:10:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 8 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
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
1795129671 50
1795129676 50
```
</details>

---

