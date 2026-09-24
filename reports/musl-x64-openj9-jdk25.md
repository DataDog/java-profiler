---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-24 06:19:09 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (4 unique values: 50-84 cores)</summary>

```
1790244813 63
1790244818 63
1790244823 63
1790244828 63
1790244833 63
1790244838 63
1790244843 63
1790244848 61
1790244853 61
1790244858 61
1790244863 61
1790244868 61
1790244873 61
1790244878 61
1790244883 61
1790244888 61
1790244893 61
1790244898 61
1790244903 61
1790244908 61
```
</details>

---

