---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-28 17:18:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1790629937 48
1790629942 48
1790629947 48
1790629952 48
1790629957 48
1790629962 48
1790629967 48
1790629972 48
1790629977 48
1790629982 48
1790629987 48
1790629993 48
1790629998 48
1790630003 48
1790630008 48
1790630013 48
1790630018 48
1790630023 48
1790630028 48
1790630033 48
```
</details>

---

