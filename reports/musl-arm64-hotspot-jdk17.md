---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 11:46:28 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1786376357 32
1786376362 32
1786376367 32
1786376372 32
1786376377 32
1786376382 32
1786376387 32
1786376392 32
1786376397 32
1786376402 32
1786376407 32
1786376412 32
1786376417 32
1786376422 32
1786376427 32
1786376432 32
1786376438 32
1786376443 32
1786376448 32
1786376453 32
```
</details>

---

