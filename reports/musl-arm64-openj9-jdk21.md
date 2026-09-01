---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-01 15:37:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1788291140 32
1788291145 32
1788291150 32
1788291155 32
1788291160 32
1788291165 32
1788291170 32
1788291175 32
1788291180 32
1788291185 32
1788291190 32
1788291195 32
1788291200 32
1788291205 32
1788291210 32
1788291215 32
1788291220 32
1788291225 32
1788291230 32
1788291235 32
```
</details>

---

