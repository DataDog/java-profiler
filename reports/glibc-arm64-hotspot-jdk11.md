---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 07:04:03 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 8 |
| Allocations | 312 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 13 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 29-64 cores)</summary>

```
1795175990 64
1795175995 64
1795176000 64
1795176005 64
1795176010 29
1795176015 29
1795176021 29
1795176026 29
1795176031 29
1795176036 29
1795176041 29
1795176046 29
1795176051 29
1795176056 29
1795176061 29
1795176066 29
1795176071 29
1795176076 29
1795176081 29
1795176086 29
```
</details>

---

