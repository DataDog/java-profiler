---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-23 21:22:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 8 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 10 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1787534342 46
1787534347 46
1787534352 46
1787534357 46
1787534362 46
1787534367 46
1787534372 43
1787534377 43
1787534382 43
1787534387 43
1787534392 43
1787534397 43
1787534402 43
1787534407 43
1787534412 43
1787534417 43
1787534422 43
1787534427 43
1787534432 43
1787534437 48
```
</details>

---

