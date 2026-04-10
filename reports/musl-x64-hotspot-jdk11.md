---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-10 11:02:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 984 |
| Sample Rate | 16.40/sec |
| Health Score | 1025% |
| Threads | 9 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1775833028 28
1775833033 30
1775833038 30
1775833043 30
1775833048 30
1775833053 30
1775833058 30
1775833063 30
1775833068 30
1775833073 30
1775833078 30
1775833083 30
1775833088 30
1775833093 30
1775833098 30
1775833103 30
1775833108 30
1775833113 30
1775833118 30
1775833123 30
```
</details>

---

