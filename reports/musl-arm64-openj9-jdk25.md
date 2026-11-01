---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-01 01:04:53 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 817 |
| Sample Rate | 13.62/sec |
| Health Score | 851% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1793509247 34
1793509252 34
1793509257 29
1793509262 29
1793509267 29
1793509272 29
1793509277 29
1793509282 29
1793509287 29
1793509292 29
1793509297 29
1793509302 29
1793509307 29
1793509312 29
1793509317 29
1793509322 29
1793509327 29
1793509332 29
1793509337 29
1793509342 29
```
</details>

---

