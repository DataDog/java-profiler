---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 12:39:36 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 749 |
| Sample Rate | 12.48/sec |
| Health Score | 780% |
| Threads | 9 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (4 unique values: 73-79 cores)</summary>

```
1793205291 73
1793205296 73
1793205301 73
1793205306 73
1793205311 73
1793205316 75
1793205321 75
1793205326 75
1793205331 75
1793205336 75
1793205341 75
1793205346 75
1793205351 75
1793205356 75
1793205361 75
1793205366 75
1793205371 75
1793205376 75
1793205381 77
1793205386 77
```
</details>

---

