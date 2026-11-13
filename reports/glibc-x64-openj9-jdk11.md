---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 07:28:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 9 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (3 unique values: 59-79 cores)</summary>

```
1794572487 59
1794572492 59
1794572497 59
1794572502 59
1794572507 59
1794572512 63
1794572517 63
1794572522 63
1794572527 63
1794572532 63
1794572537 63
1794572542 79
1794572547 79
1794572552 79
1794572557 79
1794572562 79
1794572567 79
1794572572 79
1794572577 79
1794572583 79
```
</details>

---

