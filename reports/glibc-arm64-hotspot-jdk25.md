---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 09:53:26 EST

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
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 13 |
| Allocations | 129 |

<details>
<summary>CPU Timeline (2 unique values: 29-44 cores)</summary>

```
1795186168 29
1795186173 29
1795186178 29
1795186183 29
1795186188 29
1795186193 29
1795186198 29
1795186203 29
1795186208 29
1795186213 29
1795186218 29
1795186223 29
1795186228 44
1795186233 44
1795186238 44
1795186243 44
1795186248 44
1795186253 44
1795186258 44
1795186263 44
```
</details>

---

