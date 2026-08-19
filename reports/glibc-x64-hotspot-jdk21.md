---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-19 05:51:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (4 unique values: 47-96 cores)</summary>

```
1787132856 49
1787132861 49
1787132866 49
1787132871 49
1787132876 49
1787132881 49
1787132886 47
1787132891 47
1787132896 94
1787132901 94
1787132906 94
1787132911 94
1787132916 96
1787132921 96
1787132926 96
1787132931 96
1787132936 96
1787132941 96
1787132946 96
1787132951 96
```
</details>

---

