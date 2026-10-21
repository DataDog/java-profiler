---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-21 05:55:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 10 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 662 |
| Sample Rate | 11.03/sec |
| Health Score | 689% |
| Threads | 11 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (3 unique values: 61-82 cores)</summary>

```
1792576253 82
1792576258 82
1792576263 82
1792576268 82
1792576273 82
1792576278 82
1792576283 82
1792576288 82
1792576293 82
1792576298 82
1792576303 82
1792576308 82
1792576313 61
1792576318 61
1792576323 63
1792576328 63
1792576333 63
1792576338 63
1792576343 63
1792576348 63
```
</details>

---

