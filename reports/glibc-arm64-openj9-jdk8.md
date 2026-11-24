---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-24 12:19:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 374 |
| Sample Rate | 6.23/sec |
| Health Score | 389% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1795540521 48
1795540526 48
1795540531 48
1795540536 48
1795540541 48
1795540546 48
1795540551 48
1795540556 48
1795540561 48
1795540566 48
1795540571 48
1795540576 48
1795540581 48
1795540586 48
1795540591 48
1795540596 48
1795540601 48
1795540607 48
1795540612 48
1795540617 48
```
</details>

---

