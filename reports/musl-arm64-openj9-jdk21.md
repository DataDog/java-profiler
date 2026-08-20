---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-19 22:04:18 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 9 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1787191194 64
1787191199 64
1787191204 64
1787191209 64
1787191214 64
1787191219 64
1787191224 64
1787191229 64
1787191234 64
1787191239 64
1787191244 64
1787191249 64
1787191254 59
1787191259 59
1787191264 59
1787191269 59
1787191274 59
1787191279 59
1787191284 59
1787191289 59
```
</details>

---

