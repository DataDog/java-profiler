---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 13:02:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 786 |
| Sample Rate | 13.10/sec |
| Health Score | 819% |
| Threads | 11 |
| Allocations | 553 |

<details>
<summary>CPU Timeline (3 unique values: 41-52 cores)</summary>

```
1790787375 41
1790787380 41
1790787385 52
1790787390 52
1790787395 52
1790787400 52
1790787405 52
1790787410 52
1790787415 52
1790787420 52
1790787425 52
1790787430 52
1790787435 52
1790787440 52
1790787445 52
1790787450 52
1790787455 52
1790787460 50
1790787465 50
1790787470 50
```
</details>

---

