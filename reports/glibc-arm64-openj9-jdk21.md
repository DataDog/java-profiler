---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-01 15:37:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (3 unique values: 32-64 cores)</summary>

```
1788291135 64
1788291140 64
1788291145 64
1788291150 64
1788291155 64
1788291160 64
1788291165 64
1788291170 64
1788291175 64
1788291180 64
1788291185 64
1788291190 64
1788291195 64
1788291200 64
1788291205 64
1788291210 64
1788291215 64
1788291220 64
1788291225 64
1788291230 64
```
</details>

---

