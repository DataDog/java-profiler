---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-12 09:20:29 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 11 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778591605 59
1778591610 59
1778591615 59
1778591620 59
1778591625 59
1778591630 59
1778591635 64
1778591640 64
1778591645 64
1778591650 64
1778591655 64
1778591660 64
1778591665 64
1778591670 64
1778591675 64
1778591680 64
1778591685 64
1778591690 64
1778591695 64
1778591700 64
```
</details>

---

