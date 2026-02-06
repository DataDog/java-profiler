---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-06 10:50:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 835 |
| Sample Rate | 13.92/sec |
| Health Score | 870% |
| Threads | 9 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770392728 32
1770392733 32
1770392738 32
1770392743 32
1770392748 32
1770392753 32
1770392758 32
1770392763 32
1770392768 32
1770392773 32
1770392778 32
1770392783 30
1770392788 30
1770392793 30
1770392799 30
1770392804 30
1770392809 30
1770392814 30
1770392819 30
1770392824 30
```
</details>

---

