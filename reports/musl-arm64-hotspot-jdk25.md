---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 09:12:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795097273 50
1795097278 50
1795097283 50
1795097288 50
1795097293 50
1795097298 50
1795097303 50
1795097308 50
1795097313 50
1795097319 50
1795097324 50
1795097329 50
1795097334 50
1795097339 50
1795097344 50
1795097349 50
1795097354 50
1795097359 50
1795097364 50
1795097369 50
```
</details>

---

