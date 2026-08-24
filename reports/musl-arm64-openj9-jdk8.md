---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-23 21:24:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 21-26 cores)</summary>

```
1787534389 21
1787534394 21
1787534399 21
1787534404 26
1787534409 26
1787534414 26
1787534419 26
1787534424 26
1787534429 26
1787534434 26
1787534439 26
1787534444 26
1787534449 26
1787534454 26
1787534459 26
1787534464 26
1787534469 26
1787534474 26
1787534479 26
1787534484 26
```
</details>

---

