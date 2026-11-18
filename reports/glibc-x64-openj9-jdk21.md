---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 05:43:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (3 unique values: 55-72 cores)</summary>

```
1794998178 70
1794998183 70
1794998188 70
1794998193 70
1794998198 70
1794998203 70
1794998208 70
1794998213 70
1794998218 72
1794998223 72
1794998228 72
1794998233 72
1794998238 72
1794998243 72
1794998248 72
1794998253 72
1794998258 72
1794998263 72
1794998268 72
1794998273 55
```
</details>

---

