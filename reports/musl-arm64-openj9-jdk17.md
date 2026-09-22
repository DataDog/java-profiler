---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 12:22:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 842 |
| Sample Rate | 14.03/sec |
| Health Score | 877% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1790093773 40
1790093778 40
1790093783 40
1790093788 40
1790093793 40
1790093798 40
1790093803 40
1790093808 40
1790093813 40
1790093818 40
1790093823 40
1790093828 40
1790093833 40
1790093838 40
1790093843 40
1790093848 40
1790093853 40
1790093858 40
1790093863 40
1790093868 40
```
</details>

---

