---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 08:20:13 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 6 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (1 unique values: 51-51 cores)</summary>

```
1794402930 51
1794402935 51
1794402940 51
1794402945 51
1794402950 51
1794402955 51
1794402960 51
1794402965 51
1794402970 51
1794402975 51
1794402980 51
1794402985 51
1794402990 51
1794402995 51
1794403000 51
1794403005 51
1794403010 51
1794403015 51
1794403020 51
1794403025 51
```
</details>

---

