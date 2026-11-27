---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 10:30:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 12 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 7 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 41-43 cores)</summary>

```
1795793143 43
1795793148 43
1795793153 43
1795793158 43
1795793163 43
1795793168 43
1795793173 43
1795793179 43
1795793184 43
1795793189 43
1795793194 43
1795793199 43
1795793204 43
1795793209 43
1795793214 43
1795793219 43
1795793224 43
1795793229 43
1795793234 43
1795793239 43
```
</details>

---

