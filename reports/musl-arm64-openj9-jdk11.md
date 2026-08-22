---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-21 20:15:09 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 8 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (3 unique values: 31-39 cores)</summary>

```
1787357471 36
1787357476 36
1787357481 36
1787357486 36
1787357491 31
1787357496 31
1787357501 31
1787357506 31
1787357511 31
1787357516 31
1787357521 31
1787357526 31
1787357531 31
1787357536 31
1787357541 31
1787357546 31
1787357551 31
1787357556 31
1787357561 31
1787357566 31
```
</details>

---

