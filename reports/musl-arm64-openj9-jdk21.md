---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-09 00:56:56 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 12 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1786251165 34
1786251170 34
1786251175 34
1786251180 34
1786251185 34
1786251190 34
1786251195 34
1786251200 29
1786251205 29
1786251210 29
1786251215 29
1786251220 29
1786251225 29
1786251230 29
1786251235 29
1786251240 34
1786251245 34
1786251250 34
1786251255 34
1786251260 32
```
</details>

---

