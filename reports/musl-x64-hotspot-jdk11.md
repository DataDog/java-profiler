---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-23 06:56:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 10 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1083 |
| Sample Rate | 18.05/sec |
| Health Score | 1128% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (5 unique values: 57-66 cores)</summary>

```
1776941441 66
1776941446 66
1776941451 66
1776941456 66
1776941461 64
1776941466 64
1776941472 64
1776941477 64
1776941482 64
1776941487 64
1776941492 57
1776941497 57
1776941502 59
1776941507 59
1776941512 59
1776941517 59
1776941522 59
1776941527 59
1776941532 59
1776941537 59
```
</details>

---

