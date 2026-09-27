---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-27 00:58:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 279 |
| Sample Rate | 4.65/sec |
| Health Score | 291% |
| Threads | 9 |
| Allocations | 147 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 6 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 38-43 cores)</summary>

```
1790484803 38
1790484808 38
1790484813 38
1790484818 38
1790484823 38
1790484828 43
1790484833 43
1790484838 43
1790484843 43
1790484848 43
1790484853 43
1790484858 43
1790484863 43
1790484868 41
1790484873 41
1790484878 41
1790484883 41
1790484888 41
1790484893 41
1790484898 41
```
</details>

---

