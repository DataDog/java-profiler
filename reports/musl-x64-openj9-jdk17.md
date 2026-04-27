---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-27 16:29:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 10 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1034 |
| Sample Rate | 17.23/sec |
| Health Score | 1077% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (4 unique values: 63-70 cores)</summary>

```
1777321173 63
1777321178 65
1777321183 65
1777321188 65
1777321193 65
1777321198 70
1777321203 70
1777321208 70
1777321213 70
1777321218 70
1777321223 70
1777321228 70
1777321233 70
1777321238 70
1777321243 70
1777321248 70
1777321253 70
1777321258 70
1777321263 70
1777321268 70
```
</details>

---

