---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-10 06:10:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 12 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 272 |
| Sample Rate | 4.53/sec |
| Health Score | 283% |
| Threads | 14 |
| Allocations | 151 |

<details>
<summary>CPU Timeline (2 unique values: 24-44 cores)</summary>

```
1786356285 24
1786356290 24
1786356295 44
1786356300 44
1786356305 44
1786356310 44
1786356315 44
1786356320 44
1786356325 44
1786356330 44
1786356335 44
1786356340 44
1786356345 44
1786356350 44
1786356355 44
1786356360 44
1786356365 44
1786356370 44
1786356375 44
1786356380 44
```
</details>

---

