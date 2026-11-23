---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:06:28 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 9 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1795449600 32
1795449605 32
1795449610 32
1795449615 32
1795449620 32
1795449625 32
1795449630 32
1795449635 32
1795449640 32
1795449645 32
1795449650 32
1795449655 32
1795449660 32
1795449665 32
1795449670 32
1795449675 32
1795449680 32
1795449685 32
1795449690 32
1795449695 30
```
</details>

---

