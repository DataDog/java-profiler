---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 09:06:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 840 |
| Sample Rate | 14.00/sec |
| Health Score | 875% |
| Threads | 10 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (4 unique values: 31-41 cores)</summary>

```
1790168550 31
1790168555 31
1790168560 31
1790168565 41
1790168570 41
1790168575 41
1790168580 41
1790168585 41
1790168590 41
1790168595 41
1790168600 41
1790168605 39
1790168610 39
1790168615 39
1790168620 39
1790168625 41
1790168630 41
1790168635 41
1790168640 40
1790168645 40
```
</details>

---

