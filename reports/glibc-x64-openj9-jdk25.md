---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-24 15:44:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 82-84 cores)</summary>

```
1787600211 82
1787600216 82
1787600221 82
1787600226 82
1787600231 82
1787600236 82
1787600241 82
1787600246 82
1787600251 82
1787600256 84
1787600261 84
1787600266 82
1787600271 82
1787600276 82
1787600281 82
1787600286 82
1787600291 82
1787600296 84
1787600301 84
1787600306 84
```
</details>

---

