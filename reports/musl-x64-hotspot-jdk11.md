---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 10:27:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 920 |
| Sample Rate | 15.33/sec |
| Health Score | 958% |
| Threads | 10 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (4 unique values: 87-91 cores)</summary>

```
1790173234 87
1790173239 87
1790173244 87
1790173249 87
1790173254 89
1790173259 89
1790173264 89
1790173269 90
1790173274 90
1790173279 90
1790173284 90
1790173289 90
1790173294 91
1790173299 91
1790173304 91
1790173309 91
1790173314 91
1790173319 91
1790173324 91
1790173329 91
```
</details>

---

