---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 05:18:01 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 906 |
| Sample Rate | 15.10/sec |
| Health Score | 944% |
| Threads | 10 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (7 unique values: 40-87 cores)</summary>

```
1795083192 40
1795083197 40
1795083202 40
1795083207 40
1795083213 40
1795083218 40
1795083223 40
1795083228 51
1795083233 51
1795083238 51
1795083243 51
1795083248 51
1795083253 51
1795083258 51
1795083263 53
1795083268 53
1795083273 53
1795083278 62
1795083283 62
1795083288 67
```
</details>

---

