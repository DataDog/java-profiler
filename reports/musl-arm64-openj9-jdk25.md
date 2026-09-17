---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 18:02:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 14 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1789682175 28
1789682180 28
1789682185 28
1789682190 28
1789682195 28
1789682200 28
1789682205 28
1789682210 28
1789682215 28
1789682220 28
1789682225 28
1789682230 28
1789682235 28
1789682240 33
1789682245 33
1789682250 33
1789682255 33
1789682260 33
1789682265 33
1789682270 33
```
</details>

---

