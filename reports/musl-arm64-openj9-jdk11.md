---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 17:08:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 339 |
| Sample Rate | 5.65/sec |
| Health Score | 353% |
| Threads | 14 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (3 unique values: 17-30 cores)</summary>

```
1794348243 22
1794348248 22
1794348253 22
1794348258 22
1794348263 22
1794348268 22
1794348273 22
1794348278 22
1794348283 22
1794348288 22
1794348293 22
1794348298 22
1794348303 22
1794348308 22
1794348313 17
1794348318 17
1794348323 30
1794348328 30
1794348333 30
1794348338 30
```
</details>

---

