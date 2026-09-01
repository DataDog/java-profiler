---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-01 12:28:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 341 |
| Sample Rate | 5.68/sec |
| Health Score | 355% |
| Threads | 10 |
| Allocations | 157 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 13 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (4 unique values: 56-60 cores)</summary>

```
1788279730 59
1788279735 59
1788279740 59
1788279745 59
1788279750 59
1788279755 59
1788279760 59
1788279765 59
1788279770 59
1788279775 59
1788279780 59
1788279785 59
1788279790 59
1788279795 59
1788279800 59
1788279805 59
1788279810 60
1788279815 60
1788279821 60
1788279826 58
```
</details>

---

