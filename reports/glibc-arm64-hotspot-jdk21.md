---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-20 05:46:32 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 12 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1789897374 29
1789897379 29
1789897384 29
1789897389 29
1789897394 29
1789897399 29
1789897404 29
1789897409 29
1789897414 34
1789897419 34
1789897424 34
1789897429 34
1789897434 34
1789897439 34
1789897444 34
1789897449 34
1789897454 34
1789897459 34
1789897464 34
1789897469 32
```
</details>

---

