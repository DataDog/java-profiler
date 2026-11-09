---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-09 05:57:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (2 unique values: 39-40 cores)</summary>

```
1794221516 40
1794221521 40
1794221526 39
1794221531 39
1794221536 39
1794221541 39
1794221546 39
1794221551 39
1794221556 39
1794221561 39
1794221566 39
1794221571 39
1794221576 39
1794221581 39
1794221586 39
1794221591 39
1794221596 39
1794221601 39
1794221606 39
1794221611 39
```
</details>

---

