---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-01 00:59:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 137 |
| Sample Rate | 2.28/sec |
| Health Score | 142% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 49-64 cores)</summary>

```
1790830496 54
1790830501 49
1790830506 49
1790830511 49
1790830516 49
1790830521 49
1790830526 49
1790830531 49
1790830536 49
1790830541 49
1790830546 49
1790830551 49
1790830556 49
1790830561 49
1790830566 49
1790830571 49
1790830576 54
1790830582 54
1790830587 59
1790830592 59
```
</details>

---

