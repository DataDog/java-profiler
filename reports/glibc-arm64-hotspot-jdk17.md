---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-20 05:42:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (3 unique values: 12-18 cores)</summary>

```
1787218652 12
1787218657 12
1787218662 15
1787218667 15
1787218672 15
1787218677 15
1787218682 15
1787218687 15
1787218692 15
1787218697 15
1787218702 15
1787218707 15
1787218712 15
1787218717 15
1787218722 15
1787218727 15
1787218732 15
1787218737 15
1787218743 15
1787218748 18
```
</details>

---

