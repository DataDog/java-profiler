---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 12:58:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (5 unique values: 71-83 cores)</summary>

```
1795542751 71
1795542756 71
1795542761 71
1795542766 71
1795542771 79
1795542776 79
1795542781 79
1795542786 79
1795542791 79
1795542796 79
1795542801 79
1795542806 79
1795542811 79
1795542816 77
1795542821 77
1795542826 79
1795542831 79
1795542836 81
1795542841 81
1795542846 81
```
</details>

---

