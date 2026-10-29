---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-29 12:43:59 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 6 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 12 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 39-40 cores)</summary>

```
1793291800 39
1793291805 39
1793291810 39
1793291815 39
1793291820 39
1793291825 39
1793291830 39
1793291835 40
1793291840 40
1793291845 40
1793291850 40
1793291855 40
1793291860 40
1793291865 40
1793291870 40
1793291875 40
1793291880 40
1793291885 40
1793291890 40
1793291895 40
```
</details>

---

