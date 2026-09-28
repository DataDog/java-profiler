---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 10:34:16 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 875 |
| Sample Rate | 14.58/sec |
| Health Score | 911% |
| Threads | 9 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (2 unique values: 22-24 cores)</summary>

```
1790605748 24
1790605753 24
1790605758 24
1790605763 24
1790605768 22
1790605773 22
1790605778 22
1790605783 22
1790605788 22
1790605793 22
1790605798 22
1790605803 22
1790605808 22
1790605813 22
1790605818 22
1790605823 22
1790605828 24
1790605833 24
1790605838 22
1790605843 22
```
</details>

---

