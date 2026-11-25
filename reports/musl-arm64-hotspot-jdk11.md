---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:48:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 146 |
| Sample Rate | 2.43/sec |
| Health Score | 152% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 11 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (3 unique values: 28-33 cores)</summary>

```
1795632226 28
1795632231 28
1795632236 28
1795632241 28
1795632247 28
1795632252 28
1795632257 28
1795632262 28
1795632267 28
1795632272 28
1795632277 28
1795632282 28
1795632287 28
1795632292 28
1795632297 28
1795632302 33
1795632307 33
1795632312 33
1795632317 33
1795632322 29
```
</details>

---

