---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-11 11:49:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 146 |
| Sample Rate | 2.43/sec |
| Health Score | 152% |
| Threads | 12 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 13 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778514234 64
1778514239 64
1778514244 64
1778514249 64
1778514254 64
1778514259 64
1778514264 64
1778514269 64
1778514274 64
1778514279 64
1778514284 59
1778514289 59
1778514294 59
1778514299 59
1778514304 59
1778514309 59
1778514314 59
1778514319 59
1778514324 59
1778514329 59
```
</details>

---

