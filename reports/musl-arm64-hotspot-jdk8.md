---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-18 00:06:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
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
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1794978140 29
1794978145 29
1794978150 29
1794978155 29
1794978160 34
1794978165 34
1794978170 29
1794978175 29
1794978180 29
1794978185 29
1794978190 29
1794978195 29
1794978200 29
1794978205 29
1794978210 29
1794978215 29
1794978220 29
1794978225 29
1794978230 34
1794978235 34
```
</details>

---

