---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-01 15:38:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 434 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1788291120 44
1788291125 44
1788291130 44
1788291135 44
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
```
</details>

---

