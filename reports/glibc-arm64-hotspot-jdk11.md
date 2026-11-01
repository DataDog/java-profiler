---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-01 01:04:50 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 12 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 315 |
| Sample Rate | 5.25/sec |
| Health Score | 328% |
| Threads | 13 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1793509250 24
1793509255 24
1793509260 24
1793509265 24
1793509270 24
1793509275 24
1793509280 24
1793509285 24
1793509290 24
1793509295 24
1793509300 24
1793509305 24
1793509310 24
1793509315 24
1793509320 24
1793509325 24
1793509330 24
1793509335 24
1793509340 24
1793509345 24
```
</details>

---

