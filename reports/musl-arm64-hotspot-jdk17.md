---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-12 09:25:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 11 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (4 unique values: 37-47 cores)</summary>

```
1791811232 47
1791811237 47
1791811242 47
1791811247 47
1791811252 47
1791811257 46
1791811262 46
1791811267 46
1791811272 46
1791811277 46
1791811282 46
1791811287 47
1791811292 47
1791811297 47
1791811302 47
1791811307 45
1791811312 45
1791811317 45
1791811322 45
1791811327 45
```
</details>

---

