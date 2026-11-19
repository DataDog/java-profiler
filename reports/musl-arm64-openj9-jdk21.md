---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 09:14:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 14 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (3 unique values: 14-53 cores)</summary>

```
1795097236 14
1795097241 14
1795097246 14
1795097251 14
1795097256 14
1795097261 14
1795097266 14
1795097271 14
1795097276 14
1795097281 14
1795097286 14
1795097291 14
1795097296 14
1795097301 14
1795097306 14
1795097311 14
1795097316 18
1795097321 18
1795097326 18
1795097331 18
```
</details>

---

