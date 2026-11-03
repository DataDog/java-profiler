---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-03 12:55:03 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 10 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (4 unique values: 45-48 cores)</summary>

```
1793728219 47
1793728224 47
1793728229 47
1793728235 47
1793728240 47
1793728245 47
1793728250 47
1793728255 47
1793728260 47
1793728265 47
1793728270 47
1793728275 47
1793728280 45
1793728285 45
1793728290 45
1793728295 45
1793728300 45
1793728305 45
1793728310 46
1793728315 46
```
</details>

---

