---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 18:10:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (4 unique values: 35-54 cores)</summary>

```
1795129581 35
1795129586 35
1795129591 40
1795129596 40
1795129601 40
1795129606 40
1795129611 40
1795129616 40
1795129621 54
1795129626 54
1795129631 40
1795129636 40
1795129641 40
1795129646 40
1795129651 40
1795129656 40
1795129661 40
1795129666 40
1795129671 40
1795129676 40
```
</details>

---

