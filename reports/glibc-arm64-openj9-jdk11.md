---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 09:54:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 7 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790257753 50
1790257758 50
1790257763 50
1790257768 50
1790257773 50
1790257778 50
1790257783 50
1790257788 50
1790257793 50
1790257798 50
1790257803 50
1790257808 50
1790257813 50
1790257818 50
1790257823 50
1790257828 50
1790257833 50
1790257838 50
1790257843 50
1790257848 50
```
</details>

---

