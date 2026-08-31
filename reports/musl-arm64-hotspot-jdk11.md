---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-31 00:49:31 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 317 |
| Sample Rate | 5.28/sec |
| Health Score | 330% |
| Threads | 14 |
| Allocations | 159 |

<details>
<summary>CPU Timeline (2 unique values: 12-14 cores)</summary>

```
1788151510 14
1788151515 14
1788151520 14
1788151525 14
1788151531 14
1788151536 14
1788151541 14
1788151546 14
1788151551 14
1788151556 14
1788151561 14
1788151566 14
1788151571 14
1788151576 14
1788151581 14
1788151586 12
1788151591 12
1788151596 12
1788151601 12
1788151606 12
```
</details>

---

