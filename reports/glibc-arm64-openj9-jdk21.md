---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-21 09:26:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 13 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787318483 48
1787318488 48
1787318493 48
1787318498 48
1787318503 48
1787318508 48
1787318513 48
1787318518 48
1787318523 48
1787318528 48
1787318533 43
1787318538 43
1787318543 43
1787318548 43
1787318553 43
1787318558 43
1787318563 43
1787318568 43
1787318573 43
1787318578 43
```
</details>

---

