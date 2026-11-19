---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 13:54:35 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 9 |
| Allocations | 324 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 987 |
| Sample Rate | 16.45/sec |
| Health Score | 1028% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 77-81 cores)</summary>

```
1795114174 81
1795114179 81
1795114184 81
1795114189 81
1795114194 79
1795114199 79
1795114204 79
1795114209 79
1795114214 79
1795114219 79
1795114224 79
1795114229 79
1795114234 79
1795114239 79
1795114244 77
1795114249 77
1795114254 77
1795114259 77
1795114264 79
1795114269 79
```
</details>

---

