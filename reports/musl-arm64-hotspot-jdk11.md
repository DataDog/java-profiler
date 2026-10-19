---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-19 05:56:45 EDT

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 7 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 12 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (1 unique values: 16-16 cores)</summary>

```
1792403439 16
1792403444 16
1792403449 16
1792403454 16
1792403459 16
1792403464 16
1792403469 16
1792403474 16
1792403479 16
1792403484 16
1792403489 16
1792403494 16
1792403499 16
1792403504 16
1792403509 16
1792403514 16
1792403519 16
1792403524 16
1792403529 16
1792403534 16
```
</details>

---

