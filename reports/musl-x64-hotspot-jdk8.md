---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-29 06:43:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 248 |
| Sample Rate | 4.13/sec |
| Health Score | 258% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 78-84 cores)</summary>

```
1790678285 80
1790678290 80
1790678295 80
1790678300 80
1790678305 78
1790678310 78
1790678315 78
1790678320 78
1790678325 82
1790678330 82
1790678335 82
1790678340 82
1790678345 82
1790678350 82
1790678355 84
1790678360 84
1790678365 84
1790678370 84
1790678375 84
1790678380 84
```
</details>

---

