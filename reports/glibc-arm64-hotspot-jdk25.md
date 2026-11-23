---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 00:00:36 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795409846 29
1795409851 29
1795409856 29
1795409861 34
1795409866 34
1795409871 34
1795409876 34
1795409881 34
1795409886 34
1795409891 34
1795409896 34
1795409901 34
1795409906 34
1795409911 34
1795409916 34
1795409921 34
1795409926 34
1795409931 34
1795409936 34
1795409941 34
```
</details>

---

