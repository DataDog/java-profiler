---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 15:22:39 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (3 unique values: 43-51 cores)</summary>

```
1794341813 43
1794341818 43
1794341823 43
1794341828 43
1794341833 43
1794341838 43
1794341843 43
1794341848 43
1794341853 43
1794341858 43
1794341863 43
1794341868 47
1794341873 47
1794341878 47
1794341883 47
1794341888 47
1794341893 47
1794341898 47
1794341903 47
1794341908 47
```
</details>

---

