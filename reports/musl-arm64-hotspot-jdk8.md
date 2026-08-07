---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-07 12:24:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 138 |
| Sample Rate | 2.30/sec |
| Health Score | 144% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 9-29 cores)</summary>

```
1786119561 14
1786119566 14
1786119571 14
1786119576 14
1786119581 9
1786119586 9
1786119591 29
1786119596 29
1786119601 29
1786119606 29
1786119611 29
1786119616 29
1786119621 9
1786119626 9
1786119631 9
1786119636 9
1786119641 9
1786119646 9
1786119651 9
1786119656 9
```
</details>

---

