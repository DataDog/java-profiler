---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 08:02:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 143 |
| Sample Rate | 2.38/sec |
| Health Score | 149% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 13 |
| Allocations | 170 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1794488238 43
1794488243 43
1794488248 43
1794488253 43
1794488258 43
1794488263 43
1794488268 43
1794488273 43
1794488278 43
1794488283 43
1794488288 43
1794488293 43
1794488298 43
1794488303 43
1794488308 43
1794488313 43
1794488318 43
1794488323 43
1794488328 43
1794488333 48
```
</details>

---

