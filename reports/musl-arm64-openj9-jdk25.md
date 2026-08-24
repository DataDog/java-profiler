---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-23 21:23:19 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 9 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1787534349 46
1787534354 46
1787534359 46
1787534364 46
1787534369 43
1787534374 43
1787534379 43
1787534384 43
1787534389 43
1787534394 43
1787534399 43
1787534404 43
1787534409 43
1787534414 43
1787534419 43
1787534424 43
1787534429 43
1787534434 43
1787534439 48
1787534444 48
```
</details>

---

