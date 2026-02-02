---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-02-02 10:12:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 214 |
| Sample Rate | 3.57/sec |
| Health Score | 223% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 291 |
| Sample Rate | 4.85/sec |
| Health Score | 303% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (7 unique values: 55-62 cores)</summary>

```
1770044770 59
1770044775 61
1770044780 61
1770044785 61
1770044790 55
1770044795 55
1770044800 55
1770044805 55
1770044810 55
1770044815 62
1770044820 62
1770044825 58
1770044830 58
1770044835 58
1770044840 58
1770044845 58
1770044850 57
1770044855 57
1770044860 57
1770044865 57
```
</details>

---

