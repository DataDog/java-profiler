---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 05:57:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 11 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (6 unique values: 34-51 cores)</summary>

```
1794826392 45
1794826397 45
1794826402 45
1794826407 45
1794826412 45
1794826417 40
1794826422 40
1794826427 40
1794826433 40
1794826438 36
1794826443 36
1794826448 36
1794826453 34
1794826458 34
1794826463 51
1794826468 51
1794826473 51
1794826478 51
1794826483 40
1794826488 40
```
</details>

---

