---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 12:31:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 11 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (2 unique values: 81-89 cores)</summary>

```
1787243315 81
1787243320 81
1787243325 81
1787243330 81
1787243335 81
1787243340 81
1787243345 81
1787243350 81
1787243355 81
1787243360 81
1787243365 81
1787243370 81
1787243375 81
1787243380 81
1787243385 81
1787243390 81
1787243395 89
1787243400 89
1787243405 89
1787243410 89
```
</details>

---

