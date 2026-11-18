---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:25:47 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 918 |
| Sample Rate | 15.30/sec |
| Health Score | 956% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (3 unique values: 81-85 cores)</summary>

```
1795015262 85
1795015267 85
1795015272 85
1795015277 85
1795015282 85
1795015287 85
1795015292 83
1795015297 83
1795015302 83
1795015307 83
1795015312 83
1795015317 83
1795015322 83
1795015327 83
1795015332 83
1795015337 83
1795015342 83
1795015347 83
1795015352 81
1795015357 81
```
</details>

---

