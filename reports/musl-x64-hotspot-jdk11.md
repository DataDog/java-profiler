---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 14:50:21 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 9 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (3 unique values: 66-83 cores)</summary>

```
1795031126 74
1795031131 74
1795031136 74
1795031141 74
1795031146 74
1795031151 74
1795031156 74
1795031161 74
1795031166 74
1795031171 74
1795031176 74
1795031181 74
1795031186 74
1795031191 83
1795031196 83
1795031201 83
1795031206 83
1795031211 83
1795031216 66
1795031221 66
```
</details>

---

