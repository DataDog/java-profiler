---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 14:47:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 165 |
| Sample Rate | 2.75/sec |
| Health Score | 172% |
| Threads | 14 |
| Allocations | 110 |

<details>
<summary>CPU Timeline (2 unique values: 30-33 cores)</summary>

```
1794512576 33
1794512581 33
1794512586 33
1794512591 33
1794512597 33
1794512602 33
1794512607 33
1794512612 33
1794512617 33
1794512622 33
1794512627 33
1794512632 33
1794512637 33
1794512642 33
1794512647 33
1794512652 33
1794512657 30
1794512662 30
1794512667 30
1794512672 30
```
</details>

---

