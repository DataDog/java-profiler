---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-22 05:27:13 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (4 unique values: 24-44 cores)</summary>

```
1787390497 34
1787390502 34
1787390507 34
1787390512 34
1787390517 24
1787390522 24
1787390527 24
1787390532 29
1787390537 29
1787390542 44
1787390547 44
1787390552 44
1787390557 44
1787390562 44
1787390567 44
1787390572 44
1787390577 44
1787390582 44
1787390587 44
1787390592 44
```
</details>

---

