---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-27 16:29:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 54-68 cores)</summary>

```
1777321163 68
1777321168 68
1777321173 68
1777321178 68
1777321183 68
1777321188 68
1777321193 68
1777321198 68
1777321203 68
1777321208 54
1777321213 54
1777321218 54
1777321223 54
1777321228 61
1777321233 61
1777321238 61
1777321243 61
1777321248 61
1777321253 61
1777321258 61
```
</details>

---

