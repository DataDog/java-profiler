---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 06:39:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 168 |
| Sample Rate | 2.80/sec |
| Health Score | 175% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 143 |
| Sample Rate | 2.38/sec |
| Health Score | 149% |
| Threads | 13 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1795606558 28
1795606563 28
1795606568 28
1795606573 28
1795606578 28
1795606583 28
1795606588 28
1795606593 28
1795606598 28
1795606603 28
1795606608 28
1795606613 28
1795606618 28
1795606623 28
1795606628 28
1795606633 28
1795606638 28
1795606643 28
1795606648 28
1795606653 28
```
</details>

---

