---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 13:11:29 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 7 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 14-26 cores)</summary>

```
1793207243 26
1793207248 26
1793207253 26
1793207258 26
1793207263 26
1793207268 26
1793207273 26
1793207278 26
1793207283 26
1793207288 26
1793207293 26
1793207298 26
1793207303 26
1793207308 26
1793207313 26
1793207318 26
1793207323 26
1793207328 26
1793207333 26
1793207338 26
```
</details>

---

