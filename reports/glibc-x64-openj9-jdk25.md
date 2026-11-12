---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 14:47:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (4 unique values: 49-52 cores)</summary>

```
1794512577 51
1794512582 51
1794512587 51
1794512592 51
1794512597 51
1794512602 51
1794512607 51
1794512612 51
1794512617 49
1794512622 49
1794512627 49
1794512632 50
1794512637 50
1794512642 50
1794512647 50
1794512652 50
1794512657 50
1794512662 50
1794512667 50
1794512672 50
```
</details>

---

