---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-12 08:46:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 11 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 22-30 cores)</summary>

```
1786538539 30
1786538544 30
1786538549 30
1786538554 30
1786538559 30
1786538564 30
1786538569 25
1786538574 25
1786538579 25
1786538585 25
1786538590 25
1786538595 25
1786538600 25
1786538605 25
1786538610 25
1786538615 25
1786538620 25
1786538625 25
1786538630 25
1786538635 25
```
</details>

---

