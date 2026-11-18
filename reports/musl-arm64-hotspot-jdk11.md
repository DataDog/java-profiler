---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 08:22:46 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1795007922 36
1795007927 36
1795007932 36
1795007937 36
1795007942 36
1795007947 36
1795007952 36
1795007957 36
1795007962 36
1795007967 36
1795007972 36
1795007977 36
1795007982 36
1795007987 36
1795007992 36
1795007997 36
1795008002 36
1795008007 36
1795008012 36
1795008017 36
```
</details>

---

