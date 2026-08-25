---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-25 16:41:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 236 |
| Sample Rate | 3.93/sec |
| Health Score | 246% |
| Threads | 9 |
| Allocations | 173 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1787690309 64
1787690314 64
1787690319 64
1787690324 64
1787690329 64
1787690334 59
1787690339 59
1787690344 59
1787690349 59
1787690354 54
1787690359 54
1787690364 54
1787690369 54
1787690374 54
1787690379 54
1787690384 54
1787690389 59
1787690394 59
1787690399 59
1787690404 59
```
</details>

---

