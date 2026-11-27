---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-27 11:20:31 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 9 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1795796147 94
1795796152 94
1795796157 94
1795796162 94
1795796167 94
1795796172 94
1795796177 94
1795796182 94
1795796187 94
1795796192 94
1795796198 94
1795796203 94
1795796208 94
1795796213 94
1795796218 94
1795796223 94
1795796228 94
1795796233 92
1795796238 92
1795796243 92
```
</details>

---

