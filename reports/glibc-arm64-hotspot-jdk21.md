---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 10:29:08 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1793197512 36
1793197517 36
1793197522 36
1793197527 36
1793197532 36
1793197537 36
1793197542 36
1793197547 36
1793197552 36
1793197557 36
1793197562 36
1793197567 36
1793197572 36
1793197577 36
1793197582 36
1793197587 36
1793197592 36
1793197597 36
1793197602 36
1793197607 36
```
</details>

---

