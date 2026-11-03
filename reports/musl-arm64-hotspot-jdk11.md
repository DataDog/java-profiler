---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 12:51:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 12 |
| Allocations | 182 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 8 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 25-38 cores)</summary>

```
1793727966 25
1793727971 25
1793727976 38
1793727981 38
1793727986 25
1793727991 25
1793727996 25
1793728001 25
1793728006 25
1793728011 25
1793728016 25
1793728021 25
1793728026 25
1793728031 25
1793728036 25
1793728041 25
1793728046 25
1793728051 25
1793728056 25
1793728061 25
```
</details>

---

