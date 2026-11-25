---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:22:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 10 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 9 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 72-81 cores)</summary>

```
1795641299 78
1795641304 78
1795641309 78
1795641314 78
1795641319 78
1795641324 78
1795641329 78
1795641334 78
1795641339 78
1795641344 78
1795641349 78
1795641354 78
1795641359 78
1795641364 78
1795641369 78
1795641374 78
1795641379 78
1795641384 78
1795641389 78
1795641394 81
```
</details>

---

