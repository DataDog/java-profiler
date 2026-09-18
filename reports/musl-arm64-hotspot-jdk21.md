---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 11:13:59 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789743414 48
1789743419 48
1789743424 48
1789743429 48
1789743434 48
1789743439 48
1789743444 48
1789743449 48
1789743454 43
1789743459 43
1789743464 43
1789743469 43
1789743474 43
1789743479 43
1789743484 43
1789743489 43
1789743494 43
1789743500 43
1789743505 48
1789743510 48
```
</details>

---

