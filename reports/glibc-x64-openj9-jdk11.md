---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 13:58:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 12.90/sec |
| Health Score | 806% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793123651 30
1793123656 30
1793123661 30
1793123666 30
1793123671 30
1793123676 30
1793123681 30
1793123686 30
1793123691 32
1793123696 32
1793123701 32
1793123706 32
1793123711 32
1793123716 32
1793123721 32
1793123726 32
1793123731 32
1793123736 32
1793123741 32
1793123746 32
```
</details>

---

