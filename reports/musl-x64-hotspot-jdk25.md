---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 08:38:42 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 10 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (2 unique values: 29-30 cores)</summary>

```
1792672413 29
1792672418 29
1792672423 29
1792672428 30
1792672433 30
1792672438 30
1792672443 30
1792672448 30
1792672453 30
1792672458 30
1792672463 30
1792672468 30
1792672473 30
1792672478 30
1792672483 30
1792672488 30
1792672493 30
1792672498 30
1792672503 30
1792672508 30
```
</details>

---

