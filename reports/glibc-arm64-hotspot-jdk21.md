---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 10:18:48 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 9 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1795706054 38
1795706059 38
1795706064 38
1795706069 43
1795706074 43
1795706079 43
1795706084 43
1795706089 43
1795706094 43
1795706099 43
1795706104 43
1795706109 43
1795706114 43
1795706119 43
1795706124 43
1795706129 43
1795706134 43
1795706139 43
1795706144 43
1795706149 43
```
</details>

---

