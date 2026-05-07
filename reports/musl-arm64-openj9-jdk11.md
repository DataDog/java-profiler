---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 06:43:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1027 |
| Sample Rate | 17.12/sec |
| Health Score | 1070% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778150404 64
1778150409 64
1778150414 64
1778150419 64
1778150424 64
1778150429 64
1778150434 64
1778150439 64
1778150444 64
1778150449 64
1778150454 64
1778150459 64
1778150464 64
1778150469 64
1778150474 64
1778150479 64
1778150484 64
1778150489 64
1778150494 64
1778150499 64
```
</details>

---

