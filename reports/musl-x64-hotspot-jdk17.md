---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-26 00:04:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
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
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 7 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1795669248 62
1795669253 64
1795669258 64
1795669263 64
1795669268 64
1795669273 64
1795669278 64
1795669283 64
1795669288 64
1795669293 64
1795669298 64
1795669303 64
1795669308 64
1795669313 64
1795669318 64
1795669323 64
1795669328 64
1795669333 64
1795669338 64
1795669343 64
```
</details>

---

