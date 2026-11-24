---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 08:09:21 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 794 |
| Sample Rate | 13.23/sec |
| Health Score | 827% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 987 |
| Sample Rate | 16.45/sec |
| Health Score | 1028% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 64-81 cores)</summary>

```
1795525405 64
1795525410 64
1795525415 64
1795525420 64
1795525425 64
1795525431 64
1795525436 64
1795525441 64
1795525446 64
1795525451 64
1795525456 81
1795525461 81
1795525466 81
1795525471 81
1795525476 81
1795525481 79
1795525486 79
1795525491 79
1795525496 79
1795525501 81
```
</details>

---

