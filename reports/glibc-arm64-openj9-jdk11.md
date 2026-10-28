---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 12:39:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1009 |
| Sample Rate | 16.82/sec |
| Health Score | 1051% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1793205353 30
1793205358 30
1793205363 30
1793205368 30
1793205373 30
1793205378 30
1793205383 30
1793205388 30
1793205393 30
1793205398 30
1793205403 30
1793205408 30
1793205413 30
1793205418 30
1793205423 30
1793205428 30
1793205433 30
1793205438 30
1793205443 30
1793205448 30
```
</details>

---

