---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 05:23:19 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 308 |
| Sample Rate | 5.13/sec |
| Health Score | 321% |
| Threads | 8 |
| Allocations | 174 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1794910607 29
1794910612 29
1794910617 29
1794910622 34
1794910627 34
1794910632 34
1794910637 34
1794910642 34
1794910647 34
1794910652 34
1794910657 34
1794910662 34
1794910667 34
1794910672 34
1794910677 34
1794910682 34
1794910687 34
1794910692 34
1794910697 34
1794910702 34
```
</details>

---

