---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-21 06:29:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 8 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 8 |
| Allocations | 577 |

<details>
<summary>CPU Timeline (2 unique values: 26-28 cores)</summary>

```
1792578267 28
1792578272 28
1792578277 28
1792578282 28
1792578287 28
1792578292 28
1792578297 28
1792578302 28
1792578307 28
1792578312 28
1792578317 26
1792578322 26
1792578327 26
1792578332 26
1792578337 26
1792578342 26
1792578347 26
1792578352 26
1792578357 26
1792578362 26
```
</details>

---

