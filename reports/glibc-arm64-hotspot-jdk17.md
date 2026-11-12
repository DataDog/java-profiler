---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 04:59:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 13 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794477278 48
1794477283 48
1794477288 48
1794477293 48
1794477298 48
1794477303 48
1794477308 48
1794477313 48
1794477318 48
1794477323 48
1794477328 48
1794477333 48
1794477338 48
1794477343 48
1794477348 48
1794477353 48
1794477358 48
1794477363 48
1794477368 48
1794477373 48
```
</details>

---

