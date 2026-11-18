---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:34:32 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795015813 46
1795015818 46
1795015823 46
1795015828 46
1795015833 46
1795015838 46
1795015843 46
1795015848 46
1795015853 46
1795015858 46
1795015863 46
1795015868 46
1795015873 51
1795015878 51
1795015883 51
1795015888 51
1795015893 51
1795015898 51
1795015903 51
1795015908 51
```
</details>

---

