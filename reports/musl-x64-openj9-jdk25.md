---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-12 13:12:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 9 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1770919605 28
1770919610 28
1770919615 28
1770919620 28
1770919625 28
1770919630 28
1770919635 28
1770919640 28
1770919645 28
1770919650 28
1770919655 28
1770919660 28
1770919665 28
1770919670 28
1770919675 30
1770919680 30
1770919685 32
1770919690 32
1770919695 30
1770919700 30
```
</details>

---

