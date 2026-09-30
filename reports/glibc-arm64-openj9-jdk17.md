---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-30 05:50:41 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 13 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (3 unique values: 26-51 cores)</summary>

```
1790761517 31
1790761522 31
1790761527 31
1790761532 31
1790761537 31
1790761542 31
1790761547 31
1790761552 31
1790761557 31
1790761562 26
1790761567 26
1790761572 26
1790761577 26
1790761582 26
1790761587 26
1790761592 26
1790761597 26
1790761602 26
1790761607 26
1790761612 31
```
</details>

---

