---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-21 10:05:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 9 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (2 unique values: 9-29 cores)</summary>

```
1792591197 29
1792591202 29
1792591207 29
1792591212 29
1792591217 29
1792591222 29
1792591227 29
1792591232 29
1792591237 29
1792591242 29
1792591247 9
1792591252 9
1792591257 9
1792591262 9
1792591267 9
1792591272 9
1792591277 9
1792591282 9
1792591287 9
1792591292 9
```
</details>

---

