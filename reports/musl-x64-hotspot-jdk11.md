---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 06:07:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 147 |
| Sample Rate | 2.45/sec |
| Health Score | 153% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 7 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 76-78 cores)</summary>

```
1795690891 76
1795690896 76
1795690901 76
1795690906 76
1795690911 76
1795690916 76
1795690921 76
1795690926 76
1795690931 76
1795690936 76
1795690941 76
1795690946 76
1795690951 76
1795690956 76
1795690961 76
1795690966 78
1795690971 78
1795690976 78
1795690981 78
1795690986 78
```
</details>

---

