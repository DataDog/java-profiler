---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 05:32:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793615251 32
1793615256 32
1793615261 32
1793615267 32
1793615272 32
1793615277 32
1793615282 32
1793615287 32
1793615292 32
1793615297 32
1793615302 32
1793615307 32
1793615312 32
1793615317 32
1793615322 32
1793615327 32
1793615332 32
1793615337 32
1793615342 32
1793615347 32
```
</details>

---

