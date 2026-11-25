---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:35:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 12 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 14 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795631443 29
1795631448 29
1795631453 29
1795631458 29
1795631463 29
1795631468 29
1795631473 29
1795631478 29
1795631483 29
1795631488 29
1795631493 29
1795631498 29
1795631503 29
1795631508 29
1795631513 29
1795631518 29
1795631523 29
1795631528 34
1795631533 34
1795631538 34
```
</details>

---

