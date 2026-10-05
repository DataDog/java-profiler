---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-05 00:55:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 8 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 15-32 cores)</summary>

```
1791175833 15
1791175838 15
1791175843 15
1791175848 15
1791175853 15
1791175858 15
1791175863 32
1791175868 32
1791175873 32
1791175878 32
1791175883 32
1791175888 32
1791175893 32
1791175898 32
1791175903 32
1791175908 32
1791175913 32
1791175918 32
1791175923 32
1791175928 32
```
</details>

---

