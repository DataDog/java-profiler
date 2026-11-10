---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 08:53:19 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 311 |
| Sample Rate | 5.18/sec |
| Health Score | 324% |
| Threads | 9 |
| Allocations | 166 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 358 |
| Sample Rate | 5.97/sec |
| Health Score | 373% |
| Threads | 13 |
| Allocations | 153 |

<details>
<summary>CPU Timeline (5 unique values: 41-59 cores)</summary>

```
1794318511 41
1794318516 41
1794318521 41
1794318526 41
1794318532 54
1794318537 54
1794318542 54
1794318547 54
1794318552 59
1794318557 59
1794318562 59
1794318567 59
1794318572 59
1794318577 59
1794318582 59
1794318587 46
1794318592 46
1794318597 46
1794318602 46
1794318607 46
```
</details>

---

