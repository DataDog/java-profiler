---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-30 21:22:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 229 |
| Sample Rate | 3.82/sec |
| Health Score | 239% |
| Threads | 9 |
| Allocations | 135 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 14 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1788139110 29
1788139115 29
1788139120 29
1788139125 29
1788139130 29
1788139135 29
1788139140 29
1788139145 29
1788139150 29
1788139155 29
1788139160 34
1788139165 34
1788139170 34
1788139175 29
1788139180 29
1788139185 29
1788139190 29
1788139195 29
1788139200 29
1788139205 29
```
</details>

---

