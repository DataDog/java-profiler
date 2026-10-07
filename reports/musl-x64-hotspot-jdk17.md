---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-07 05:56:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 764 |
| Sample Rate | 12.73/sec |
| Health Score | 796% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (5 unique values: 65-77 cores)</summary>

```
1791366516 77
1791366521 77
1791366526 77
1791366532 77
1791366537 77
1791366542 77
1791366547 69
1791366552 69
1791366557 71
1791366562 71
1791366567 71
1791366572 71
1791366577 71
1791366582 71
1791366587 71
1791366592 71
1791366597 71
1791366602 71
1791366607 73
1791366612 73
```
</details>

---

