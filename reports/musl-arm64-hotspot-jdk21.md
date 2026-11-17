---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 08:47:49 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 287 |
| Sample Rate | 4.78/sec |
| Health Score | 299% |
| Threads | 11 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (2 unique values: 47-52 cores)</summary>

```
1794922836 52
1794922841 52
1794922846 52
1794922851 52
1794922856 52
1794922861 52
1794922866 47
1794922871 47
1794922876 47
1794922881 47
1794922886 47
1794922891 47
1794922896 47
1794922901 47
1794922906 47
1794922911 47
1794922916 47
1794922921 47
1794922926 47
1794922931 47
```
</details>

---

