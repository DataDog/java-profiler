---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-10 19:29:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 158 |
| Sample Rate | 2.63/sec |
| Health Score | 164% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 196 |
| Sample Rate | 3.27/sec |
| Health Score | 204% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 64-68 cores)</summary>

```
1775863614 68
1775863619 68
1775863624 68
1775863629 68
1775863634 68
1775863639 68
1775863644 68
1775863649 68
1775863654 68
1775863659 68
1775863664 68
1775863669 68
1775863675 68
1775863680 68
1775863685 68
1775863690 68
1775863695 68
1775863700 68
1775863705 68
1775863710 64
```
</details>

---

