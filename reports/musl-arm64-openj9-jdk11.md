---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 11:47:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 14 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 20-23 cores)</summary>

```
1793115758 23
1793115763 23
1793115768 20
1793115773 20
1793115778 20
1793115783 20
1793115788 20
1793115793 20
1793115798 20
1793115803 20
1793115808 20
1793115813 20
1793115818 20
1793115823 23
1793115828 23
1793115833 23
1793115838 23
1793115843 23
1793115848 23
1793115853 23
```
</details>

---

