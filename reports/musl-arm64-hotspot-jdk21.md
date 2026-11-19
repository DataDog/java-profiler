---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 13:35:46 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 14 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 36-50 cores)</summary>

```
1795112757 36
1795112762 36
1795112767 36
1795112772 36
1795112777 36
1795112782 36
1795112787 36
1795112792 36
1795112797 36
1795112802 36
1795112808 36
1795112813 36
1795112818 36
1795112823 36
1795112828 36
1795112833 50
1795112838 50
1795112843 50
1795112848 50
1795112853 50
```
</details>

---

