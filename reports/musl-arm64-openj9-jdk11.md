---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-01 00:59:50 EDT

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
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 16 |
| Allocations | 187 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1790830471 64
1790830476 64
1790830481 64
1790830486 64
1790830491 64
1790830496 64
1790830501 64
1790830506 64
1790830511 64
1790830516 64
1790830521 64
1790830526 64
1790830531 64
1790830536 64
1790830541 64
1790830546 64
1790830551 64
1790830556 64
1790830562 64
1790830567 64
```
</details>

---

