---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-06 04:52:17 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1772790472 24
1772790477 24
1772790482 24
1772790487 24
1772790492 24
1772790497 24
1772790502 24
1772790507 24
1772790512 24
1772790517 24
1772790522 24
1772790527 24
1772790532 24
1772790537 24
1772790542 24
1772790547 24
1772790552 24
1772790557 24
1772790562 24
1772790567 24
```
</details>

---

