---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 12:59:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 9 |
| Allocations | 186 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 6 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793120100 48
1793120105 48
1793120110 48
1793120115 48
1793120120 48
1793120125 48
1793120130 48
1793120135 48
1793120140 48
1793120145 48
1793120150 48
1793120155 48
1793120160 48
1793120165 43
1793120170 43
1793120175 43
1793120180 43
1793120185 43
1793120190 43
1793120195 43
```
</details>

---

