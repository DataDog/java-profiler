---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 12:04:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 11 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 40-45 cores)</summary>

```
1793203127 45
1793203132 45
1793203137 45
1793203142 45
1793203147 40
1793203152 40
1793203157 40
1793203162 40
1793203167 40
1793203172 40
1793203177 40
1793203182 40
1793203187 40
1793203192 40
1793203197 45
1793203202 45
1793203207 43
1793203212 43
1793203217 43
1793203222 43
```
</details>

---

