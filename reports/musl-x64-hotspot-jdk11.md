---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 13:50:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 8 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 888 |
| Sample Rate | 14.80/sec |
| Health Score | 925% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 72-76 cores)</summary>

```
1794595536 76
1794595541 76
1794595546 76
1794595551 76
1794595556 76
1794595561 76
1794595566 76
1794595571 76
1794595576 76
1794595581 76
1794595586 76
1794595591 76
1794595596 76
1794595601 76
1794595606 76
1794595611 76
1794595616 76
1794595621 76
1794595626 72
1794595631 72
```
</details>

---

