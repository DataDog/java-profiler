---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-25 10:31:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 7 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 42-45 cores)</summary>

```
1790346394 42
1790346399 42
1790346404 42
1790346409 42
1790346414 42
1790346419 45
1790346424 45
1790346429 45
1790346434 45
1790346439 45
1790346444 45
1790346449 45
1790346454 45
1790346459 45
1790346464 45
1790346469 45
1790346474 45
1790346479 45
1790346484 45
1790346489 45
```
</details>

---

