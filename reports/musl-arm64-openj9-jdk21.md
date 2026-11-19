---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 13:30:05 EST

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 13 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (5 unique values: 16-24 cores)</summary>

```
1795112620 21
1795112625 21
1795112630 21
1795112635 21
1795112640 16
1795112645 16
1795112650 17
1795112655 17
1795112660 17
1795112665 17
1795112670 19
1795112675 19
1795112680 19
1795112685 19
1795112690 19
1795112695 19
1795112700 24
1795112705 24
1795112710 24
1795112715 24
```
</details>

---

