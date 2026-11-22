---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-22 17:10:35 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (6 unique values: 24-63 cores)</summary>

```
1795385211 24
1795385216 24
1795385221 24
1795385226 24
1795385231 26
1795385236 26
1795385241 26
1795385246 26
1795385251 26
1795385256 26
1795385261 28
1795385266 28
1795385271 28
1795385276 28
1795385281 28
1795385286 45
1795385291 45
1795385296 45
1795385301 45
1795385306 45
```
</details>

---

