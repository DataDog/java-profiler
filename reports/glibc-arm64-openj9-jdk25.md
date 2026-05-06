---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-06 15:34:41 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778095768 64
1778095773 64
1778095778 64
1778095783 64
1778095788 64
1778095793 64
1778095798 64
1778095803 64
1778095808 64
1778095813 64
1778095818 64
1778095823 64
1778095828 64
1778095833 64
1778095838 64
1778095843 64
1778095848 64
1778095853 64
1778095858 64
1778095863 64
```
</details>

---

