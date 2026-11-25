---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:28:32 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1795630973 94
1795630978 94
1795630983 94
1795630988 94
1795630993 94
1795630998 94
1795631003 94
1795631008 94
1795631013 94
1795631018 96
1795631023 96
1795631028 96
1795631033 96
1795631038 96
1795631043 96
1795631048 94
1795631053 94
1795631058 94
1795631063 94
1795631068 94
```
</details>

---

