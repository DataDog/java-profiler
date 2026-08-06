---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-06 10:08:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 154 |
| Sample Rate | 2.57/sec |
| Health Score | 161% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 14 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1786024995 53
1786025000 53
1786025005 53
1786025010 53
1786025015 48
1786025020 48
1786025025 48
1786025030 48
1786025035 48
1786025040 48
1786025045 48
1786025051 48
1786025056 48
1786025061 48
1786025066 48
1786025071 48
1786025076 48
1786025081 48
1786025086 48
1786025091 48
```
</details>

---

