---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 13:22:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 8 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1795025919 51
1795025924 51
1795025929 51
1795025934 51
1795025939 51
1795025944 51
1795025949 51
1795025954 51
1795025959 51
1795025964 51
1795025969 51
1795025974 51
1795025979 51
1795025984 51
1795025989 51
1795025994 51
1795025999 51
1795026005 51
1795026010 51
1795026015 51
```
</details>

---

