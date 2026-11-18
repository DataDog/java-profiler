---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 14:50:20 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 248 |
| Sample Rate | 4.13/sec |
| Health Score | 258% |
| Threads | 13 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1795031125 34
1795031130 34
1795031136 34
1795031141 34
1795031146 34
1795031151 34
1795031156 34
1795031161 34
1795031166 34
1795031171 34
1795031176 34
1795031181 34
1795031186 34
1795031191 34
1795031196 34
1795031201 34
1795031206 34
1795031211 32
1795031216 32
1795031221 32
```
</details>

---

