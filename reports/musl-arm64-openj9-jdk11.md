---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 08:09:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 7 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795525412 64
1795525417 64
1795525422 64
1795525427 64
1795525432 64
1795525437 64
1795525442 64
1795525447 64
1795525452 64
1795525457 64
1795525462 64
1795525467 64
1795525472 64
1795525477 64
1795525482 64
1795525487 64
1795525492 64
1795525497 64
1795525502 64
1795525507 64
```
</details>

---

