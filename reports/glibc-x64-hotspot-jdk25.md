---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 14:50:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (4 unique values: 71-82 cores)</summary>

```
1795031161 82
1795031166 82
1795031171 82
1795031176 82
1795031181 82
1795031186 82
1795031191 74
1795031196 74
1795031201 74
1795031206 73
1795031211 73
1795031216 73
1795031221 73
1795031226 73
1795031231 73
1795031236 73
1795031241 73
1795031246 73
1795031251 73
1795031256 73
```
</details>

---

