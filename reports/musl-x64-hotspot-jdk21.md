---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-27 10:59:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (2 unique values: 53-55 cores)</summary>

```
1795794887 55
1795794892 55
1795794897 55
1795794902 55
1795794907 55
1795794912 55
1795794917 55
1795794922 55
1795794927 55
1795794932 55
1795794937 55
1795794942 55
1795794947 55
1795794952 55
1795794957 55
1795794962 55
1795794967 55
1795794972 55
1795794977 55
1795794982 53
```
</details>

---

