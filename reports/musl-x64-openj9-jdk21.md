---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 08:31:19 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (3 unique values: 63-96 cores)</summary>

```
1795008295 75
1795008300 75
1795008305 75
1795008310 75
1795008315 75
1795008320 75
1795008325 75
1795008330 96
1795008335 96
1795008340 96
1795008345 96
1795008350 96
1795008355 96
1795008360 63
1795008365 63
1795008370 63
1795008375 63
1795008381 63
1795008386 63
1795008391 63
```
</details>

---

