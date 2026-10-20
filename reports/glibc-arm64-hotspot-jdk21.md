---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-20 07:43:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 12 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792496379 32
1792496384 32
1792496389 32
1792496394 30
1792496399 30
1792496404 30
1792496409 30
1792496414 30
1792496419 30
1792496424 30
1792496429 30
1792496434 30
1792496439 30
1792496444 30
1792496449 30
1792496454 30
1792496459 30
1792496464 30
1792496469 30
1792496474 30
```
</details>

---

