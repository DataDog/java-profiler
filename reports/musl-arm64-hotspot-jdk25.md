---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-19 15:32:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 308 |
| Sample Rate | 5.13/sec |
| Health Score | 321% |
| Threads | 12 |
| Allocations | 162 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 12 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1792438064 38
1792438069 38
1792438074 38
1792438079 38
1792438084 38
1792438089 38
1792438094 38
1792438099 38
1792438104 38
1792438109 43
1792438114 43
1792438119 48
1792438124 48
1792438129 48
1792438134 48
1792438139 48
1792438144 48
1792438149 48
1792438154 48
1792438159 48
```
</details>

---

