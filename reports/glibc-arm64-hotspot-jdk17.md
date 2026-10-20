---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-20 13:18:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 359 |
| Sample Rate | 5.98/sec |
| Health Score | 374% |
| Threads | 12 |
| Allocations | 145 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 139 |
| Sample Rate | 2.32/sec |
| Health Score | 145% |
| Threads | 15 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1792516409 51
1792516414 51
1792516419 51
1792516424 51
1792516429 51
1792516434 51
1792516439 64
1792516444 64
1792516449 64
1792516454 64
1792516459 64
1792516464 64
1792516469 64
1792516474 64
1792516479 64
1792516484 64
1792516489 51
1792516494 51
1792516499 51
1792516504 51
```
</details>

---

