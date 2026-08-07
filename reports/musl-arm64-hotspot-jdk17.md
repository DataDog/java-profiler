---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-07 05:50:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 13 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1786095975 32
1786095980 32
1786095985 32
1786095990 32
1786095995 32
1786096000 32
1786096005 32
1786096010 32
1786096015 32
1786096020 31
1786096025 31
1786096030 31
1786096035 31
1786096040 31
1786096045 31
1786096050 31
1786096055 31
1786096060 31
1786096065 31
1786096070 31
```
</details>

---

