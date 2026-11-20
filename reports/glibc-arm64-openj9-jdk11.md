---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 13:41:31 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 355 |
| Sample Rate | 5.92/sec |
| Health Score | 370% |
| Threads | 10 |
| Allocations | 185 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795199785 64
1795199790 64
1795199795 64
1795199800 64
1795199805 64
1795199810 64
1795199815 64
1795199820 64
1795199825 64
1795199830 64
1795199835 64
1795199840 64
1795199845 64
1795199850 64
1795199855 64
1795199860 64
1795199865 64
1795199870 64
1795199875 64
1795199880 64
```
</details>

---

