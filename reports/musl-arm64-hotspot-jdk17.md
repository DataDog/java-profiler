---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-16 10:15:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 13 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (4 unique values: 46-64 cores)</summary>

```
1794841846 51
1794841851 51
1794841856 51
1794841861 51
1794841866 51
1794841871 51
1794841876 51
1794841881 51
1794841886 51
1794841891 51
1794841896 46
1794841901 46
1794841906 46
1794841911 46
1794841916 46
1794841921 46
1794841926 46
1794841931 46
1794841936 46
1794841941 59
```
</details>

---

