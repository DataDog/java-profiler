---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-20 13:25:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 246 |
| Sample Rate | 4.10/sec |
| Health Score | 256% |
| Threads | 10 |
| Allocations | 177 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 304 |
| Sample Rate | 5.07/sec |
| Health Score | 317% |
| Threads | 12 |
| Allocations | 161 |

<details>
<summary>CPU Timeline (3 unique values: 24-31 cores)</summary>

```
1787246450 31
1787246455 26
1787246460 26
1787246465 26
1787246470 26
1787246475 26
1787246480 26
1787246485 26
1787246490 26
1787246495 26
1787246500 26
1787246505 26
1787246510 26
1787246515 26
1787246520 26
1787246525 26
1787246530 26
1787246535 26
1787246540 26
1787246545 24
```
</details>

---

