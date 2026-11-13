---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 07:31:27 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 8 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794572888 32
1794572893 32
1794572898 32
1794572903 32
1794572908 32
1794572913 32
1794572918 32
1794572923 32
1794572929 32
1794572934 32
1794572939 32
1794572944 32
1794572949 32
1794572954 32
1794572959 32
1794572964 32
1794572969 32
1794572974 32
1794572979 32
1794572984 32
```
</details>

---

