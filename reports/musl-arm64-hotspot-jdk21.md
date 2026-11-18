---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 10:03:30 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 251 |
| Sample Rate | 4.18/sec |
| Health Score | 261% |
| Threads | 14 |
| Allocations | 113 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1795013803 48
1795013808 48
1795013813 48
1795013818 48
1795013823 48
1795013828 48
1795013833 48
1795013838 48
1795013843 48
1795013848 48
1795013853 48
1795013858 48
1795013863 48
1795013868 48
1795013873 48
1795013878 48
1795013883 48
1795013888 48
1795013893 43
1795013898 43
```
</details>

---

