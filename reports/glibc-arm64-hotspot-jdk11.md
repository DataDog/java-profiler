---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 15:36:16 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 248 |
| Sample Rate | 4.13/sec |
| Health Score | 258% |
| Threads | 9 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789673419 48
1789673424 48
1789673429 48
1789673434 48
1789673439 48
1789673444 48
1789673449 48
1789673454 48
1789673459 48
1789673464 48
1789673469 48
1789673474 48
1789673479 48
1789673484 48
1789673489 48
1789673494 48
1789673499 48
1789673504 48
1789673509 43
1789673514 43
```
</details>

---

