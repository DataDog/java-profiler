---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-23 16:42:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 10 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790195914 50
1790195919 50
1790195924 50
1790195929 50
1790195934 50
1790195939 50
1790195944 50
1790195949 50
1790195954 50
1790195959 50
1790195964 50
1790195969 50
1790195974 50
1790195979 50
1790195984 50
1790195989 50
1790195994 50
1790195999 50
1790196004 50
1790196009 50
```
</details>

---

