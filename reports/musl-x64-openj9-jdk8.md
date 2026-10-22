---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-22 08:01:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 293 |
| Sample Rate | 4.88/sec |
| Health Score | 305% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 19-24 cores)</summary>

```
1792670173 22
1792670178 24
1792670183 24
1792670188 24
1792670193 24
1792670198 24
1792670203 24
1792670208 24
1792670213 24
1792670218 24
1792670223 24
1792670228 24
1792670233 24
1792670238 19
1792670243 19
1792670248 19
1792670253 19
1792670258 19
1792670263 19
1792670268 19
```
</details>

---

