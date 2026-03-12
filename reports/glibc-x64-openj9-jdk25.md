---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-12 11:39:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 10 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 12 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (4 unique values: 58-64 cores)</summary>

```
1773329672 64
1773329677 64
1773329682 64
1773329687 64
1773329692 64
1773329697 64
1773329702 63
1773329707 63
1773329712 63
1773329717 63
1773329722 63
1773329727 63
1773329732 61
1773329737 61
1773329742 63
1773329747 63
1773329752 63
1773329757 63
1773329762 63
1773329767 63
```
</details>

---

