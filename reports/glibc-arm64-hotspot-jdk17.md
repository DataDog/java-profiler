---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-16 10:15:45 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794841881 43
1794841886 43
1794841891 43
1794841896 43
1794841901 43
1794841906 43
1794841911 43
1794841916 43
1794841921 43
1794841926 43
1794841931 43
1794841936 43
1794841941 43
1794841946 43
1794841951 43
1794841956 43
1794841961 43
1794841966 38
1794841971 38
1794841976 38
```
</details>

---

