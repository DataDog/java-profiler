---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:35:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 150 |
| Sample Rate | 2.50/sec |
| Health Score | 156% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 14 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1795631458 30
1795631463 30
1795631468 30
1795631473 30
1795631478 30
1795631483 30
1795631488 30
1795631493 30
1795631498 30
1795631503 30
1795631508 30
1795631513 30
1795631518 30
1795631523 30
1795631528 30
1795631533 30
1795631538 30
1795631543 34
1795631548 34
1795631553 34
```
</details>

---

