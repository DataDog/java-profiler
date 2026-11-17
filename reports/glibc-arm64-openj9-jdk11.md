---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 06:25:16 EST

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
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 7 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 13 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (2 unique values: 30-34 cores)</summary>

```
1794914457 30
1794914462 30
1794914467 30
1794914472 30
1794914477 30
1794914482 30
1794914487 30
1794914492 30
1794914497 30
1794914502 30
1794914507 30
1794914512 30
1794914517 30
1794914522 30
1794914527 30
1794914532 30
1794914537 30
1794914542 34
1794914547 34
1794914552 34
```
</details>

---

