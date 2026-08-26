---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-26 17:48:11 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 9 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (3 unique values: 86-96 cores)</summary>

```
1787780547 96
1787780552 96
1787780557 96
1787780562 96
1787780567 96
1787780572 96
1787780577 96
1787780582 96
1787780587 96
1787780592 96
1787780597 96
1787780602 96
1787780607 96
1787780612 96
1787780617 96
1787780622 96
1787780627 96
1787780632 94
1787780637 94
1787780642 94
```
</details>

---

