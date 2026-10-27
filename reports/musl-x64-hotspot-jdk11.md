---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 12:59:33 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 863 |
| Sample Rate | 14.38/sec |
| Health Score | 899% |
| Threads | 10 |
| Allocations | 555 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1793120069 30
1793120074 30
1793120079 30
1793120084 30
1793120089 30
1793120094 30
1793120100 30
1793120105 30
1793120110 30
1793120115 28
1793120120 28
1793120125 28
1793120130 28
1793120135 32
1793120140 32
1793120145 32
1793120150 32
1793120155 32
1793120160 32
1793120165 32
```
</details>

---

