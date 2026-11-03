---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 12:55:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1035 |
| Sample Rate | 17.25/sec |
| Health Score | 1078% |
| Threads | 9 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793728261 48
1793728266 48
1793728271 48
1793728276 48
1793728281 48
1793728286 48
1793728291 48
1793728296 48
1793728301 48
1793728306 48
1793728311 48
1793728316 48
1793728321 48
1793728326 48
1793728331 48
1793728336 48
1793728341 48
1793728346 48
1793728351 48
1793728356 48
```
</details>

---

