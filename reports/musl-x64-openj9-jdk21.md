---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-08 12:05:52 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 10 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (4 unique values: 74-80 cores)</summary>

```
1791475208 78
1791475213 78
1791475218 80
1791475223 80
1791475228 80
1791475233 80
1791475238 78
1791475243 78
1791475248 78
1791475253 78
1791475258 78
1791475263 78
1791475268 78
1791475273 78
1791475278 78
1791475283 78
1791475288 76
1791475293 76
1791475298 74
1791475303 74
```
</details>

---

