---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 08:53:42 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794491342 36
1794491347 36
1794491352 36
1794491357 48
1794491362 48
1794491367 48
1794491372 48
1794491377 48
1794491382 48
1794491387 48
1794491392 48
1794491397 48
1794491402 48
1794491407 48
1794491412 48
1794491417 48
1794491422 48
1794491427 48
1794491432 48
1794491437 48
```
</details>

---

