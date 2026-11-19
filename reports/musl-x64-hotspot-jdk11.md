---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 05:46:58 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 12.92/sec |
| Health Score | 807% |
| Threads | 9 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 60-64 cores)</summary>

```
1795084956 62
1795084961 62
1795084966 62
1795084971 62
1795084976 62
1795084981 62
1795084986 62
1795084991 62
1795084996 62
1795085001 62
1795085006 62
1795085011 62
1795085016 64
1795085021 64
1795085026 62
1795085031 62
1795085036 62
1795085041 62
1795085046 60
1795085051 60
```
</details>

---

