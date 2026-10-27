---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 19:04:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (3 unique values: 51-64 cores)</summary>

```
1793141965 51
1793141970 51
1793141975 51
1793141980 51
1793141985 51
1793141990 51
1793141995 51
1793142000 51
1793142005 51
1793142010 51
1793142015 64
1793142020 64
1793142025 64
1793142030 64
1793142035 64
1793142040 64
1793142045 64
1793142050 64
1793142055 64
1793142060 64
```
</details>

---

